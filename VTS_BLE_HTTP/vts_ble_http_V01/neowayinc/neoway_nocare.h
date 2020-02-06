/*==========================================================================
 |               Neoway OpenCPU --  User API
 |
 |              Copyright (c) 2013 Neoway Ltd.
 |
 |--------------------------------------------------------------------------
 | File Description
 | ----------------
 |      Basic data type definition
 |
 |--------------------------------------------------------------------------
 |
 |  Designed by     :   
 |  Coded    by     :   
 |  Tested   by     :   
 |
 \=========================================================================*/

#ifndef __NEOWAY_NOCARE_H__
#define __NEOWAY_NOCARE_H__

typedef S32(*memcmp_fp)(const void*,const void*, U32);
typedef void*(*memcpy_fp)(void*,const void*, U32);
typedef void*(*memset_fp)(void*, S32, U32);
typedef S32(*strcmp_fp)(const S8*, const S8*);
typedef S8*(*strcpy_fp)(S8*, const S8*);
typedef U32(*strlen_fp)( const S8*);
typedef S8*(*strncpy_fp)(S8*, const S8*, U32);
typedef S8*(*strcat_fp)(S8*, const S8*);
typedef S8*(*strchr_fp)(const S8*, S32);
typedef U32(*strcspn_fp)(const S8*, const S8*);
typedef S8*(*strncat_fp)(S8*, const S8*, U32);
typedef S32(*strncmp_fp)(const S8*, const S8*, U32);
typedef S8*(*strrchr_fp)(const S8*, S32);
typedef U32(*strspn_fp)(const S8*, const S8*);
typedef S32(*sprintf_fp)(S8 *, const S8 *, ...);
typedef S32(*snprintf_fp)(S8* s, U32 n, const S8*  format, ...);
typedef S32(*vsprintf_fp)(S8 *, const S8 *, ...);
typedef S32(*vsnprintf_fp)(S8* s, U32 n, const S8*  format, ...);
typedef void(*__rt_lib_init_fp)(unsigned int, unsigned int);

typedef void (*Neoway_WriteAppToFlash_fp)(U32 );
typedef S32 (*Neoway_RegisterCallBack_fp)(NeowayCallbackIdEnum ,U32 );
typedef S32 (*Neoway_SendMsgTask_fp)(NeowayModuleTypeEnum , NeowayModuleTypeEnum , NeowayMsgIdEnum ,void *,U16 );
typedef S32 (*Neoway_InitTimer_fp)(NeowayTimerId *,NeowayModuleTypeEnum );
typedef S32 (*Neoway_StartTimer_fp)(NeowayTimerId *,U32 );
typedef S32 (*Neoway_StopTimer_fp)(NeowayTimerId *);
typedef NeowayTimerId * (*Neoway_GetTimerId_fp)(NeowayMsgTypeStruct );
typedef S32 (*Neoway_IsTimeExpiredValid_fp)(NeowayTimerId *);
typedef void (*Neoway_Reset_fp)(void);
typedef void (*Neoway_Shutdown_fp)(void);
typedef S32 (*Neoway_Sleep_fp)(NeowayBoolEnum );
typedef S32 (*Neoway_StartWatchdog_fp)(U32 );
typedef void (*Neoway_StopWatchdog_fp)(void);
typedef void (*Neoway_FeedWatchdog_fp)(void);
typedef void (*Neoway_SetTime_fp)(NeowayRtcStruct * );
typedef void (*Neoway_GetTime_fp)(NeowayRtcStruct * );
typedef S32 (*Neoway_IsTimeValid_fp)(NeowayRtcStruct * );
typedef void *(*Neoway_GetMemory_fp)(U32 );
typedef void (*Neoway_ReleaseMemory_fp)(void *);
typedef U32 (*Neoway_GetLeftMemory_fp)(void);
typedef S32 (*Neoway_GetNvParam_fp)(U8* );
typedef S32 (*Neoway_SaveNvParam_fp)(U8* );
typedef void (*Neoway_GpioInputMode_fp)(U8 , U8 , U8 );
typedef void (*Neoway_GpioOutputMode_fp)(U8 , U8 );
typedef S32  (*Neoway_GpioModeConfigure_fp)(U8 ,U8 );
typedef S32  (*Neoway_GpioDirectionConfigure_fp)(U8 ,U8 );
typedef void (*Neoway_GpioPullEnable_fp)(U8 , U8 );
typedef void (*Neoway_GpioPullSelect_fp)(U8 ,U8 );
typedef void  (*Neoway_GpioWrite_fp)(U8 ,U8 );
typedef U8 (*Neoway_GpioRead_fp)(U8 );
typedef U16 (*Neoway_ReadAdcValue_fp)(U8 );
typedef U16 (*Neoway_GetPowerSupply_fp)(void);
typedef void (*Neoway_InterruptInit_fp)(U16 ,NeowayIntNumEnum );
typedef void (*Neoway_InterruptSetDebounceTime_fp)(NeowayIntNumEnum ,U8 );
typedef void (*Neoway_InterruptSetPolarity_fp)(NeowayIntNumEnum ,NeowayBoolEnum );
typedef void (*Neoway_InterruptSetTriggerMode_fp)(NeowayIntNumEnum ,NeowayBoolEnum );
typedef NeowayMutexId (*Neoway_CreateMutex_fp)(S8 * );
typedef void (*Neoway_TakeMutex_fp)(NeowayMutexId );
typedef void (*Neoway_GiveMutex_fp)(NeowayMutexId );
typedef void (*Neoway_VirtualUartSend_fp)(NeowayModuleTypeEnum ,char *,U32 );
typedef S32 (*Neoway_EraseFlash_fp)(U32  );
typedef S32 (*Neoway_ReadFlash_fp)(U32  ,U8 * , U32 );
typedef S32 (*Neoway_WriteFlash_fp)(U32  ,U8 * , U32 );
typedef void (*Neoway_WriteUart1_fp)(U8 *,U16 );
typedef void(*Neoway_Print_fp)(S8 *,...);
typedef void (*Neoway_StartFtpUpdate_fp)(void);
typedef U8 (*Neoway_remote_param_setting_fp)(kal_uint8 ,const char *,const char *,const char *,const char *);//wzlopen
typedef void (*Neoway_remote_path_set_fp)(const char *);//wzlopen
typedef void (*Neoway_SetIpDataShowFlag_fp)(U8 );
typedef void (*Neoway_OpenUart1_toClient_Flag_fp)(U8 );
typedef S32 (*Neoway_FSOpen_fp)(const U16 * , U32 );
typedef S32 (*Neoway_FSClose_fp)(S32 );
typedef S32 (*Neoway_FSRead_fp)(S32 , void * , U32 , U32 * );
typedef S32 (*Neoway_FSWrite_fp)(S32 , void * , U32 , U32 * );
typedef S32 (*Neoway_FSSeek_fp)(S32 , S32 , S32 );
typedef S32 (*Neoway_FSCommit_fp)(S32 );
typedef S32 (*Neoway_FSGetFileSize_fp)(S32 , U32 * );
typedef S32 (*Neoway_FSDelete_fp)(const U16 * );
typedef S32 (*Neoway_FSLeftSpace_fp)();
typedef void (*Neoway_UartOpen_fp)(NeowayUartPortEnum );
typedef void (*Neoway_SetBaudrate_fp)(NeowayUartPortEnum ,NEOWAY_UART_BAUDRATE );
typedef void (*Neoway_Uart1Config_fp)(NeowayUartPortEnum ,UARTDCBStruct *);
typedef void (*Neoway_UartConfig_fp)(NeowayUartPortEnum ,UARTDCBStruct *);
typedef void (*Neoway_UartSend_fp)(NeowayUartPortEnum ,U8*,U16 );
typedef void (*Neoway_ReadAppVersion_fp)(U8*);
typedef bool (*neoway_user_tcp_setup_func_fp)(char *,char *,char *);
typedef bool (*neoway_user_tcp_send_func_fp)(char *,char *,int );
typedef bool (*neoway_user_tcp_close_func_fp)(char *);
typedef void (*Neoway_i2c_configure_fp)(kal_uint32 , kal_uint32 );
typedef void (*Neoway_i2c_send_ext_fp)( U16 , kal_uint8* , kal_uint32 );
typedef void (*Neoway_i2c_receive_ext_fp)(U16 , kal_uint8* , kal_uint32 );
typedef void (*Neoway_i2c_send_ext8_fp)( U8 , kal_uint8* , kal_uint32 );
typedef void (*Neoway_i2c_receive_ext8_fp)(U8 , kal_uint8* , kal_uint32 );
typedef U32 (*Neoway_SPI_Open_fp)(U32 );
typedef U32 (*Neoway_SPI_Close_fp)(SPI_HANDLE );
typedef U32 (*Neoway_SPI_Configure_fp)(SPI_HANDLE , SPI_CONFIG_PARAM_T * );//, SPI_CONFIG_PARAM_T* pConfigParam
typedef U32 (*Neoway_SPI_Write_fp)(SPI_HANDLE , void* , U32 , U32 , SPI_CALLBACK );
typedef U32 (*Neoway_SPI_Read_fp)(SPI_HANDLE , void* , U32 , U32 , SPI_CALLBACK );
typedef void (*Neoway_us_delay_fp)(kal_uint32 );
typedef void (*Neoway_SetAlarm_fp)(NeowayRtcStruct * ,U8 );
typedef void (*Neoway_VMC_enable_fp)(kal_bool , U8 );
typedef void (*neoway_caculate_md5_checksum_fp)(kal_uint8 *, kal_uint8 md5_out[32],kal_uint16 );
typedef S32 (*neoway_audio_play_file_fp)(void *);
typedef S32 (*neoway_audio_play_string_fp)(U8 *, U32 , U8 );
typedef void (*Neoway_apn_list_init_fp)(neoway_apn_gprs_struct *);
typedef void (*Neoway_StartFotaUpdate_fp)(U8 *);

typedef bool (*neoway_user_udp_setup_func_fp)(char *,char *,char *, char *);
typedef bool (*neoway_user_udp_send_func_fp)(char *,char *,int );
typedef bool (*neoway_user_udp_close_func_fp)(char *);

typedef int (*atoi_fp)(const char *);
typedef double (*atof_fp)(const char *);
typedef long int (*atol_fp)(const char *);
typedef U32 (*Neoway_GetCurrentTime_fp)(void);

typedef bool(*neoway_user_ftp_login_func_fp)(char *,char *,char *,char *);
typedef bool(*neoway_user_ftp_logout_func_fp)(void);
typedef bool(*neoway_user_ftp_put_func_fp)(char *,char *,char *,char *);
typedef void(*Neoway_PWM_Start_fp)(U8);
typedef void(*Neoway_PWM_Stop_fp)(U8);
typedef void(*Neoway_PWM_32K_Configure_fp)(U32, U8, U8);
typedef void(*Neoway_PWM_13M_Configure_fp)(U32, U8, U8);
extern memcmp_fp memcmp;
extern memcpy_fp memcpy;
extern memset_fp memset;
extern strcmp_fp strcmp;
extern strcpy_fp strcpy;
extern strlen_fp strlen;
extern strncpy_fp strncpy;
extern strcat_fp strcat;
extern strchr_fp strchr;
extern strcspn_fp strcspn;
extern strncat_fp strncat;
extern strncmp_fp strncmp;
extern strrchr_fp strrchr;
extern strspn_fp strspn;
extern sprintf_fp sprintf;
extern snprintf_fp snprintf;
extern vsprintf_fp vsprintf;
extern vsnprintf_fp vsnprintf;
extern __rt_lib_init_fp __rt_lib_init;


extern Neoway_WriteAppToFlash_fp Neoway_WriteAppToFlash;
extern Neoway_RegisterCallBack_fp Neoway_RegisterCallBack;
extern Neoway_SendMsgTask_fp Neoway_SendMsgTask;
extern Neoway_InitTimer_fp Neoway_InitTimer;
extern Neoway_StartTimer_fp Neoway_StartTimer;
extern Neoway_StopTimer_fp Neoway_StopTimer;
extern Neoway_GetTimerId_fp Neoway_GetTimerId;
extern Neoway_IsTimeExpiredValid_fp Neoway_IsTimeExpiredValid;
extern Neoway_Reset_fp Neoway_Reset;
extern Neoway_Shutdown_fp Neoway_Shutdown;
extern Neoway_Sleep_fp Neoway_Sleep;
extern Neoway_StartWatchdog_fp Neoway_StartWatchdog;
extern Neoway_StopWatchdog_fp Neoway_StopWatchdog;
extern Neoway_FeedWatchdog_fp Neoway_FeedWatchdog;
extern Neoway_SetTime_fp Neoway_SetTime;
extern Neoway_GetTime_fp Neoway_GetTime;
extern Neoway_IsTimeValid_fp Neoway_IsTimeValid;
extern Neoway_GetMemory_fp Neoway_GetMemory;
extern Neoway_ReleaseMemory_fp Neoway_ReleaseMemory;
extern Neoway_GetLeftMemory_fp Neoway_GetLeftMemory;
extern Neoway_GetNvParam_fp Neoway_GetNvParam;
extern Neoway_SaveNvParam_fp Neoway_SaveNvParam;
extern Neoway_GpioInputMode_fp Neoway_GpioInputMode;
extern Neoway_GpioOutputMode_fp Neoway_GpioOutputMode;
extern Neoway_GpioModeConfigure_fp Neoway_GpioModeConfigure;
extern Neoway_GpioDirectionConfigure_fp Neoway_GpioDirectionConfigure;
extern Neoway_GpioPullEnable_fp Neoway_GpioPullEnable;
extern Neoway_GpioPullSelect_fp Neoway_GpioPullSelect;
extern Neoway_GpioWrite_fp Neoway_GpioWrite;
extern Neoway_GpioRead_fp Neoway_GpioRead;
extern Neoway_ReadAdcValue_fp Neoway_ReadAdcValue;
extern Neoway_GetPowerSupply_fp Neoway_GetPowerSupply;
extern Neoway_InterruptInit_fp Neoway_InterruptInit;
extern Neoway_InterruptSetDebounceTime_fp Neoway_InterruptSetDebounceTime;
extern Neoway_InterruptSetPolarity_fp Neoway_InterruptSetPolarity;
extern Neoway_InterruptSetTriggerMode_fp Neoway_InterruptSetTriggerMode;
extern Neoway_CreateMutex_fp Neoway_CreateMutex;
extern Neoway_TakeMutex_fp Neoway_TakeMutex;
extern Neoway_GiveMutex_fp Neoway_GiveMutex;
extern Neoway_VirtualUartSend_fp Neoway_VirtualUartSend;
extern Neoway_EraseFlash_fp Neoway_EraseFlash;
extern Neoway_ReadFlash_fp Neoway_ReadFlash;
extern Neoway_WriteFlash_fp Neoway_WriteFlash;
extern Neoway_WriteUart1_fp Neoway_WriteUart1;
extern Neoway_Print_fp Neoway_Print;
extern Neoway_StartFtpUpdate_fp Neoway_StartFtpUpdate;
extern Neoway_remote_param_setting_fp Neoway_remote_param_setting;//wzlopen
extern Neoway_remote_path_set_fp Neoway_remote_path_set;//wzlopen
extern Neoway_SetIpDataShowFlag_fp Neoway_SetIpDataShowFlag;
extern Neoway_OpenUart1_toClient_Flag_fp Neoway_OpenUart1_toClient_Flag;
extern Neoway_FSOpen_fp Neoway_FSOpen;
extern Neoway_FSClose_fp Neoway_FSClose;
extern Neoway_FSRead_fp Neoway_FSRead;
extern Neoway_FSWrite_fp Neoway_FSWrite;
extern Neoway_FSSeek_fp Neoway_FSSeek;
extern Neoway_FSCommit_fp Neoway_FSCommit;
extern Neoway_FSGetFileSize_fp Neoway_FSGetFileSize;
extern Neoway_FSDelete_fp Neoway_FSDelete;
extern Neoway_FSLeftSpace_fp Neoway_FSLeftSpace;
extern Neoway_UartOpen_fp Neoway_UartOpen;
extern Neoway_SetBaudrate_fp Neoway_SetBaudrate;
extern Neoway_UartConfig_fp Neoway_UartConfig;
extern Neoway_UartSend_fp Neoway_UartSend;
extern Neoway_ReadAppVersion_fp Neoway_ReadAppVersion;
extern neoway_user_tcp_setup_func_fp neoway_user_tcp_setup_func;
extern neoway_user_tcp_send_func_fp neoway_user_tcp_send_func;
extern neoway_user_tcp_close_func_fp neoway_user_tcp_close_func;
extern Neoway_i2c_configure_fp Neoway_i2c_configure;
extern Neoway_i2c_send_ext_fp Neoway_i2c_send_ext;
extern Neoway_i2c_receive_ext_fp Neoway_i2c_receive_ext;
extern Neoway_i2c_send_ext8_fp Neoway_i2c_send_ext8;
extern Neoway_i2c_receive_ext8_fp Neoway_i2c_receive_ext8;
extern Neoway_SPI_Open_fp Neoway_SPI_Open;
extern Neoway_SPI_Close_fp Neoway_SPI_Close;
extern Neoway_SPI_Configure_fp Neoway_SPI_Configure;
extern Neoway_SPI_Write_fp Neoway_SPI_Write;
extern Neoway_SPI_Read_fp Neoway_SPI_Read;
extern Neoway_us_delay_fp Neoway_us_delay;
extern Neoway_SetAlarm_fp Neoway_SetAlarm;
extern Neoway_VMC_enable_fp Neoway_VMC_enable;
extern neoway_caculate_md5_checksum_fp neoway_caculate_md5_checksum;
extern neoway_audio_play_file_fp neoway_audio_play_file;
extern neoway_audio_play_string_fp neoway_audio_play_string;

extern neoway_user_udp_setup_func_fp neoway_user_udp_setup_func;
extern neoway_user_udp_send_func_fp neoway_user_udp_send_func;
extern neoway_user_udp_close_func_fp neoway_user_udp_close_func;

/* extern atoi_fp atoi;
extern atof_fp atof;
extern atol_fp atol; */

extern Neoway_GetCurrentTime_fp Neoway_GetCurrentTime;



extern U32 FIX_MOD_ID_USER1;
extern U32 FIX_MOD_ID_USER2;
extern U32 FIX_MOD_ID_USER3;
extern U32 FIX_MOD_ID_USER4;
extern U32 FIX_MOD_ID_USER5;
extern U32 FIX_MOD_ID_USER6;
extern U32 FIX_MOD_ID_USER7;
extern neoway_user_ftp_login_func_fp neoway_user_ftp_login_func;
extern neoway_user_ftp_logout_func_fp neoway_user_ftp_logout_func;
extern neoway_user_ftp_put_func_fp neoway_user_ftp_put_func;
extern Neoway_PWM_Start_fp Neoway_PWM_Start;
extern Neoway_PWM_Stop_fp Neoway_PWM_Stop;
extern Neoway_PWM_13M_Configure_fp Neoway_PWM_13M_Configure;
extern Neoway_PWM_32K_Configure_fp Neoway_PWM_32K_Configure;
#endif  // End-of __NEOWAY_TYPE_H__

