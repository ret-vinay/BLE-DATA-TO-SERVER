
#include "neoway_openplatform.h"
#include "math.h"
#include "gps.h"

/****************************Used functions**************************************************/
char* StrStr(char *str, char *substr);
float my_a2f(char *p);
void extracting_gps_values(char* Rcv_str );
/********************************************************************************************/

/****************************GPS Variables Declaration**************************************************/
char *rmc=NULL;
/********************************************************************************************/

/****************************CONTROL FLAG'S**************************************************/
U16 GPS_Data_extr_Complet = 0;
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
 * Definition: my_a2f
 * Parameter: char *p
 * Return value: float
 *****************************************************************************/
float my_a2f(char *p) 
{
	// string_to_float_function
	// here i took another two   variables for counting the number of digits in mantissa
	int i, num = 0, num2 = 0, pnt_seen = 0, x = 0, y = 1; 
	float f1, f2, f3;
	for (i = 0; p[i]; i++)
	if (p[i] == '.') 
	{
	  pnt_seen = i;
	  break;
	}
	//Neoway_Print("pnt_seen=%d",pnt_seen); 
	for (i = 0; p[i]; i++)
	{
		if (i < pnt_seen) num = num * 10 + (p[i] - 48);
		else if (i == pnt_seen) continue;
		else 
		{
		  num2 = num2 * 10 + (p[i] - 48);
		  ++x;
		}
	}
	//Neoway_Print("num=%d num2=%d x=%d",num,num2,x);
	// it takes 10 if it has 1 digit ,100 if it has 2 digits in mantissa
	for(i = 1; i <= x; i++) 
	y = y * 10;
	f2 = num2 / (float) y;
	f3 = num + f2;
	return f3;
}
/*****************************************************************************
 * Definition: extracting_gps_values
 * Parameter: void
 * Return value: void
 *****************************************************************************/
void extracting_gps_values(char* Rcv_str )
{
	char  comma=',',valid,lat_dir,long_dir;
	int j=0,count=0,a=0,b=0,c=0,m;
	int d=0,e=0,g=0,h=0,k=0,z=0;
	static int i=0;
	float deg_flt,conv_deg_flt,min_flt;
	float conv_min_flt,my_lat,my_long;
/************************************MEMORY_CLEAR**************************************************************************************************/
	// Clear_Buff();
/**************************************************************************************************************************************************/	
/***********************************RMC CONVERTION************************************************************************************************/	
	// Neoway_UartSend(NEOWAY_UART_PORT_1,loc_buf,strlen(loc_buf));
	if((rmc=strstr(loc_buf,"$GNRMC"))){
		if(rmc[0]==0x24)
		{
			for(j=0;rmc[j]!= '*'; j++)//j<80;j++)
			{
				if(rmc[j]==0x0D)
					break;
				else
					RMC[j]=rmc[j];
			}
			RMC[j]='\0';
			// Neoway_UartSend(NEOWAY_UART_PORT_1,RMC,strlen(RMC));
			// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",strlen("\r"));
		}	
		for(i=0;RMC[i]!='\0';i++)
		{
			if(comma==RMC[i])
			{
				count++;
				//Neoway_Print("now comma position=%d %c\r",i,RMC[i]);
				//b=i;
				switch(count)
				{
					case 1:for(a=i+1;RMC[a]!=',';a++)						
							{
								if(RMC[a]=='.')
									break;
								time_buf[z]=RMC[a];
								z++;
								if(z==2 || z==5){
									time_buf[z]=':';
									z++;
								}
							}  
							time_buf[z]='\0';
							//Neoway_Print("time_buf=%s\r",time_buf);		
							sprintf(final_time ,"%s",time_buf);
							// Neoway_UartSend(NEOWAY_UART_PORT_1,final_time,strlen(final_time));
							z=0;
						break;				
				
					case 2:	valid=RMC[i+1];
							//Neoway_Print("valid_data=%c\r",valid);
							//Neoway_Print("now value at position A=%d",i+1);
						break;
							
					case 3:	for(b=i+1;RMC[b]!=',';b++)						
							{
								lat_buf[z]=RMC[b];
								z++;
							}  
							lat_buf[z]='\0';
							//Neoway_Print("lat_buf=%s\r",lat_buf);
							z=0;
						break;
					
					case 4: lat_dir=RMC[i+1];
							//Neoway_Print("lat_dir=%c\r",lat_dir);
						break;
							
					case 5: for(c=i+1;RMC[c]!=',';c++)
							{
								long_buf[z]=RMC[c];
								z++;	
							} 
							long_buf[z] ='\0';
							//Neoway_Print("long_buf=%s\r",long_buf);
							z=0;
						break;
						
					case 6:long_dir=RMC[i+1];
							//Neoway_Print("long_dir=%c\r",long_dir);
						break;
							
					case 7:	for(d=i+1;RMC[d]!=',';d++)
							{
								speed_buf[z]=RMC[d];
								z++;	
							} 
							speed_buf[z] ='\0';
							//Neoway_Print("speed_buf=%s\r",speed_buf);
							z=0;
						break;
					case 9: for(e=i+1;RMC[e]!=',';e++)
							{
								date_buf[z]=RMC[e];
								z++;	
								if(z==2){
									date_buf[z]='-';
									z++;
								}
								if(z==5){
									date_buf[z++]='-';
									date_buf[z++]='2';
									date_buf[z++]='0';
								}
							} 
							date_buf[z] ='\0';
							//Neoway_Print("*****date_buf=%s\r*****",date_buf);
							z=0;
						break;
				}
			}			   
		}
		/**************************************************************************************************************************************************/
		count=0; a=0;b=0;c=0;d=0;e=0;z=0;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(((valid=='A')&&(lat_dir=='N')&&(long_dir=='E'))||((valid=='A')&&(lat_dir=='N')&&(long_dir=='W'))||((valid=='A')&&(lat_dir=='S')&&(long_dir=='E'))||((valid=='A')&&(lat_dir=='S')&&(long_dir=='W')))
		{	
			//Neoway_Print("lat_buf=%s",lat_buf);
			//Neoway_Print("long_buf=%s",long_buf);
			//N10G7_GPS_SPEED = (int) atof(speed_buf);////////******_Speed_********/
			/***************************lat_convertion*********************************************************************************************************/
			degree[0]=lat_buf[0];
			degree[1]=lat_buf[1];
			degree[2]='.';
			degree[3]='\0';
			deg_flt=my_a2f(degree);
			//deg_flt=atoi(degree);
			//Neoway_Print("deg_flt=%d",deg_flt);
			memcpy(min,&lat_buf[2],(sizeof(lat_buf)-2));
			min[9]='\0';
			//Neoway_Print("min=%s",min);
			min_flt=my_a2f(min);
			conv_min_flt=min_flt/60;
			my_lat=deg_flt+conv_min_flt;
			/**************************************************************************************************************************************************/
			memset(degree,0,sizeof(degree));
			/***************************long_convertion********************************************************************************************************/
			degree[0]=long_buf[0];
			degree[1]=long_buf[1];
			degree[2]=long_buf[2];
			degree[3]='.';
			degree[4]='\0';
			//Neoway_Print("degree=%s",degree);
			deg_flt=my_a2f(degree);
			//Neoway_Print("deg_flt=%f",deg_flt);
			memcpy(min,&long_buf[3],(sizeof(long_buf)-3));
			min[9]='\0';
			//Neoway_Print("min=%s",min);
			min_flt=my_a2f(min);
			conv_min_flt=min_flt/60;
			//Neoway_Print("conv_min_flt=%f",conv_min_flt);
			my_long=deg_flt+conv_min_flt;
			/**************************************************************************************************************************************************/
			memset(degree,0,sizeof(degree));
			/*************************************************Distance calculation**************************************************************************/
			if(start_loc_flag == 0){
				dLat1=(double)my_lat;
				dLong1=(double)my_long;
				start_loc_flag = 1;
			}
			else if(start_loc_flag == 1){
				if(dLat2 != my_lat){
					dLat2=(double)my_lat;
				}
				else{
					dLat2=dLat2;
				}
				if(dLong2 != my_long){
					dLong2=(double)my_long;
				}
				else{
					dLong2=dLong2;
				}
			}
			final_distance= distance(dLat1, dLong1, dLat2, dLong2, 'K');
			memset(distance_buf,0,sizeof(distance_buf));
			sprintf(distance_buf,"\"Distance\":\"%lfkm\"",final_distance);
			// Neoway_UartSend(0,distance_buf,strlen(distance_buf));
			/********************************get system time*******************************************/
			Neoway_GetTime(&rtc_time);		//get system time	
			sprintf(time_temp,"%d:%d:%d",rtc_time.rtc_hour,rtc_time.rtc_min,rtc_time.rtc_sec);
			/*****************FINAL_DATA_DISPLAY***************************************************************************************************************/
			//sprintf(final_speed,"SPEED=%s",speed_buf);
			sprintf(final_lat , "\"LAT\":\"%f\"", my_lat);		//float to string
			sprintf(final_long, "\"LONG\":\"%f\"", my_long);	//float to string 
			sprintf(final_GMT , "\"TIMESTAMP\":\"%s %s\"",date_buf,final_time);//  time_temp
			// sprintf(final_ble, "\"HOUSEID\":\"%s\"",ble_data);
			/**************************************************************************************************************************************************/
			//sprintf(System_ID,"system_IMEI=%s",Module_IMEI_Number);
			
			BAT_Percent= GET_BAT_VOLTAGE(); /// Get the Remained Battery Percentage
			sprintf(Remained_BAT_Percent, "BAT=%d" ,BAT_Percent);
			//Neoway_UartSend(NEOWAY_UART_PORT_2,Remained_BAT_Percent,strlen(Remained_BAT_Percent));
			//Neoway_UartSend(NEOWAY_UART_PORT_2,"\n",strlen("\n"));
			// sprintf(SD_Card_FileName, "%s.txt",date_buf);
			//strcpy(SD_Card_FileName,"220318.txt");			
			/********************************DATA_TO_SERVER****************************************************************************************************/

			// sprintf(TrackDate,  "\"trackDt\" : \"%s %s\" ",date_buf,time_buf);
			//sprintf(Tripcode,   "\"tripCode\" : \"%s\"", Module_IMEI_Number);
			//sprintf(createdBy,  "\"createdBy\" : \"%s\"", Module_IMEI_Number);
			//sprintf(updatedBy,  "\"updatedBy\" : \"%s\"", Module_IMEI_Number);		
			//sprintf(data_to_server,"{%s,%s,%s,%s,%s,%s,%s,%s}",companyBranchId,TrackDate,final_long,final_lat,Tripcode,Active,createdBy,updatedBy);
			// //sprintf(data_to_server,"{%s,%s,%s}",final_lat,final_long,final_GMT);
			memset(data_to_server,0,sizeof(data_to_server));
			sprintf(data_to_server,"{%s,%s,%s,%s,%s,%s,%s}",Tripcode,app_version,final_lat,final_long,final_GMT,acc_loc_buf,distance_buf);
			// Neoway_UartSend(NEOWAY_UART_PORT_1,data_to_server,strlen(data_to_server));
			// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",strlen("\r"));
			/**************************************************************************************************************************************************/
			GPS_Data_extr_Complet = 1;
			GSM_GPS_CONNECTED = 0;
			if(GPS_CONNECTED == 0)
				GPS_CONNECTED = 1;
		}
	}
	else{	
		//sprintf(System_ID,"system_IMEI=%s",Module_IMEI_Number);
		
		BAT_Percent = GET_BAT_VOLTAGE(); /// Get the Remained Battery Percentage
		sprintf(Remained_BAT_Percent, "BAT=%d" ,BAT_Percent);
		
		gsm_loc_buf_extrn(latlng_buf);		
		
		Neoway_GetTime(&rtc_time);		//get system time	
		// Neoway_Print("current time is %d:%d:%d",rtc_time.rtc_hour,rtc_time.rtc_min,rtc_time.rtc_sec);
		// Neoway_Print("current date is %d:%d:%d",rtc_time.rtc_day,rtc_time.rtc_mon,rtc_time.rtc_year);
		sprintf(time_temp,"%d:%d:%d",rtc_time.rtc_hour,rtc_time.rtc_min,rtc_time.rtc_sec);
		sprintf(date_temp,"%d:%d:20%d",rtc_time.rtc_day,rtc_time.rtc_mon,rtc_time.rtc_year);
		
		strcpy(date_buf,date_temp);
		// Neoway_Print("time_temp is %s",time_temp);
		// Neoway_Print("date_temp is %s",date_temp);
		// Neoway_Print("date_buf is %s",date_buf);
		// Neoway_UartSend(NEOWAY_UART_PORT_2,Remained_BAT_Percent,strlen(Remained_BAT_Percent));
		// Neoway_UartSend(NEOWAY_UART_PORT_2,"\n",strlen("\n"));
		// sprintf(SD_Card_FileName, "%s.txt",date_buf);
		// strcpy(SD_Card_FileName,"220318.txt");
		sprintf(final_lat , "\"LAT\":\"%s\"",latt_buf);		//float to string
		sprintf(final_long, "\"LONG\":\"%s\"",lng_buf);	//float to string 
		sprintf(final_GMT , "\"TIMESTAMP\":\"%s %s\"",date_temp,time_temp);
		// sprintf(TrackDate , "\"trackDt\" : \"NA NA\""); 
		//sprintf(Tripcode,   "\"tripCode\" : \"NA\"" );
		//sprintf(createdBy,  "\"createdBy\" : \"NA\"" );
		//sprintf(updatedBy,  "\"updatedBy\" : \"NA\"" );
		//sprintf(data_to_server,"{%s,%s,%s,%s,%s,%s,%s,%s}",companyBranchId,TrackDate,final_long,final_lat,Tripcode,Active,createdBy,updatedBy);
		// // sprintf(data_to_server,"{%s,%s,%s}",final_lat,final_long,final_GMT);
		memset(data_to_server,0,sizeof(data_to_server));
		sprintf(data_to_server,"{%s,%s,%s,%s,%s,%s}",Tripcode,app_version,final_lat,final_long,final_GMT,acc_loc_buf);
		// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",strlen("\r"));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,data_to_server,strlen(data_to_server));
		// Neoway_UartSend(NEOWAY_UART_PORT_1,"\r",strlen("\r"));
		GPS_Data_extr_Complet = 1;
		if(GPS_CONNECTED == 1)
			GPS_CONNECTED = 0;
	}
}