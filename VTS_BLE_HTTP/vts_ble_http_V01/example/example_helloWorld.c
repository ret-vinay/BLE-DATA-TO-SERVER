#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"
#include "neoway_message.h"
#include "user.h"
#include "ble.h"
#include "fota.h"

#define   GPS_LED_PIN     13
#define   BAT_LED_PIN     21

/****************************UART BUFFER'S***************************************************/
U8 Uart_buf1[1024],Uart_buf2[1024],Uart_buf3[256];
U8 Loc_Uart_buf1[1024],Loc_Uart_buf2[1024],Loc_Uart_buf3[1024];
U16 Uart_buf1_len = 0,Uart_buf2_len = 0,Uart_buf3_len = 0;
/********************************************************************************************/

/****************************CONTROL FLAG'S**************************************************/
U16 GPS_CONNECTED = 1, GSM_GPS_CONNECTED = 0,FOTA_LED_FLAG = 1, SEND_DATA = 0;
/********************************************************************************************/

/****************************Used functions***************************************************/
void Read_uart_data();
/********************************************************************************************/

/****************************TIMER'S DECLARATION**********************************************/
NeowayTimerId LEDGlow_Timer_Task1,UartRead_timer_task2;
/********************************************************************************************/

/********************************************************************************************
 * Definition: Neoway_UserInit
 * Parameter: void
 * Return value: void
 * Comments: initializing UART,GPIO'S,Timers assignment
 ********************************************************************************************/
void Neoway_UserInit(void)
{
	Neoway_us_delay(500000); // 5 seconds delay
	
	Neoway_StopWatchdog();
	
	Neoway_UartOpen(NEOWAY_UART_PORT_1);
	Neoway_SetBaudrate(NEOWAY_UART_PORT_1, NEOWAY_UART_BAUD_9600);
	
	Neoway_UartOpen(NEOWAY_UART_PORT_2);
	Neoway_SetBaudrate(NEOWAY_UART_PORT_2, NEOWAY_UART_BAUD_9600);
	
	Neoway_UartOpen(NEOWAY_UART_PORT_3);
	Neoway_SetBaudrate(NEOWAY_UART_PORT_3,NEOWAY_UART_BAUD_9600);
	
	Neo_AtInit();
	Neoway_MessageTimersInit();
	init_interrupt();
	
	Neoway_GpioModeConfigure(BAT_LED_PIN,NEOWAY_MODE_GPIO);   //BAT Pin Set output 
	Neoway_GpioDirectionConfigure(BAT_LED_PIN,1);
	Neoway_GpioWrite(BAT_LED_PIN,1);				// device ON indication without battery
	
	Neoway_InitTimer(&LEDGlow_Timer_Task1,NEOWAY_MOD_USER3);
	Neoway_StartTimer(&LEDGlow_Timer_Task1,216);
	
	Neoway_InitTimer(&UartRead_timer_task2,NEOWAY_MOD_USER2);
	Neoway_StartTimer(&UartRead_timer_task2,216);
}
/********************************************************************************************
 * Definition: Neoway_UserTask1
 * Parameter: NeowayMsgTypeStruct msg_type,NeowayModuleTypeEnum mod_type
 * Return value: void
 * Comments: Running USERTASK1 for LED Blinking
 ********************************************************************************************/
void Neoway_UserTask1(NeowayMsgTypeStruct msg_type,NeowayModuleTypeEnum mod_type)
{
	// Neoway_Print("Neoway_UserTask1 running");
	switch(msg_type.msg_id)
	{
		case NEOWAY_MSG_ID_TIMER_EXPIRY:
			{	
				NeowayTimerId * current_time_id=Neoway_GetTimerId(msg_type);
				/**************check the current timer valid or not***************/
				if(Neoway_IsTimeExpiredValid(current_time_id)!=NEOWAY_RET_OK)
				{
					Neoway_UartSend(NEOWAY_UART_PORT_1,"not valid timer\r",7);
					break;
				}
				if(current_time_id==&neoway_at_stream)	//Initialize the AT commands for sending.
				{
					// Neoway_Print("Calling Neo_SendNextAT");					
					Neo_SendNextAT();
					// GPS_Data_extr_Complet=0;					
					Neoway_StartTimer(&neoway_at_stream,216); /*New 27*********** 216 Change Here **************/
				}
				else if (current_time_id==&neoway_to_send_at)
				{
					// Neoway_Print("Calling Neo_ATSendCmd");
					Neo_ATSendCmd();
					if(gNeo_send_at_info_state.total_item!=0)
						
					Neoway_StartTimer(&neoway_to_send_at,216); /*New 27*********** 216 Change Here **************/
				}
				else if (current_time_id==&neoway_at_send_overtime)
				{
					// Neoway_Print("Calling Neo_ATSendOvertime,SET");
					Neo_ATSendOvertime();
				}			
			}
			break;
		case NEOWAY_MSG_ID_EIND_NOTIFY: //Start to send the initialization AT commands.
			Neoway_StartTimer(&neoway_at_stream,21);//Start to send AT commands.
			break;
		case NEOWAY_MSG_ID_DATA_SEND_REQUIRE:
			gNeo_MSG_send_count--;
			// Neoway_Print("Calling Neo_ATSendData");
			Neo_ATSendData(); 
			break;
		case NEOWAY_MSG_ID_AT_SEND_OK:		
			// Neoway_Print("Calling Neo_ATSendOK");
			Neo_ATSendOK();	
			break;
		case NEOWAY_MSG_ID_AT_SEND_ERROR:	
			// Neoway_Print("Calling Neo_ATSendError");
			Neo_ATSendError();
			break;
		case NEOWAY_FOTA_START_NOTIFY:
			// Neoway_Print("Call FOTA function Here");
			// update_available();
			Neoway_StartTimer(&neoway_at_stream,21);// Start to send AT commands.
			break;
		case NEOWAY_FOTA_END_NOTIFY:	
			// Neoway_Print("End of FOTA function");
			Neoway_StartTimer(&neoway_at_stream,21);// Start to send AT commands.
			break;
		default :
			break;
	}
}
/*****************************************************************************
 * Definition: Neoway_UserTask2
 * Parameter: NeowayMsgTypeStruct msg_type,NeowayModuleTypeEnum mod_type
 * Return value: void
 * Comments: Running USERTASK2 to read the Data from UART for every 0.7 seconds
 *****************************************************************************/
void Neoway_UserTask2(NeowayMsgTypeStruct msg_type,NeowayModuleTypeEnum mod_type)
{
	// Neoway_Print("Neoway_UserTask2 running");
	switch(msg_type.msg_id)
	{
		case NEOWAY_MSG_ID_TIMER_EXPIRY:
			{	
				NeowayTimerId * current_time_id=Neoway_GetTimerId(msg_type);
				/**************check the current timer valid or not***************/
				if(current_time_id==&UartRead_timer_task2)
				{
					if(Neoway_IsTimeExpiredValid(&UartRead_timer_task2)==NEOWAY_RET_OK)
					{						
						Read_uart_data();
						Neoway_StartTimer(&UartRead_timer_task2,160);
					}					
				}				
			}
			break;
			break;
		default :
			break;
	}
}
/*****************************************************************************
 * Definition: Neoway_UserTask3
 * Parameter: NeowayMsgTypeStruct msg_type,NeowayModuleTypeEnum mod_type
 * Return value: void
 * Comments: Running USERTASK3 for sending the AT commands
 *****************************************************************************/
void Neoway_UserTask3(NeowayMsgTypeStruct msg_type,NeowayModuleTypeEnum mod_type)
{
	// Neoway_Print("Neoway_UserTask3 running");
	switch(msg_type.msg_id)
	{
		case NEOWAY_MSG_ID_TIMER_EXPIRY:
			{
				NeowayTimerId * current_time_id=Neoway_GetTimerId(msg_type);//Obtain the ID of the timer which times out.
				/**************check the current timer valid or not***************/
				if(current_time_id==&LEDGlow_Timer_Task1)
				{
					if(Neoway_IsTimeExpiredValid(&LEDGlow_Timer_Task1)==NEOWAY_RET_OK)
					{
						/* Neoway_Print("****LEDGlow_Timer_Task1 Running****");*/
						if(GPS_CONNECTED == 1 || GSM_GPS_CONNECTED == 1){
							Neoway_GpioWrite(GPS_LED_PIN,1);
							Neoway_us_delay(500000);
							Neoway_GpioWrite(GPS_LED_PIN,0);
							Neoway_us_delay(500000);
						}
						if(FOTA_LED_FLAG == 1){
							Neoway_GpioWrite(BAT_LED_PIN,1);
							Neoway_us_delay(500000);
							Neoway_GpioWrite(BAT_LED_PIN,0);
							Neoway_us_delay(500000);
						}
						else {
							Neoway_GpioWrite(BAT_LED_PIN,1);
						}
						if(battery_voltage == BAT_LOW){
							Neoway_GpioWrite(BAT_LED_PIN,1);
							Neoway_us_delay(40000);
							Neoway_GpioWrite(BAT_LED_PIN,0);
							Neoway_us_delay(40000);
						}
						else if(battery_voltage == BAT_HIGH){
							Neoway_GpioWrite(BAT_LED_PIN,1);
						}					
					}
					Neoway_StartTimer(&LEDGlow_Timer_Task1,20);					
				}
				break;
			}
		default :
			break;
	}
}
/*********************************************************************************************
 * Definition: Read_uart_data
 * Parameter: void  			// address of the buffer to print
 * Return value: void
 *********************************************************************************************/
void Read_uart_data(void)
{
	// Neoway_Print("calling Read_uart_data function");
	memset(Loc_Uart_buf1,0,sizeof(Loc_Uart_buf1));
	memcpy(Loc_Uart_buf1,Uart_buf1,strlen(Uart_buf1));
	// str_send2uart(Loc_Uart_buf1);
	if(GPS_Data_extr_Complet == 0)
	{
		GPS_Data_extr_Complet = 1;
		memset(Loc_Uart_buf2,0,sizeof(Loc_Uart_buf2));
		memcpy(Loc_Uart_buf2,Uart_buf2,strlen(Uart_buf2));
		// str_send2uart(Loc_Uart_buf2);							
	}
	else{
		// Neoway_Print("GPS_Data_extraction_Not_Complete");
	}
	if(strncmp(Loc_Uart_buf3,Uart_buf3,10) !=0) // && (BLE_Data_extr_Complet == 0))
	{
		// BLE_Data_extr_Complet = 1;
		memset(Loc_Uart_buf3,0,sizeof(Loc_Uart_buf3));
		memcpy(Loc_Uart_buf3,Uart_buf3,30);
		// str_send2uart(Loc_Uart_buf3);
		extracting_ble(Loc_Uart_buf3);
	}
	else{
		// Neoway_Print("Same RF_id");
	}
}
/********************************************************************************************
 * Definition: Neoway_IntResponse
 * Parameter: NeowayIntNumEnum int_no,NeowayModuleTypeEnum mod_id
 * Return value: void
 *******************************************************************************************/
void Neoway_IntResponse(NeowayIntNumEnum int_no,NeowayModuleTypeEnum mod_id)
{
	if(int_no==NEOWAY_INT_15)
	{
		SEND_DATA = 1;
		// Neoway_Print("NEOWAY_INT_15");
		// Neoway_SendMsgTask(mod_id,NEOWAY_MOD_USER1,NEOWAY_MSG_ID_INT_NOTIFY7,NULL,0); //Response to interruption when it happens,and send message to task1.
	}
}
/********************************************************************************************
 * Definition: Neoway_UartReceive
 * Parameter: NeowayUartPortEnum port,U8 *buffer,U16 lenth, NeowayModuleTypeEnum mod_id
 * Return value: void
 *******************************************************************************************/
void Neoway_UartReceive(NeowayUartPortEnum port,U8 *buffer,U16 lenth, NeowayModuleTypeEnum mod_id)
{
	if(port==NEOWAY_UART_PORT_1)	// for System Use, Sends Response for AT Commands
	{
		memset(Uart_buf1, 0, sizeof(Uart_buf1));
		memcpy(Uart_buf1, buffer, lenth);
		Uart_buf1_len = lenth;
	}
	if(port==NEOWAY_UART_PORT_2)	// for GPS Use, Receives Response from GPS
	{
		memset(Uart_buf2, 0, sizeof(Uart_buf2));
		memcpy(Uart_buf2, buffer, lenth);
		Uart_buf2_len = lenth;
	}
	if(port==NEOWAY_UART_PORT_3)	// for User Purpose, Sends Required comments
	{
		memset(Uart_buf3, 0, sizeof(Uart_buf3));
		memcpy(Uart_buf3, buffer, lenth);
		Uart_buf3_len = lenth;
		// Neoway_Print("Uart_buf3 = %s",Uart_buf3);
	}
}
/********************************************************************************************
 * Definition: Neoway_VirtualUartReceive
 * Parameter: U8 *buff_ptr, U16 len, NeowayModuleTypeEnum mod_id
 * Return value: void
 *******************************************************************************************/
void Neoway_VirtualUartReceive(U8 *buff_ptr, U16 len, NeowayModuleTypeEnum mod_id)
{
	Neo_AT_ReceiveManage(buff_ptr,len,mod_id);// Process the UART receive function.
}
/********************************************************************************************
 * Definition: Neoway_RegisterCallbackFunction
 * Parameter: void
 * Return value: void
 *******************************************************************************************/
void Neoway_RegisterCallbackFunction(void)
{
	Neoway_RegisterCallBack(NEOWAY_KB_ID_USER_TASK_1,(U32)Neoway_UserTask1);// Rregister the UserTask1 response function
	Neoway_RegisterCallBack(NEOWAY_KB_ID_USER_TASK_2,(U32)Neoway_UserTask2);// Rregister the UserTask2 response function
	Neoway_RegisterCallBack(NEOWAY_KB_ID_USER_TASK_3,(U32)Neoway_UserTask3);// Rregister the UserTask3 response function
	Neoway_RegisterCallBack(NEOWAY_KB_ID_UART_RECEIVE,(U32)Neoway_UartReceive);// Rregister the Uart response function
	Neoway_RegisterCallBack(NEOWAY_KB_ID_FTP_UPDATE,(U32)Neoway_FtpUpdate);// Rregister the FOTA response function
	Neoway_RegisterCallBack(NEOWAY_KB_ID_INT_RESPONSE,(U32)Neoway_IntResponse);// Rregister the interruption response function
	Neoway_RegisterCallBack(NEOWAY_KB_ID_VIRTUAL_UART_RECEIVE,(U32)Neoway_VirtualUartReceive);// Rregister the Virtual Uart response function
}
#endif