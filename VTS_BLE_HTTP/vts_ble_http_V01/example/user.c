#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"
#include "user.h"

/******************************RTC Function VARIABLES****************************************/
NeowayRtcStruct  rtc_time; // declare to get Real Time Clock data
/********************************************************************************************/
/****************************CONTROL FLAG'S**************************************************/
U16 GPS_Data_extr_Complet = 0;
/********************************************************************************************/
/****************************Used functions**************************************************/
void str_send2uart(char *buffer_addr);
U32 GET_BAT_VOLTAGE(void);
void init_interrupt(void);
/**************Battery Variables and Function Declarations***********************************/ 
BAT_VOLT_LEVEL battery_voltage = BAT_HIGH;
float Bat_Voltage=0;
unsigned int BAT_Percent=0,Current_percentage=0,Previous_percentage=0;
/********************************************************************************************/
/*********************************************************************************************
 * Definition: send2uart
 * Parameter: char *buffer_addr  // address of the buffer to print
 * Return value: void
 ********************************************************************************************/
void str_send2uart(char *buffer_addr)
{
	U8 time_stamp[1024];
	
	memset(time_stamp, 0, sizeof(time_stamp));
	Neoway_GetTime(&rtc_time);		//get system time	
	sprintf(time_stamp,"%d/%d/%d: %s",rtc_time.rtc_hour,rtc_time.rtc_min,rtc_time.rtc_sec,buffer_addr);
	Neoway_UartSend(NEOWAY_UART_PORT_1,time_stamp,strlen(time_stamp));		
	Neoway_UartSend(NEOWAY_UART_PORT_1,"\n",1);
}
/********************************************************************************************
 * Definition: init_interrupt
 * Parameter: void
 * Return value: void
 *******************************************************************************************/
void init_interrupt(void)
{
	Neoway_InterruptInit(25,NEOWAY_INT_15);                   //Set GPIO_25 as interruption 15.
	Neoway_InterruptSetDebounceTime(NEOWAY_INT_15,40);		 //Set interruption debounce time to 20 ticks.
	Neoway_InterruptSetPolarity(NEOWAY_INT_15,NEOWAY_FALSE);   //Set interruption polarity as rising edge or high level.
	Neoway_InterruptSetTriggerMode(NEOWAY_INT_15,NEOWAY_FALSE);//Edge triggered interrupt.NEOWAY_TRUE
}
/*****************************************************************************
 * Definition: GET_BAT_VOLTAGE
 * Parameter: void
 * Return value: unsigned int
 *****************************************************************************/
U32 GET_BAT_VOLTAGE(void)
{
	// Read ADC and Calculating the Battery Voltage
	unsigned int adc0_reading=0;
	static First_Time_Calculation=0;
	
	adc0_reading = Neoway_ReadAdcValue(0);
	Neoway_Print("adc0_reading=%d",adc0_reading);
	Bat_Voltage = (adc0_reading/2797.0)*2.8*2.02;
	Neoway_Print("Bat_Voltage=%f",Bat_Voltage);
	if(Bat_Voltage < 3.5)//(adc0_reading < 1750)
		Bat_Voltage=3.5;
	if(Bat_Voltage > 4.12)//(adc0_reading > 2065)
		Bat_Voltage=4.12;
	Neoway_Print("Bat_Voltage=%f",Bat_Voltage);
	Current_percentage = (int)(((Bat_Voltage-3.5)/(4.12-3.5))*100);
	Neoway_Print("Current_percentage=%d",Current_percentage);
	Neoway_Print("NEOWAY_GPIO_30=%d",Neoway_GpioRead(NEOWAY_GPIO_30));
	if(First_Time_Calculation==0){
		First_Time_Calculation=1;
		Previous_percentage = Current_percentage;
		return Current_percentage;	
	}
	if(Neoway_GpioRead(NEOWAY_GPIO_30) == 0){
		if(Current_percentage >= Previous_percentage){
		  Previous_percentage = Current_percentage;
		  if(Current_percentage > 30 && battery_voltage == BAT_LOW){
				battery_voltage = BAT_HIGH;
			}			
		  return Current_percentage;
		}
		else{
			return Previous_percentage;
		}
	}
	else if(Neoway_GpioRead(NEOWAY_GPIO_30) == 1){
		if( (Current_percentage <= Previous_percentage) ){  //&& ( (Previous_percentage-Current_percentage)<5) ){
		    Previous_percentage = Current_percentage;
			if(Current_percentage < 30 && battery_voltage == BAT_HIGH){
				battery_voltage = BAT_LOW;				
			}
			return Current_percentage;
		}
		else{
			return Previous_percentage;
		}
	}
}
#endif