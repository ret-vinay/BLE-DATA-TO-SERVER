#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_message.h"
#include "at_init.h"
#include "http.h"
#include "ble.h"

#define __HTTP_Server  1
#define Max_House_No 4     // number of RF_id houses. example: 4  // consider as a 3 houses

/**************************Function declaration*********************************************/
void Neo_AtInit(void);
void Neoway_MessageTimersInit(void);
void Neo_AT_ReceiveManage(U8 *buff_ptr, U16 len, NeowayModuleTypeEnum mod_id);
void Neo_SearchAtResponse(U8 *Buffaddr, U16 Length, NeowayModuleTypeEnum mod_id);
NeowayBoolEnum Neo_SendAT(NeowayCmdEnum cmd,S8* send_str,U32 str_length,S8* send_data,U32 data_length);
void Neo_ATSendOvertime(void);
void Neo_ATSendError(void);
void Neo_ATSendOK(void);
void Neo_SendNextAT(void);
void Neo_ATSendCmd(void);
void Neo_ATSendData(void);
/*******************************************************************************************/

/**************************timer_id's declaration*********************************************/
NeowayTimerId neoway_at_stream;
NeowayTimerId neoway_to_send_at;//Send AT commands in the queue.
NeowayTimerId neoway_at_send_overtime;
NeowayTimerId neoway_fota_strart;
/******************************************************************************************/
/***************************control flag related to BLE RF_id***********************************/
U8 server_data[500];// temperory buffer to hold data
/******************************************************************************************/
/***************************variables related to BLE RF_id***********************************/
U8 XIIC_register_state=0,Module_IMEI_Number[50]="NA";
U8 gNeo_register_state=0,gNeo_signal_strong=0, gNeo_MSG_send_count=0;
/******************************************************************************************/

Neo_Send_At_Info gNeo_send_at_info_link[20];//Send SMS. Making call through TCP data is in the saving queue.
NeowaySendAtInfoState gNeo_send_at_info_state;
Neo_Send_At_Info gNeo_at_info={0};

Neo_AtResponseDistill gNeo_at_response_parser=
{
	{0},
	0,
	0,
	0,
	0
};

/********************************************************************************************
 * Definition: Neo_AtInit
 * Parameter: void
 * Return value: void
 * Comments: Initialization of command pointer to point command/data buffer
 ********************************************************************************************/
void Neo_AtInit(void)
{
	memset(&gNeo_send_at_info_state,0,sizeof(gNeo_send_at_info_state));
	memset(&gNeo_send_at_info_link,0,sizeof(gNeo_send_at_info_link));
	gNeo_send_at_info_state.head_position=&gNeo_send_at_info_link[0];
	gNeo_send_at_info_state.end_position=&gNeo_send_at_info_link[0];
	gNeo_send_at_info_state.total_item=0;
}
/********************************************************************************************
 * Definition: Neoway_MessageTimersInit
 * Parameter: void
 * Return value: void
 * Comments: timers Initialization to usertask's
 ********************************************************************************************/
void Neoway_MessageTimersInit(void)
{
	Neoway_InitTimer(&neoway_at_stream,NEOWAY_MOD_USER1);
	Neoway_InitTimer(&neoway_to_send_at, NEOWAY_MOD_USER1);
	Neoway_InitTimer(&neoway_at_send_overtime, NEOWAY_MOD_USER1);
	Neoway_InitTimer(&neoway_fota_strart,NEOWAY_MOD_USER1);
}
/********************************************************************************************
 * Definition: Neo_ATSendOvertime
 * Parameter: void
 * Return value: void
 * Comments: if device exceeds response time call this function
 ********************************************************************************************/
void Neo_ATSendOvertime(void)
{	
	// Neoway_Print("calling ATSendError function");
	Neo_ATSendError();
}
/********************************************************************************************
 * Definition: Neo_AT_ReceiveManage
 * Parameter: U8 *buff_ptr, U16 len, NeowayModuleTypeEnum mod_id
 * Return value: void
 * Comments: checking response for next AT command send or data send  
 ********************************************************************************************/
void Neo_AT_ReceiveManage(U8 *buff_ptr, U16 len, NeowayModuleTypeEnum mod_id)
{	
	U16 i;
	//Neoway_UartSend(0,(U8*)&mod_id,2);
	// Neoway_Print("Process the UART receive function");
	memcpy(&gNeo_at_response_parser.buffer[gNeo_at_response_parser.last_lenth],buff_ptr,len);
	len=len+gNeo_at_response_parser.last_lenth;
	for(i=gNeo_at_response_parser.last_lenth;i<len;i++)
	{
		if(gNeo_at_response_parser.buffer[i]=='>')
		{
			if(gNeo_MSG_send_count<=1)
			{
				gNeo_MSG_send_count++;
				Neoway_SendMsgTask(mod_id,NEOWAY_MOD_USER1,NEOWAY_MSG_ID_DATA_SEND_REQUIRE,NULL,0);
			}
			gNeo_at_response_parser.tag_num=0;
			gNeo_at_response_parser.column++;
		}
		else if(gNeo_at_response_parser.buffer[i]==0x0D)
		{
			gNeo_at_response_parser.tag_num=1;
			gNeo_at_response_parser.column++;
		}
		else if(gNeo_at_response_parser.buffer[i]==0x0A)
		{

			if(gNeo_at_response_parser.tag_num==1)//0d 0a
			{
				Neo_SearchAtResponse(&gNeo_at_response_parser.buffer[gNeo_at_response_parser.start_position],gNeo_at_response_parser.column-1, mod_id);
				gNeo_at_response_parser.column=0;
				gNeo_at_response_parser.start_position=i+1;
				gNeo_at_response_parser.tag_num=0;
			}else
			{
				gNeo_at_response_parser.column++;
			}
		}
		else
		{
			gNeo_at_response_parser.tag_num=0;
			gNeo_at_response_parser.column++;
		}	
	}
	gNeo_at_response_parser.last_lenth=len-gNeo_at_response_parser.start_position;
	memcpy(&gNeo_at_response_parser.buffer[0],&gNeo_at_response_parser.buffer[gNeo_at_response_parser.start_position],gNeo_at_response_parser.last_lenth);
	gNeo_at_response_parser.start_position=0; 
}
/********************************************************************************************
 * Definition: Neo_SearchAtResponse
 * Parameter: U8 *Buffaddr, U16 Length, NeowayModuleTypeEnum mod_id
 * Return value: void
 * Comments: separation of AT command response 
 ********************************************************************************************/
void Neo_SearchAtResponse(U8 *Buffaddr, U16 Length, NeowayModuleTypeEnum mod_id)
{
	// Neoway_Print("Process the UART receive SearchAtResponse function");
	if(Length==0||Length==1)
	{
		return ;
	}
	else if(memcmp(&Buffaddr[0],"MODEM:ST",8)==0)
	{ 
		Neoway_SendMsgTask(mod_id,NEOWAY_MOD_USER1,NEOWAY_FOTA_START_NOTIFY,NULL,0);
	}	
	else if(memcmp(&Buffaddr[0],"OK",2)==0)
	{
		Neoway_SendMsgTask(mod_id,NEOWAY_MOD_USER1,NEOWAY_MSG_ID_AT_SEND_OK,NULL,0);
	}
	else if(memcmp(&Buffaddr[0],"ERROR",5)==0)
	{
		Neoway_SendMsgTask(mod_id,NEOWAY_MOD_USER1,NEOWAY_MSG_ID_AT_SEND_ERROR,NULL,0);
	}
	else if(memcmp(&Buffaddr[0],"+CSQ",4)==0)
	{
		if(Buffaddr[7]==',')//One bit
		{
			gNeo_signal_strong=Buffaddr[6]-0x30;
		}
		else if(Buffaddr[6]=='9')
		{
			gNeo_signal_strong=0;
		}
		else
		{
			gNeo_signal_strong=(Buffaddr[6]-0x30)*10+(Buffaddr[7]-0x30);
		}
	}
	else if(memcmp(&Buffaddr[0],"+CREG",5)==0)
	{
		if(Buffaddr[9]=='1'||Buffaddr[9]=='5')
		{
			gNeo_register_state=Buffaddr[9]-0x30;
		}
		else
		{
			gNeo_register_state=0;
		}
	}
	else if(memcmp(&Buffaddr[0],"+CGSN:",6)==0)
	{
		strncpy(Module_IMEI_Number,&Buffaddr[7],15);// strlen(Buffaddr)-9);	
	}
	else if(memcmp(&Buffaddr[0],"+XIIC:",6)==0)
	{
		if(Buffaddr[10]=='1'&&Buffaddr[11]==',')
		{
			XIIC_register_state=1;
		}
		else
		{
			XIIC_register_state=0;
		}
	}
	else if(memcmp(&Buffaddr[0],"+TCPCLOSE",9)==0)
	{
	}
	else if(memcmp(&Buffaddr[0],"+TCPSETUP",9)==0)
	{
	}
	else if(memcmp(&Buffaddr[0],"+TCPSEND",8)==0)
	{
	}
	else if(memcmp(&Buffaddr[0],"GPRS DISCONNECTION",18)==0)
	{
	}
	else if(memcmp(&Buffaddr[0],"+CMT:",5)==0)
	{
	}
	else if( memcmp(&Buffaddr[0],"+HTTPRECV:",10)==0 ) 
	{
		
	}
	else if( memcmp(&Buffaddr[0],"HTTP/",5)==0 )
	{
	}
	else if(memcmp(&Buffaddr[0],"+HTTPCLOSED:",12)==0)
	{
	}
	else if( memcmp(&Buffaddr[0],"+CIPGSMLOC:",11)==0 )
	{
	}
	else if( memcmp(&Buffaddr[0],"+GLTS:",6)==0 ) // +UPDATETIME:
	{
	}
	else if( memcmp(&Buffaddr[0],"+UPDATETIME:",12)==0 )
	{
	}
}
/********************************************************************************************
 * Definition: Neo_ATSendCmd 
 * Parameter: void
 * Return value: void
 * Comments: sending the AT commands
 ********************************************************************************************/
void Neo_ATSendCmd(void)
{
	if(gNeo_at_info.at_send_state!=AT_IDLE)//Sending AT commands
	{
		return;//Exit directly
	}
	else if(gNeo_send_at_info_state.total_item!=0)
	{
		memcpy(&gNeo_at_info,gNeo_send_at_info_state.head_position,sizeof(Neo_Send_At_Info));
		gNeo_send_at_info_state.total_item--;
		if(gNeo_send_at_info_state.head_position == (&gNeo_send_at_info_link[19]))
		{
			gNeo_send_at_info_state.head_position = &gNeo_send_at_info_link[0];
		}
		else
		{
			gNeo_send_at_info_state.head_position++;
		}
		switch (gNeo_at_info.cmd)
		{
			case CMD_CSQ:
			case CMD_CMGS:
			case CMD_TCPSEND:
			case CMD_GPSPWR:
			case CMD_PHONE:
			case CMD_AT:
			case CMD_INIT:
			case CMD_TCP0:
			case CMD_TCP1:
				gNeo_at_info.at_send_state=AT_SENDING;//Sending AT commands
				Neoway_StartTimer(&neoway_at_send_overtime,1080);//Sending times out after 5 seconds.
				Neoway_VirtualUartSend(NEOWAY_MOD_USER1,gNeo_at_info.send_str,gNeo_at_info.str_length);
				break;
			case CMD_TCP0_SETUP:
			case CMD_TCP1_SETUP:
				gNeo_at_info.at_send_state=AT_SENDING;//Sending AT commands
				Neoway_StartTimer(&neoway_at_send_overtime,6500);//Sending times out after 30.1 seconds.
				Neoway_VirtualUartSend(NEOWAY_MOD_USER1,gNeo_at_info.send_str,gNeo_at_info.str_length);
				break;
			case CMD_HTTP:/**********HTTP****************/
			case CMD_MQTT:/**********MQTT****************/
				gNeo_at_info.at_send_state=AT_SENDING;//Sending AT commands
				Neoway_StartTimer(&neoway_at_send_overtime,2160);//Sending times out after 30.1 seconds.
				Neoway_VirtualUartSend(NEOWAY_MOD_USER1,gNeo_at_info.send_str,gNeo_at_info.str_length);
				break;
			case CMD_HTTP_SETUP:/**********HTTP_SETUP****************/
			case CMD_MQTT_SETUP:/**********MQTT_SETUP****************/
				gNeo_at_info.at_send_state=AT_SENDING;//Sending AT commands
				Neoway_StartTimer(&neoway_at_send_overtime,6500);//Sending times out after 30.1 seconds.
				Neoway_VirtualUartSend(NEOWAY_MOD_USER1,gNeo_at_info.send_str,gNeo_at_info.str_length);
				break;
			default : gNeo_at_info.cmd=CMD_NULL;
				break;
		}
		return ;
	}
}
/********************************************************************************************
 * Definition: Neo_ATSendData 
 * Parameter: void
 * Return value: void
 * Comments: sending the Data
 ********************************************************************************************/
void Neo_ATSendData(void)
{
	if(gNeo_at_info.at_send_state==AT_SENDING&&(gNeo_at_info.cmd==CMD_CMGS||gNeo_at_info.cmd==CMD_HTTP))//CMD_TCPSEND))
	{
		Neoway_StopTimer(&neoway_at_send_overtime);
		Neoway_StartTimer(&neoway_at_send_overtime,10800);//Sending times out after 50 seconds.
		gNeo_at_info.at_send_state=AT_SENDING_DATA;
		Neoway_VirtualUartSend(NEOWAY_MOD_USER1,gNeo_at_info.send_data,gNeo_at_info.data_length);//
	}
}
/********************************************************************************************
 * Definition: Neo_SendAT 
 * Parameter: NeowayCmdEnum cmd,S8* send_str,U32 str_length,S8* send_data,U32 data_length
 * Return value: NeowayBoolEnum
 * Comments: if device got error response, call back to send same command again
 ********************************************************************************************/
NeowayBoolEnum Neo_SendAT(NeowayCmdEnum cmd,S8* send_str,U32 str_length,S8* send_data,U32 data_length)
{
	Neo_AtInit();
	//	Neoway_Print("total item = %d AT:%s", gNeo_send_at_info_state.total_item,send_str);
	if(gNeo_send_at_info_state.total_item >= 20)
	{
		//	Neoway_Print("OVERFLOW total item = %d AT:%s", gNeo_send_at_info_state.total_item,send_str);
		return NEOWAY_FALSE;
	}
	
	memset(gNeo_send_at_info_state.end_position,0,sizeof(Neo_Send_At_Info));
	gNeo_send_at_info_state.end_position->cmd=cmd;
	gNeo_send_at_info_state.end_position->at_send_state=AT_IDLE;
	gNeo_send_at_info_state.end_position->str_length = str_length;
	memcpy(gNeo_send_at_info_state.end_position->send_str,send_str,str_length);
	//	Neoway_Print("end_position %s", gNeo_send_at_info_state.end_position->send_str);

	if(data_length==0)
	{
		gNeo_send_at_info_state.end_position->send_data[0]=0;//=NULL;
		gNeo_send_at_info_state.end_position->data_length=data_length;
	}
	else
	{
		gNeo_send_at_info_state.end_position->data_length=data_length;
		memcpy(gNeo_send_at_info_state.end_position->send_data,send_data,data_length);
		gNeo_send_at_info_state.end_position->send_data[data_length]=0;
	}
	if(gNeo_send_at_info_state.end_position == (&gNeo_send_at_info_link[19]))
	{
		gNeo_send_at_info_state.end_position = &gNeo_send_at_info_link[0];
	}
	else
	{
		gNeo_send_at_info_state.end_position++;
	}
	gNeo_send_at_info_state.total_item++;
	
	if(gNeo_send_at_info_state.total_item==1)
		Neoway_StartTimer(&neoway_to_send_at,21);

	return NEOWAY_TRUE;
}
/********************************************************************************************
 * Definition: Neo_ATSendError 
 * Parameter: void
 * Return value: void
 * Comments: if device got error response, call back to send same command again
 ********************************************************************************************/
void Neo_ATSendError(void)
{
	if(gNeo_at_info.at_send_state==AT_IDLE||gNeo_at_info.cmd==CMD_NULL)
	{
		return ;
	}
	if(gNeo_at_init_state_machine!=SM_INIT_OK && gNeo_at_info.cmd == CMD_INIT)//Initializing. Forbidden sending other commands.
	{
		Neoway_StopTimer(&neoway_at_send_overtime);
		gNeo_at_info.at_send_state=AT_IDLE;
		switch (gNeo_at_init_state_machine)
		{
			case SM_IDLE:
				break;
			case SM_AT_SENDING:
				gNeo_at_init_state_machine=SM_IDLE;
				break;
			case SM_CSQ_SENDING:
				gNeo_at_init_state_machine=SM_AT_SEND_OK;
				break;
			case SM_CREG_SENDING:
				gNeo_at_init_state_machine=SM_CSQ_SEND_OK;
				break;
			case SM_CSCS_SENDING:
				gNeo_at_init_state_machine=SM_CREG_SEND_OK;
				break;
			case SM_CNMI_SENDING:
				gNeo_at_init_state_machine=SM_CSCS_SEND_OK;
				break;
			case SM_IMEI_SENDING:
				gNeo_at_init_state_machine=SM_CNMI_SEND_OK;
				break;
			case SM_XIIC_SENDING:
				gNeo_at_init_state_machine=SM_IMEI_SEND_OK;
				break;
			case SM_XIIC_Q_SENDING:
				gNeo_at_init_state_machine=SM_XIIC_SEND_OK;
				break;
			case SM_UPDATETIME_SENDING:
				gNeo_at_init_state_machine=SM_XIIC_Q_SEND_OK;
				break;
			case SM_CIPGSMLOC_SENDING:
				gNeo_at_init_state_machine=SM_UPDATETIME_SEND_OK;
				break;
			default :
				break;
		}
		return ;
	}
	#if __HTTP_Server
	if(HTTP_Server_State!=SM_HTTP_INIT_OK)
	{
		Neoway_StopTimer(&neoway_at_send_overtime);
		gNeo_at_info.at_send_state=AT_IDLE;
		
		switch (HTTP_Server_State)
		{
			case SM_HTTP_DATA_SENDING:
				HTTP_Server_State=SM_HTTP_IDLE;
				break;
			case SM_HTTP_PORT_SENDING:
				HTTP_Server_State=SM_HTTP_IDLE;// SM_HTTP_DATA_SEND_OK;
				break;
			case SM_HTTP_SETUP_SENDING:
				HTTP_Server_State=SM_HTTP_IDLE; // SM_HTTP_PORT_SEND_OK;
				break;
			case SM_HTTP_ACTION_SENDING:
				HTTP_Server_State=SM_HTTP_IDLE; // SM_HTTP_SETUP_SEND_OK;
				break;
			case SM_HTTP_CLOSE_SENDING:
				HTTP_Server_State=SM_HTTP_IDLE; // SM_HTTP_ACTION_SEND_OK;
				break;	
		}
		return;
	}
	#endif
	switch (gNeo_at_info.cmd)
	{
		case CMD_CMGS:
		case CMD_TCPSEND:	
		case CMD_GPSPWR:
		case CMD_PHONE:
		case CMD_TCP0_SETUP:
		case CMD_TCP0:
		case CMD_AT:
			Neoway_StopTimer(&neoway_at_send_overtime);
			gNeo_at_info.at_send_state=AT_IDLE;
			break;
		default :
			break;
	}
	return ;
}
/********************************************************************************************
 * Definition: Neo_ATSendOK 
 * Parameter: void
 * Return value: void
 * Comments: if device got OK response, change the message Id for send next command
 ********************************************************************************************/
void Neo_ATSendOK(void)
{
	if(gNeo_at_info.at_send_state==AT_IDLE)// if AT command is not sent.
	{
		return ;//Exit directly
	}
	if(gNeo_at_info.cmd!=CMD_NULL)
	{
		if(gNeo_at_init_state_machine!=SM_INIT_OK && gNeo_at_info.cmd == CMD_INIT)//Initializing. Forbidden sending other commands.
		{
			Neoway_StopTimer(&neoway_at_send_overtime);
			gNeo_at_info.at_send_state=AT_IDLE;
			switch (gNeo_at_init_state_machine)
			{
				case SM_IDLE:
					break;
				case SM_AT_SENDING:
					gNeo_at_init_state_machine=SM_AT_SEND_OK;
					break;
				case SM_CSQ_SENDING:
					if(gNeo_signal_strong<5){
						gNeo_at_init_state_machine=SM_AT_SEND_OK;
					}
					else{
						gNeo_at_init_state_machine=SM_CSQ_SEND_OK;
					}
					break;
				case SM_CREG_SENDING:
					if(gNeo_register_state==0){
						gNeo_at_init_state_machine=SM_CSQ_SEND_OK;
					}
					else{
						gNeo_at_init_state_machine=SM_CREG_SEND_OK;
					}					
					break;
				case SM_CSCS_SENDING:
					gNeo_at_init_state_machine=SM_CSCS_SEND_OK;
					break;
				case SM_CNMI_SENDING:
					gNeo_at_init_state_machine=SM_CNMI_SEND_OK;
					break;
				case SM_IMEI_SENDING:
					gNeo_at_init_state_machine=SM_IMEI_SEND_OK;
					break;
				case SM_XIIC_SENDING:
					gNeo_at_init_state_machine=SM_XIIC_SEND_OK;
					break;
				case SM_XIIC_Q_SENDING:
					if(XIIC_register_state==1){
						gNeo_at_init_state_machine=SM_XIIC_Q_SEND_OK;
					}
					else{
						gNeo_at_init_state_machine=SM_IMEI_SEND_OK;
					}	
					break;
				case SM_UPDATETIME_SENDING:
					Neoway_us_delay(2000000);
					gNeo_at_init_state_machine=SM_UPDATETIME_SEND_OK;
					break;
				case SM_CIPGSMLOC_SENDING:
					Neoway_us_delay(3000000);	
					gNeo_at_init_state_machine=SM_CIPGSMLOC_SEND_OK;
					gNeo_at_init_state_machine=SM_INIT_OK;
					Neoway_UartSend(NEOWAY_UART_PORT_1,"SM_INIT_OK\r",11);
					#if __HTTP_Server
						HTTP_Server_State = SM_HTTP_IDLE;
					#endif
					break;	
				default :
					break;
			}
			return ;
		}
	}
	#if __HTTP_Server
	if(HTTP_Server_State!=SM_HTTP_INIT_OK)
	{
		Neoway_StopTimer(&neoway_at_send_overtime);
		gNeo_at_info.at_send_state=AT_IDLE;
		switch (HTTP_Server_State)
		{
			case SM_HTTP_DATA_SENDING:
				HTTP_Server_State=SM_HTTP_DATA_SEND_OK;
				break;
			case SM_HTTP_PORT_SENDING:
				HTTP_Server_State=SM_HTTP_PORT_SEND_OK;
				break;
			case SM_HTTP_SETUP_SENDING:
				if (RF_Id_count == Max_House_No || SEND_DATA == 1){ // should reach maximum number of houses
					SEND_DATA = 0;
					HTTP_Server_State=SM_HTTP_SETUP_SEND_OK;
				}
				else{
					HTTP_Server_State = SM_HTTP_ACTION_SEND_OK;
				}
				break;
			case SM_HTTP_ACTION_SENDING:
				HTTP_Server_State = SM_HTTP_ACTION_SEND_OK;
				RF_Id_count = 0;
				break;
			case SM_HTTP_CLOSE_SENDING:
				HTTP_Server_State = SM_HTTP_CLOSE_SEND_OK;
				HTTP_Server_State=SM_HTTP_INIT_OK;
				HTTP_Server_State=SM_HTTP_IDLE;
				break;
			default :
				break;
		}
		return;
	}
	#endif
	switch (gNeo_at_info.cmd)
	{
		case CMD_CMGS:
		case CMD_TCPSEND:
			if(gNeo_at_info.at_send_state==AT_SENDING_DATA)
			{
				Neoway_StopTimer(&neoway_at_send_overtime);
				gNeo_at_info.at_send_state=AT_IDLE;
			}
			break;
		case CMD_GPSPWR:
		case CMD_PHONE:
		case CMD_TCP0:
		case CMD_TCP0_SETUP:
		case CMD_AT:
			Neoway_StopTimer(&neoway_at_send_overtime);
			gNeo_at_info.at_send_state=AT_IDLE;
			break;
		default :
			break;
	}
	return ;
}
/********************************************************************************************
 * Definition: Neo_SendNextAT 
 * Parameter: void
 * Return value: void
 * Comments: change the message Id and send next AT command
 ********************************************************************************************/
void Neo_SendNextAT(void)
{
	if(gNeo_send_at_info_state.total_item!=0||gNeo_at_info.at_send_state!=AT_IDLE)
	{//Busy in initializing AT
		return ;
	}//AT is idle.
	if(gNeo_at_init_state_machine!=SM_INIT_OK)
	{
		switch (gNeo_at_init_state_machine)
		{
			case SM_IDLE:
				gNeo_at_init_state_machine=SM_AT_SENDING;
				Neo_SendAT(CMD_INIT, "at\r",3, NULL, 0);
				break;
			case SM_AT_SEND_OK:
				gNeo_at_init_state_machine=SM_CSQ_SENDING;
				Neo_SendAT(CMD_INIT, "at+csq\r",7, NULL, 0);
				break;
			case SM_CSQ_SEND_OK:
				gNeo_at_init_state_machine=SM_CREG_SENDING;
				Neo_SendAT(CMD_INIT, "at+creg\?\r",9, NULL, 0);
				break;
			case SM_CREG_SEND_OK:
				gNeo_at_init_state_machine=SM_CSCS_SENDING;
				Neo_SendAT(CMD_INIT, "at+cscs=\"ucs2\"\r",15, NULL, 0);
				break;
			case SM_CSCS_SEND_OK:
				gNeo_at_init_state_machine=SM_CNMI_SENDING;
				Neo_SendAT(CMD_INIT, "at+cnmi=2,2,0,0,0\r",18, NULL, 0);
				break;
			case SM_CNMI_SEND_OK:
				gNeo_at_init_state_machine=SM_IMEI_SENDING;
				Neo_SendAT(CMD_INIT, "at+cgsn\r",9, NULL, 0);
				break;
			case SM_IMEI_SEND_OK:
				gNeo_at_init_state_machine=SM_XIIC_SENDING;
				Neo_SendAT(CMD_INIT, "at+xiic=1\r",10, NULL, 0);
				break;
			case SM_XIIC_SEND_OK:
				gNeo_at_init_state_machine=SM_XIIC_Q_SENDING;
				Neo_SendAT(CMD_INIT, "at+xiic?\r",9, NULL, 0);
				break;
			case SM_XIIC_Q_SEND_OK:
				gNeo_at_init_state_machine=SM_UPDATETIME_SENDING;
				Neo_SendAT(CMD_INIT, "at+glts=1\r",strlen("at+glts=1\r"), NULL, 0);
				break;
			case SM_UPDATETIME_SEND_OK:
				gNeo_at_init_state_machine=SM_CIPGSMLOC_SENDING;
				Neo_SendAT(CMD_INIT, "at+cipgsmloc\r", strlen("at+cipgsmloc\r"), NULL, 0);
				break;
			default :
				break;
		}
		return ; 
	}
	#if __HTTP_Server
	if(HTTP_Server_State!=SM_HTTP_INIT_OK)
	{
		switch (HTTP_Server_State)
		{
			case SM_HTTP_IDLE:      // First At command
				HTTP_Server_State=SM_HTTP_DATA_SENDING;
				Neo_SendAT(CMD_HTTP, Server_URL, strlen(Server_URL), NULL, 0);				
				break;
			case SM_HTTP_DATA_SEND_OK:   	// Port number with HTTP comand				
				HTTP_Server_State=SM_HTTP_PORT_SENDING;
				Neo_SendAT(CMD_HTTP,"AT+HTTPPARA=port,8000\r",strlen("AT+HTTPPARA=port,8000\r"), NULL, 0);
				break;
			case SM_HTTP_PORT_SEND_OK: 		// HTTP set up Command
				HTTP_Server_State=SM_HTTP_SETUP_SENDING;
				Neo_SendAT(CMD_HTTP_SETUP,"AT+HTTPSETUP\r",strlen("AT+HTTPSETUP\r"), NULL, 0);
				break;
			case SM_HTTP_SETUP_SEND_OK: 	// HTTP Action Command
				HTTP_Server_State=SM_HTTP_ACTION_SENDING;
				memset(server_data, 0,sizeof(server_data));
				get_push_Data(server_data);
				memset(data_to_server, 0,sizeof(data_to_server));
				memcpy(data_to_server, server_data, strlen(server_data));
				sprintf(HttpAction_Buff,"AT+HTTPACTION=2,%d,2\r",strlen(data_to_server)); 
				Neo_SendAT(CMD_HTTP,HttpAction_Buff,strlen(HttpAction_Buff), data_to_server, strlen(data_to_server));
				Neoway_UartSend(NEOWAY_UART_PORT_1,data_to_server,strlen(data_to_server));
				break;
			case SM_HTTP_ACTION_SEND_OK:  // HTTP Close Command
				HTTP_Server_State=SM_HTTP_CLOSE_SENDING;
				Neo_SendAT(CMD_HTTP,"AT+HTTPCLOSE\r",14, NULL, 0);
				break;
			default :
				break;
		}
		return ;
	}
	#endif
}
#endif