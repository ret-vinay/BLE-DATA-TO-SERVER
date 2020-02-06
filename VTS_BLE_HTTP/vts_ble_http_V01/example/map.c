
#include "neoway_openplatform.h"

typedef enum {
    FUNC_memcmp_0,
    FUNC_memcpy_1,
    FUNC_memset_2,
    FUNC_strcmp_3,
    FUNC_strcpy_4,
    FUNC_strlen_5,
    FUNC_strncpy_6,
    FUNC_strcat_7,
    FUNC_strchr_8,
    FUNC_strcspn_9,
    FUNC_strncat_10,
    FUNC_strncmp_11,
    FUNC_strrchr_12,
    FUNC_strspn_13,
    FUNC_sprintf_14,
    FUNC_snprintf_15,
    FUNC_vsprintf_16,
    FUNC_vsnprintf_17,
    FUNC_rt_lib_init_18,
    FUNC_19,
    FUNC_20,
    FUNC_WriteAppToFlash_21,
    FUNC_RegisterCallBack_22,
    FUNC_SendMsgTask_23,
    FUNC_InitTimer_24,
    FUNC_StartTimer_25,
    FUNC_StopTimer_26,
    FUNC_GetTimerId_27,
    FUNC_IsTimeExpiredValid_28,
    FUNC_Reset_29,
    FUNC_Shutdown_30,
    FUNC_Sleep_31,
    FUNC_StartWatchdog_32,
    FUNC_StopWatchdog_33,
    FUNC_FeedWatchdog_34,
    FUNC_SetTime_35,
    FUNC_GetTime_36,
    FUNC_IsTimeValid_37,
    FUNC_GetMemory_38,
    FUNC_ReleaseMemory_39,
    FUNC_GetLeftMemory_40,
    FUNC_GetNvParam_41,
    FUNC_SaveNvParam_42,
    FUNC_GpioInputMode_43,
    FUNC_GpioOutputMode_44,
    FUNC_GpioModeConfigure_45,
    FUNC_GpioDirectionConfigure_46,
    FUNC_GpioPullEnable_47,
    FUNC_GpioPullSelect_48,
    FUNC_GpioWrite_49,
    FUNC_GpioRead_50,
    FUNC_ReadAdcValue_51,
    FUNC_InterruptInit_52,
    FUNC_InterruptSetDebounceTime_53,
    FUNC_InterruptSetPolarity_54,
    FUNC_InterruptSetTriggerMode_55,
    FUNC_CreateMutex_56,
    FUNC_TakeMutex_57,
    FUNC_GiveMutex_58,
    FUNC_VirtualUartSend_59,
    FUNC_EraseFlash_60,
    FUNC_ReadFlash_61,
    FUNC_WriteFlash_62,
    FUNC_WriteUart1_63,
    FUNC_Print_64,
    FUNC_StartFtpUpdate_65,
    FUNC_SetIpDataShowFlag_66,
    FUNC_OpenUart1_toClient_Flag_67,
    FUNC_FSOpen_68,
    FUNC_FSClose_69,
    FUNC_FSRead_70,
    FUNC_FSWrite_71,
    FUNC_FSSeek_72,
    FUNC_FSCommit_73,
    FUNC_FSGetFileSize_74,
    FUNC_FSDelete_75,
    FUNC_FSLeftSpace_76,
    FUNC_UartOpen_77,
    FUNC_SetBaudrate_78,
    FUNC_Uart1Config_79,
    FUNC_UartConfig_80,
    FUNC_UartSend_81,
    FUNC_ReadAppVersion_82,
    FUNC_user_tcp_setup_func_83,
    FUNC_user_tcp_send_func_84,
    FUNC_user_tcp_close_func_85,
    FUNC_i2c_configure_86,
    FUNC_i2c_send_ext_87,
    FUNC_i2c_receive_ext_88,
    FUNC_i2c_send_ext8_89,
    FUNC_i2c_receive_ext8_90,
    FUNC_SPI_Open_91,
    FUNC_SPI_Close_92,
    FUNC_SPI_Configure_93,
    FUNC_SPI_Write_94,
    FUNC_SPI_Read_95,
    FUNC_us_delay_96,
    FUNC_SetAlarm_97,
    FUNC_VMC_enable_98,
    FUNC_caculate_md5_checksum_99,
    FUNC_audio_play_file_100,
    FUNC_audio_play_string_101,
    FUNC_apn_list_init_102,
    FUNC_StartFotaUpdate_103,
    FUNC_atoi_104,
    FUNC_atof_105,
    FUNC_atol_106,
    FUNC_GetCurrentTime_107,
    FUNC_Remote_Param_Setting_108,
    FUNC_Remote_Path_Set_109,
    FUNC_user_udp_setup_func_110,
    FUNC_user_udp_send_func_111,
    FUNC_user_udp_close_func_112,
    FIX_MOD_ID_USER1_120=120,
    FIX_MOD_ID_USER2_121,
    FIX_MOD_ID_USER3_122,
    FIX_MOD_ID_USER4_123,
    FIX_MOD_ID_USER5_124,
    FIX_MOD_ID_USER6_125,
    FIX_MOD_ID_USER7_126,
    FIX_CUSTOM_APP_BIN_BUF_127,
    FIX_SPI_BUF_128,
    //U8_Custom_App_Info_129,
    FUNC_Neoway_GetPowerSupply_129,
    FUNC_user_ftp_login_func_130,
    FUNC_user_ftp_logout_func_131,
    FUNC_user_ftp_put_func_132,
    NEOWAY_FUNC_END
}NeowayFuncListEnum;


memcmp_fp memcmp;//
memcpy_fp memcpy;
memset_fp memset;//
strcmp_fp strcmp;
strcpy_fp strcpy;
strlen_fp strlen;
strncpy_fp strncpy;
strcat_fp strcat;
strchr_fp strchr;
strcspn_fp strcspn;
strncat_fp strncat;
strncmp_fp strncmp;
strrchr_fp strrchr;
strspn_fp strspn;
sprintf_fp sprintf;
snprintf_fp snprintf;
vsprintf_fp vsprintf;
vsnprintf_fp vsnprintf;
__rt_lib_init_fp __rt_lib_init;


Neoway_WriteAppToFlash_fp Neoway_WriteAppToFlash;
Neoway_RegisterCallBack_fp Neoway_RegisterCallBack;//
Neoway_SendMsgTask_fp Neoway_SendMsgTask;//
Neoway_InitTimer_fp Neoway_InitTimer;//
Neoway_StartTimer_fp Neoway_StartTimer;//
Neoway_StopTimer_fp Neoway_StopTimer;//
Neoway_GetTimerId_fp Neoway_GetTimerId;//
Neoway_IsTimeExpiredValid_fp Neoway_IsTimeExpiredValid;//
Neoway_Reset_fp Neoway_Reset;//
Neoway_Shutdown_fp Neoway_Shutdown;//
Neoway_Sleep_fp Neoway_Sleep;
Neoway_StartWatchdog_fp Neoway_StartWatchdog;//
Neoway_StopWatchdog_fp Neoway_StopWatchdog;//
Neoway_FeedWatchdog_fp Neoway_FeedWatchdog;//
Neoway_SetTime_fp Neoway_SetTime;//
Neoway_GetTime_fp Neoway_GetTime;//
Neoway_IsTimeValid_fp Neoway_IsTimeValid;//
Neoway_GetMemory_fp Neoway_GetMemory;//
Neoway_ReleaseMemory_fp Neoway_ReleaseMemory;//
Neoway_GetLeftMemory_fp Neoway_GetLeftMemory;//
Neoway_GetNvParam_fp Neoway_GetNvParam;//
Neoway_SaveNvParam_fp Neoway_SaveNvParam;//
Neoway_GpioInputMode_fp Neoway_GpioInputMode;
Neoway_GpioOutputMode_fp Neoway_GpioOutputMode;
Neoway_GpioModeConfigure_fp Neoway_GpioModeConfigure;
Neoway_GpioDirectionConfigure_fp Neoway_GpioDirectionConfigure;
Neoway_GpioPullEnable_fp Neoway_GpioPullEnable;
Neoway_GpioPullSelect_fp Neoway_GpioPullSelect;
Neoway_GpioWrite_fp Neoway_GpioWrite;
Neoway_GpioRead_fp Neoway_GpioRead;
Neoway_ReadAdcValue_fp Neoway_ReadAdcValue;//
Neoway_InterruptInit_fp Neoway_InterruptInit;
Neoway_InterruptSetDebounceTime_fp Neoway_InterruptSetDebounceTime;
Neoway_InterruptSetPolarity_fp Neoway_InterruptSetPolarity;
Neoway_InterruptSetTriggerMode_fp Neoway_InterruptSetTriggerMode;
Neoway_CreateMutex_fp Neoway_CreateMutex;//
Neoway_TakeMutex_fp Neoway_TakeMutex;//
Neoway_GiveMutex_fp Neoway_GiveMutex;//
Neoway_VirtualUartSend_fp Neoway_VirtualUartSend;//
Neoway_EraseFlash_fp Neoway_EraseFlash;
Neoway_ReadFlash_fp Neoway_ReadFlash;
Neoway_WriteFlash_fp Neoway_WriteFlash;
Neoway_WriteUart1_fp Neoway_WriteUart1;
Neoway_Print_fp Neoway_Print;//
Neoway_StartFtpUpdate_fp Neoway_StartFtpUpdate;//
Neoway_remote_param_setting_fp Neoway_remote_param_setting;//wzlopen
Neoway_remote_path_set_fp Neoway_remote_path_set;//wzlopen
Neoway_SetIpDataShowFlag_fp Neoway_SetIpDataShowFlag;//
Neoway_OpenUart1_toClient_Flag_fp Neoway_OpenUart1_toClient_Flag;//
Neoway_FSOpen_fp Neoway_FSOpen;//
Neoway_FSClose_fp Neoway_FSClose;//
Neoway_FSRead_fp Neoway_FSRead;//
Neoway_FSWrite_fp Neoway_FSWrite;//
Neoway_FSSeek_fp Neoway_FSSeek;//
Neoway_FSCommit_fp Neoway_FSCommit;//
Neoway_FSGetFileSize_fp Neoway_FSGetFileSize;//
Neoway_FSDelete_fp Neoway_FSDelete;//
Neoway_FSLeftSpace_fp Neoway_FSLeftSpace;//
Neoway_UartOpen_fp Neoway_UartOpen;//
Neoway_SetBaudrate_fp Neoway_SetBaudrate;//
Neoway_UartConfig_fp Neoway_UartConfig;//
Neoway_UartSend_fp Neoway_UartSend;//
Neoway_ReadAppVersion_fp Neoway_ReadAppVersion;//
neoway_user_tcp_setup_func_fp neoway_user_tcp_setup_func;//
neoway_user_tcp_send_func_fp neoway_user_tcp_send_func;//
neoway_user_tcp_close_func_fp neoway_user_tcp_close_func;//
Neoway_i2c_configure_fp Neoway_i2c_configure;//
Neoway_i2c_send_ext_fp Neoway_i2c_send_ext;//
Neoway_i2c_receive_ext_fp Neoway_i2c_receive_ext;//
Neoway_i2c_send_ext8_fp Neoway_i2c_send_ext8;//
Neoway_i2c_receive_ext8_fp Neoway_i2c_receive_ext8;//
Neoway_SPI_Open_fp Neoway_SPI_Open;//
Neoway_SPI_Close_fp Neoway_SPI_Close;//
Neoway_SPI_Configure_fp Neoway_SPI_Configure;//
Neoway_SPI_Write_fp Neoway_SPI_Write;//
Neoway_SPI_Read_fp Neoway_SPI_Read;//
Neoway_us_delay_fp Neoway_us_delay;//
Neoway_SetAlarm_fp Neoway_SetAlarm;//
Neoway_VMC_enable_fp Neoway_VMC_enable;//
neoway_caculate_md5_checksum_fp neoway_caculate_md5_checksum;
neoway_audio_play_file_fp neoway_audio_play_file;//
neoway_audio_play_string_fp neoway_audio_play_string;//
Neoway_GetPowerSupply_fp Neoway_GetPowerSupply;
neoway_user_udp_setup_func_fp neoway_user_udp_setup_func;//
neoway_user_udp_send_func_fp neoway_user_udp_send_func;//
neoway_user_udp_close_func_fp neoway_user_udp_close_func;//
neoway_user_ftp_login_func_fp neoway_user_ftp_login_func;//
neoway_user_ftp_logout_func_fp neoway_user_ftp_logout_func;//
neoway_user_ftp_put_func_fp neoway_user_ftp_put_func;//
Neoway_PWM_Start_fp Neoway_PWM_Start;
Neoway_PWM_Stop_fp Neoway_PWM_Stop;
Neoway_PWM_13M_Configure_fp Neoway_PWM_13M_Configure;
Neoway_PWM_32K_Configure_fp Neoway_PWM_32K_Configure;


atoi_fp atoi;//
atof_fp atof;//
atol_fp atol;//
Neoway_GetCurrentTime_fp Neoway_GetCurrentTime;

U32 FIX_MOD_ID_USER1;
U32 FIX_MOD_ID_USER2;
U32 FIX_MOD_ID_USER3;
U32 FIX_MOD_ID_USER4;
U32 FIX_MOD_ID_USER5;
U32 FIX_MOD_ID_USER6;
U32 FIX_MOD_ID_USER7;
U8* custom_app_bin_buffer;
U8* cmmb_spi_src_buffer_all; 
U8* cmmb_spi_src_buffer_out; 

static U32* open_map;
U32 g_addr=0;
typedef U32*(*neoway_get_addr_fp)(void);
void neoway_get_addr(void)
{
    open_map = ((neoway_get_addr_fp)0x1001f301)();
    //open_map = ((neoway_get_addr_fp)0x10020f8d)();
    memcmp = (memcmp_fp)(open_map[FUNC_memcmp_0]);
    memcpy = (memcpy_fp)(open_map[FUNC_memcpy_1]);
    memset = (memset_fp)(open_map[FUNC_memset_2]);
    strcmp = (strcmp_fp)(open_map[FUNC_strcmp_3]);
    strcpy = (strcpy_fp)(open_map[FUNC_strcpy_4]);
    strlen = (strlen_fp)(open_map[FUNC_strlen_5]);
    strncpy = (strncpy_fp)(open_map[FUNC_strncpy_6]);
    strcat = (strcat_fp)(open_map[FUNC_strcat_7]);
    strchr = (strchr_fp)(open_map[FUNC_strchr_8]);
    strcspn = (strcspn_fp)(open_map[FUNC_strcspn_9]);
    strncat = (strncat_fp)(open_map[FUNC_strncat_10]);
    strncmp = (strncmp_fp)(open_map[FUNC_strncmp_11]);
    strrchr = (strrchr_fp)(open_map[FUNC_strrchr_12]);
    strspn = (strspn_fp)(open_map[FUNC_strspn_13]);
    sprintf = (sprintf_fp)(open_map[FUNC_sprintf_14]);
    snprintf = (snprintf_fp)(open_map[FUNC_snprintf_15]);
    vsprintf = (vsprintf_fp)(open_map[FUNC_vsprintf_16]);
    vsnprintf = (vsnprintf_fp)(open_map[FUNC_vsnprintf_17]);
    __rt_lib_init = (__rt_lib_init_fp)(open_map[FUNC_rt_lib_init_18]);


    Neoway_WriteAppToFlash = (Neoway_WriteAppToFlash_fp)(open_map[FUNC_WriteAppToFlash_21]);
    Neoway_RegisterCallBack = (Neoway_RegisterCallBack_fp)(open_map[FUNC_RegisterCallBack_22]);
    Neoway_SendMsgTask = (Neoway_SendMsgTask_fp)(open_map[FUNC_SendMsgTask_23]);
    Neoway_InitTimer = (Neoway_InitTimer_fp)(open_map[FUNC_InitTimer_24]);
    Neoway_StartTimer = (Neoway_StartTimer_fp)(open_map[FUNC_StartTimer_25]);
    Neoway_StopTimer = (Neoway_StopTimer_fp)(open_map[FUNC_StopTimer_26]);
    Neoway_GetTimerId = (Neoway_GetTimerId_fp)(open_map[FUNC_GetTimerId_27]);
    Neoway_IsTimeExpiredValid = (Neoway_IsTimeExpiredValid_fp)(open_map[FUNC_IsTimeExpiredValid_28]);
    Neoway_Reset = (Neoway_Reset_fp)(open_map[FUNC_Reset_29]);
    Neoway_Shutdown = (Neoway_Shutdown_fp)(open_map[FUNC_Shutdown_30]);
    Neoway_Sleep = (Neoway_Sleep_fp)(open_map[FUNC_Sleep_31]);
    Neoway_StartWatchdog = (Neoway_StartWatchdog_fp)(open_map[FUNC_StartWatchdog_32]);
    Neoway_StopWatchdog = (Neoway_StopWatchdog_fp)(open_map[FUNC_StopWatchdog_33]);
    Neoway_FeedWatchdog = (Neoway_FeedWatchdog_fp)(open_map[FUNC_FeedWatchdog_34]);
    Neoway_SetTime = (Neoway_SetTime_fp)(open_map[FUNC_SetTime_35]);
    Neoway_GetTime = (Neoway_GetTime_fp)(open_map[FUNC_GetTime_36]);
    Neoway_IsTimeValid = (Neoway_IsTimeValid_fp)(open_map[FUNC_IsTimeValid_37]);
    Neoway_GetMemory = (Neoway_GetMemory_fp)(open_map[FUNC_GetMemory_38]);
    Neoway_ReleaseMemory = (Neoway_ReleaseMemory_fp)(open_map[FUNC_ReleaseMemory_39]);
    Neoway_GetLeftMemory = (Neoway_GetLeftMemory_fp)(open_map[FUNC_GetLeftMemory_40]);
    Neoway_GetNvParam = (Neoway_GetNvParam_fp)(open_map[FUNC_GetNvParam_41]);
    Neoway_SaveNvParam = (Neoway_SaveNvParam_fp)(open_map[FUNC_SaveNvParam_42]);
    Neoway_GpioInputMode = (Neoway_GpioInputMode_fp)(open_map[FUNC_GpioInputMode_43]);
    Neoway_GpioOutputMode = (Neoway_GpioOutputMode_fp)(open_map[FUNC_GpioOutputMode_44]);
    Neoway_GpioModeConfigure = (Neoway_GpioModeConfigure_fp)(open_map[FUNC_GpioModeConfigure_45]);
    Neoway_GpioDirectionConfigure = (Neoway_GpioDirectionConfigure_fp)(open_map[FUNC_GpioDirectionConfigure_46]);
    Neoway_GpioPullEnable = (Neoway_GpioPullEnable_fp)(open_map[FUNC_GpioPullEnable_47]);
    Neoway_GpioPullSelect = (Neoway_GpioPullSelect_fp)(open_map[FUNC_GpioPullSelect_48]);
    Neoway_GpioWrite = (Neoway_GpioWrite_fp)(open_map[FUNC_GpioWrite_49]);
    Neoway_GpioRead = (Neoway_GpioRead_fp)(open_map[FUNC_GpioRead_50]);
    Neoway_ReadAdcValue = (Neoway_ReadAdcValue_fp)(open_map[FUNC_ReadAdcValue_51]);
    Neoway_InterruptInit = (Neoway_InterruptInit_fp)(open_map[FUNC_InterruptInit_52]);
    Neoway_InterruptSetDebounceTime = (Neoway_InterruptSetDebounceTime_fp)(open_map[FUNC_InterruptSetDebounceTime_53]);
    Neoway_InterruptSetPolarity = (Neoway_InterruptSetPolarity_fp)(open_map[FUNC_InterruptSetPolarity_54]);
    Neoway_InterruptSetTriggerMode = (Neoway_InterruptSetTriggerMode_fp)(open_map[FUNC_InterruptSetTriggerMode_55]);
    Neoway_CreateMutex = (Neoway_CreateMutex_fp)(open_map[FUNC_CreateMutex_56]);
    Neoway_TakeMutex = (Neoway_TakeMutex_fp)(open_map[FUNC_TakeMutex_57]);
    Neoway_GiveMutex = (Neoway_GiveMutex_fp)(open_map[FUNC_GiveMutex_58]);
    Neoway_VirtualUartSend = (Neoway_VirtualUartSend_fp)(open_map[FUNC_VirtualUartSend_59]);
    Neoway_EraseFlash = (Neoway_EraseFlash_fp)(open_map[FUNC_EraseFlash_60]);
    Neoway_ReadFlash = (Neoway_ReadFlash_fp)(open_map[FUNC_ReadFlash_61]);
    Neoway_WriteFlash = (Neoway_WriteFlash_fp)(open_map[FUNC_WriteFlash_62]);
    Neoway_WriteUart1 = (Neoway_WriteUart1_fp)(open_map[FUNC_WriteUart1_63]);
    Neoway_Print = (Neoway_Print_fp)(open_map[FUNC_Print_64]);
    Neoway_StartFtpUpdate = (Neoway_StartFtpUpdate_fp)(open_map[FUNC_StartFtpUpdate_65]);
    Neoway_SetIpDataShowFlag = (Neoway_SetIpDataShowFlag_fp)(open_map[FUNC_SetIpDataShowFlag_66]);
    Neoway_OpenUart1_toClient_Flag = (Neoway_OpenUart1_toClient_Flag_fp)(open_map[FUNC_OpenUart1_toClient_Flag_67]);
    Neoway_FSOpen = (Neoway_FSOpen_fp)(open_map[FUNC_FSOpen_68]);
    Neoway_FSClose = (Neoway_FSClose_fp)(open_map[FUNC_FSClose_69]);
    Neoway_FSRead = (Neoway_FSRead_fp)(open_map[FUNC_FSRead_70]);
    Neoway_FSWrite = (Neoway_FSWrite_fp)(open_map[FUNC_FSWrite_71]);
    Neoway_FSSeek = (Neoway_FSSeek_fp)(open_map[FUNC_FSSeek_72]);
    Neoway_FSCommit = (Neoway_FSCommit_fp)(open_map[FUNC_FSCommit_73]);
    Neoway_FSGetFileSize = (Neoway_FSGetFileSize_fp)(open_map[FUNC_FSGetFileSize_74]);
    Neoway_FSDelete = (Neoway_FSDelete_fp)(open_map[FUNC_FSDelete_75]);
    Neoway_FSLeftSpace = (Neoway_FSLeftSpace_fp)(open_map[FUNC_FSLeftSpace_76]);
    Neoway_UartOpen = (Neoway_UartOpen_fp)(open_map[FUNC_UartOpen_77]);
    Neoway_SetBaudrate = (Neoway_SetBaudrate_fp)(open_map[FUNC_SetBaudrate_78]);
    Neoway_UartConfig = (Neoway_UartConfig_fp)(open_map[FUNC_UartConfig_80]);
    Neoway_UartSend = (Neoway_UartSend_fp)(open_map[FUNC_UartSend_81]);
    Neoway_ReadAppVersion = (Neoway_ReadAppVersion_fp)(open_map[FUNC_ReadAppVersion_82]);
    neoway_user_tcp_setup_func = (neoway_user_tcp_setup_func_fp)(open_map[FUNC_user_tcp_setup_func_83]);
    neoway_user_tcp_send_func = (neoway_user_tcp_send_func_fp)(open_map[FUNC_user_tcp_send_func_84]);
    neoway_user_tcp_close_func = (neoway_user_tcp_close_func_fp)(open_map[FUNC_user_tcp_close_func_85]);
    Neoway_i2c_configure = (Neoway_i2c_configure_fp)(open_map[FUNC_i2c_configure_86]);
    Neoway_i2c_send_ext = (Neoway_i2c_send_ext_fp)(open_map[FUNC_i2c_send_ext_87]);
    Neoway_i2c_receive_ext = (Neoway_i2c_receive_ext_fp)(open_map[FUNC_i2c_receive_ext_88]);
    Neoway_i2c_send_ext8 = (Neoway_i2c_send_ext8_fp)(open_map[FUNC_i2c_send_ext8_89]);
    Neoway_i2c_receive_ext8 = (Neoway_i2c_receive_ext8_fp)(open_map[FUNC_i2c_receive_ext8_90]);
    Neoway_SPI_Open = (Neoway_SPI_Open_fp)(open_map[FUNC_SPI_Open_91]);
    Neoway_SPI_Close = (Neoway_SPI_Close_fp)(open_map[FUNC_SPI_Close_92]);
    Neoway_SPI_Configure = (Neoway_SPI_Configure_fp)(open_map[FUNC_SPI_Configure_93]);
    Neoway_SPI_Write = (Neoway_SPI_Write_fp)(open_map[FUNC_SPI_Write_94]);
    Neoway_SPI_Read = (Neoway_SPI_Read_fp)(open_map[FUNC_SPI_Read_95]);
    Neoway_us_delay = (Neoway_us_delay_fp)(open_map[FUNC_us_delay_96]);
    Neoway_SetAlarm = (Neoway_SetAlarm_fp)(open_map[FUNC_SetAlarm_97]);
    Neoway_VMC_enable = (Neoway_VMC_enable_fp)(open_map[FUNC_VMC_enable_98]);
    neoway_caculate_md5_checksum = (neoway_caculate_md5_checksum_fp)(open_map[FUNC_caculate_md5_checksum_99]);
    neoway_audio_play_file = (neoway_audio_play_file_fp)(open_map[FUNC_audio_play_file_100]);
    neoway_audio_play_string = (neoway_audio_play_string_fp)(open_map[FUNC_audio_play_string_101]);
    atoi = (atoi_fp)(open_map[FUNC_atoi_104]);
    atof = (atof_fp)(open_map[FUNC_atof_105]);
    atol = (atol_fp)(open_map[FUNC_atol_106]);
    Neoway_GetCurrentTime = (Neoway_GetCurrentTime_fp)(open_map[FUNC_GetCurrentTime_107]);
    Neoway_remote_param_setting = (Neoway_remote_param_setting_fp)(open_map[FUNC_Remote_Param_Setting_108]);
    Neoway_remote_path_set = (Neoway_remote_path_set_fp)(open_map[FUNC_Remote_Path_Set_109]);

    neoway_user_udp_setup_func = (neoway_user_udp_setup_func_fp)(open_map[FUNC_user_udp_setup_func_110]);
    neoway_user_udp_send_func = (neoway_user_udp_send_func_fp)(open_map[FUNC_user_udp_send_func_111]);
    neoway_user_udp_close_func = (neoway_user_udp_close_func_fp)(open_map[FUNC_user_udp_close_func_112]);

    FIX_MOD_ID_USER1 = open_map[FIX_MOD_ID_USER1_120];
    FIX_MOD_ID_USER2 = open_map[FIX_MOD_ID_USER2_121];
    FIX_MOD_ID_USER3 = open_map[FIX_MOD_ID_USER3_122];
    FIX_MOD_ID_USER4 = open_map[FIX_MOD_ID_USER4_123];
    FIX_MOD_ID_USER5 = open_map[FIX_MOD_ID_USER5_124];
    FIX_MOD_ID_USER6 = open_map[FIX_MOD_ID_USER6_125];
    FIX_MOD_ID_USER7 = open_map[FIX_MOD_ID_USER7_126];
    custom_app_bin_buffer = (U8*)open_map[FIX_CUSTOM_APP_BIN_BUF_127];
    cmmb_spi_src_buffer_all = (U8*)open_map[FIX_SPI_BUF_128];
    cmmb_spi_src_buffer_out = cmmb_spi_src_buffer_all+512;
    Neoway_GetPowerSupply = (Neoway_GetPowerSupply_fp)(open_map[FUNC_Neoway_GetPowerSupply_129]);
    neoway_user_ftp_login_func=(neoway_user_ftp_login_func_fp)(open_map[FUNC_user_ftp_login_func_130]);
    neoway_user_ftp_logout_func=(neoway_user_ftp_logout_func_fp)(open_map[FUNC_user_ftp_logout_func_131]);
    neoway_user_ftp_put_func=(neoway_user_ftp_put_func_fp)(open_map[FUNC_user_ftp_put_func_132]);
    //Neoway_PWM_Start=(Neoway_PWM_Start_fp)(open_map[FUNC_Neoway_PWM_Start_133]);
    //Neoway_PWM_Stop=(Neoway_PWM_Stop_fp)(open_map[FUNC_Neoway_PWM_Stop_134]);
    //Neoway_PWM_13M_Configure=(Neoway_PWM_13M_Configure_fp)(open_map[FUNC_Neoway_PWM_13M_Configure_135]);
    //Neoway_PWM_32K_Configure=(Neoway_PWM_32K_Configure_fp)(open_map[FUNC_Neoway_PWM_32K_Configure_136]);
}

void NWT_memset(U8*dst,U8 data,U32 len)
{
    U32 index;
    for (index = 0; index < len; index++) 
        *dst++ = data;
}


