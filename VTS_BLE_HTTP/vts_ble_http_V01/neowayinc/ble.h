#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"
/****************************Used functions***************************************************/
extern void extracting_ble(char *);
extern char get_push_Data(char *);
extern char push_Data(char *, char *);
extern char* strstr(char *str, char *substr);
/********************************************************************************************/
/****************************variable declaration***************************************************/
extern U8 ble_data[50],ble_data1[100],server_dat_buf[1000];
extern U16 first_id;
extern NeowayRtcStruct  rtc_time;
/********************************************************************************************/
/****************************CONTROL FLAG'S**************************************************/
extern U16 BLE_Data_extr_Complet;
extern U16 RF_Id_count;// control flag related to house count
/********************************************************************************************/
#endif