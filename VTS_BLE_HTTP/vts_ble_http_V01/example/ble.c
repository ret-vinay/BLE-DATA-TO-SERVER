#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"
#include "ble.h"

/****************************Used functions***************************************************/
void extracting_ble(char *);
char get_push_Data(char *);
char push_Data(char *, char *);
char* strstr(char *str, char *substr);
/********************************************************************************************/
/****************************variable declaration********************************************/
U8 ble_data[50]={0},ble_data1[100]={0},server_dat_buf[1000]={0};
U16 first_id=0;
/********************************************************************************************/
/****************************CONTROL FLAG'S**************************************************/
U16 BLE_Data_extr_Complet = 0;
U16 RF_Id_count=0;// control flag related to house count
/********************************************************************************************/
/*****************************************************************************
 * Definition: strstr
 * Parameter: char *str1, char *str2
 * Return value: char
 *****************************************************************************/
char* strstr(char *str1, char *str2)
{
	// String_string_compare_driver_function
	while(*str1 != '\0')
    {
        char *p = (char*)str1;
        char *q = (char*)str2;
        char *res = NULL;
        if(*p == *q)
        {
            res = p;
            while(*p && *q && *p++ == *q++);

            if(*q == '\0')
                return res;
        }
        str1++;
    }
    return NULL;
}
/*****************************************************************************
 * Definition: extracting_ble // extreaction of location data by GSM Network
 * Parameter: void
 * Return value: void
 *****************************************************************************/
void extracting_ble(char *loc_ble)
{
	U8 *ptr=NULL;
	U8 RFid[15]={0},Previous_RFid[15]={0}, timestamp[30]={0};
	U16 j=0,k=0,l=0,m=0;
	
	// Neoway_UartSend(NEOWAY_UART_PORT_1,loc_ble,strlen(loc_ble));
	ptr=loc_ble;
	if(ptr[0]==0x0D)
	{
		for(j=0;ptr[j]!= '\0'; j++)
		{
			if(ptr[j]==0x0D){
			}
			else if(ptr[j]=='.'){
				ble_data[k++]=',';
			}
			else{				
				ble_data[k++]=ptr[j];
			}
			if((j >= 1) && (j < 9)){
				RFid[l++]=ptr[j];
			}
			if((j >= 10) && (ptr[j] != '\0')){
				timestamp[m++]=ptr[j];
			}
		}
		ble_data[k]='\0';
		RFid[l] = '\0';
		timestamp[m] = '\0';
		if( strlen(timestamp) > 11 ){
			sprintf(ble_data1,"\{\"Id\":\"%s\",\"TimeStamp\":\"%s\"\}",RFid,timestamp);
		}
		else{
			Neoway_GetTime(&rtc_time);		//get system time
			memset(timestamp, 0,sizeof(timestamp));
			sprintf(timestamp,"%d:%d:%d,%d-%d-%d",rtc_time.rtc_hour,rtc_time.rtc_min,rtc_time.rtc_sec,rtc_time.rtc_day,rtc_time.rtc_mon,rtc_time.rtc_year);
			sprintf(ble_data1,"\{\"Id\":\"%s\",\"TimeStamp\":\"%s\"\}",RFid,timestamp);
		}
		// Neoway_UartSend(NEOWAY_UART_PORT_1,ble_data,strlen(ble_data));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",1);
		// Neoway_UartSend(NEOWAY_UART_PORT_1,RFid,strlen(RFid));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",1);
		// Neoway_Print("length=%d\r",strlen(RFid));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,timestamp,strlen(timestamp));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",1);
		// Neoway_Print("length=%d\r",strlen(timestamp));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,ble_data1,strlen(ble_data1));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",1);
		if(first_id == 0){
			first_id = 1;
			// Neoway_Print("first_Time_id");
			// Neoway_Print("current RFid = %s",RFid);
			// Neoway_Print("Previous_RFid = %s",Previous_RFid);
			memcpy(Previous_RFid,RFid,strlen(RFid));						
			push_Data(ble_data1, RFid);
		}
		else if(strcmp(Previous_RFid,RFid) != 0){
			// Neoway_Print("next_Time_id");
			// Neoway_Print("current RFid = %s",RFid);
			// Neoway_Print("Previous_RFid = %s",Previous_RFid);
			memcpy(Previous_RFid,RFid,strlen(RFid));
			push_Data(ble_data1, RFid);
		}
		else{
			Neoway_Print("not does anything");
		}
	}
	ptr=NULL;
	BLE_Data_extr_Complet = 0;
}
/*****************************************************************************
 * Definition: push_Data // extreaction of location data by GSM Network
 * Parameter: void
 * Return value: void
 *****************************************************************************/
char push_Data(char *loc_ble, char *id)
{
	U8 *ptr=NULL;
	ptr=server_dat_buf;
	// Neoway_Print("called push_Data function");
	if(strlen(ptr) == 0)
	{
		RF_Id_count += 1;
		Neoway_Print("RF_Id_count = %d", RF_Id_count);
		// Neoway_Print("server_dat_buf length is equal to 0");
		// Neoway_Print("loc_ble = %s",loc_ble);
		strcat(server_dat_buf,loc_ble);
		Neoway_Print("server_dat_buf = %s",server_dat_buf);
	}
	else{
		// Neoway_Print("server_dat_buf length is not equal to 0");
		// Neoway_Print("loc_ble = %s",loc_ble);
		if(strstr(server_dat_buf, id) == NULL){
			RF_Id_count += 1;
			Neoway_Print("RF_Id_count = %d", RF_Id_count);
			Neoway_Print("this card data is not exists & data is appending...");
			server_dat_buf[strlen(server_dat_buf)]=',';
			strcat(server_dat_buf,loc_ble);
			Neoway_Print("server_dat_buf = %s",server_dat_buf);
		}
		else{
			Neoway_Print("this card data is exists!!");
		}
	}
	ptr=NULL;	
	// Neoway_UartSend(NEOWAY_UART_PORT_1,server_dat_buf,strlen(server_dat_buf));
	// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",1);
}
/*****************************************************************************
 * Definition: get_push_Data // extreaction of location data by GSM Network
 * Parameter: void
 * Return value: void
 *****************************************************************************/
char get_push_Data(char *loc_ble)
{
	memset(loc_ble, 0,sizeof(loc_ble));
	sprintf(loc_ble,"\{ \"data\":\[ %s \] \}\r",server_dat_buf);
	// Neoway_UartSend(NEOWAY_UART_PORT_1,loc_ble,strlen(loc_ble));
	// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",1);
	memset(server_dat_buf, 0,sizeof(server_dat_buf));
}
#endif