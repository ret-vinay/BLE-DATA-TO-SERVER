#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"

/****************************Used functions***************************************************/
extern void str_send2uart(char *buffer_addr);
extern U32 GET_BAT_VOLTAGE(void);
extern void init_interrupt(void);
/********************************************************************************************/
/**************Battery Variables and Function Declarations***********************************/ 
typedef enum{
	BAT_LOW=0,
	BAT_HIGH=1,
}BAT_VOLT_LEVEL;

extern BAT_VOLT_LEVEL battery_voltage;
extern float Bat_Voltage;
extern unsigned int BAT_Percent,Current_percentage,Previous_percentage;
/********************************************************************************************/
/****************************CONTROL FLAG'S**************************************************/
extern U16 GPS_Data_extr_Complet;
/********************************************************************************************/
#endif