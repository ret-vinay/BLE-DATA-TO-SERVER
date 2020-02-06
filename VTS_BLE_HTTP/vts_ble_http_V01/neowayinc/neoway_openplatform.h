#ifndef __NEOWAY_OPENPLATFORM_H__
#define __NEOWAY_OPENPLATFORM_H__

#include "neoway_type.h"

/*Please consult the GPIO table to find the corresponding relationship between the module pin and GPIO.
The client can independently define the GPIO macro by the example below according to the GPIO number in the table*/
#define NEOWAY_GPIO_0  	0       //INT0
#define NEOWAY_GPIO_1  	1       //INT1
#define NEOWAY_GPIO_3  	3 
#define NEOWAY_GPIO_12  12      //Uart2 Rx
#define NEOWAY_GPIO_13 	13      //INT11
#define NEOWAY_GPIO_14 	14      //INT12 
#define NEOWAY_GPIO_15 	15
#define NEOWAY_GPIO_17 	17      //Uart2 TX
#define NEOWAY_GPIO_21 	21
#define NEOWAY_GPIO_25 	25      //INT15
#define NEOWAY_GPIO_26 	26
#define NEOWAY_GPIO_27 	27
#define NEOWAY_GPIO_28 	28
#define NEOWAY_GPIO_29	29
#define NEOWAY_GPIO_30  30      //INT16
#define NEOWAY_GPIO_31  31
#define NEOWAY_GPIO_32  32
#define NEOWAY_GPIO_33  33
#define NEOWAY_GPIO_34  34      //INT17
#define NEOWAY_GPIO_35  35      //INT18
#define NEOWAY_GPIO_36  36      //INT19
#define NEOWAY_GPIO_43  43      //SCL PIN OF I2C
#define NEOWAY_GPIO_44  44      //SDA PIN OF I2C

#define NEOWAY_MODE_GPIO    0
#define NEOWAY_MODE_INT     3   //INT MODE

/**************I2C Mode Configuration**********************/
#define NEOWAY_MODE_GPIO43_1        1   //SCL PIN OF I2C
#define NEOWAY_MODE_GPIO44_1        1   //SDA PIN OF I2C
/***************************************************/

/**************SPIMode Configuration**********************/
#define NEOWAY_MODE_GPIO27_4        4   //SCK PIN OF SPI
#define NEOWAY_MODE_GPIO26_4        4   //CS PIN OF SPI
#define NEOWAY_MODE_GPIO28_4        4   //MOSI PIN OF SPI
#define NEOWAY_MODE_GPIO29_4        4   //MISO PIN OF SPI
/***************************************************/

#define NEOWAY_RET_OK                       0
#define NEOWAY_RET_ERR_PARAM                -1
#define NEOWAY_RET_ERR_TIMER_REINIT         -2
#define NEOWAY_RET_ERR_TIMER_FULL           -3
#define NEOWAY_RET_ERR_INVALID_TIMER        -4
#define NEOWAY_RET_ERR_INVALID_TIME_OUT     -5
#define NEOWAY_RET_ERR_INVALID_TIME         -6
#define NEOWAY_RET_ERR_OPERATE_FAIL         -7
#define NEOWAY_RET_ERR_NO_SUPPORT_MODE      -8
#define NEOWAY_RET_ERR_NO_SUPPORT_PIN       -9

typedef U32 NEOWAY_UART_BAUDRATE;
typedef unsigned short WCHAR;

#define     NEOWAY_UART_BAUD_75            75
#define     NEOWAY_UART_BAUD_150           150
#define     NEOWAY_UART_BAUD_300           300
#define     NEOWAY_UART_BAUD_600           600
#define     NEOWAY_UART_BAUD_1200          1200
#define     NEOWAY_UART_BAUD_2400          2400
#define     NEOWAY_UART_BAUD_4800          4800
#define     NEOWAY_UART_BAUD_7200          7200
#define     NEOWAY_UART_BAUD_9600          9600
#define     NEOWAY_UART_BAUD_14400         14400
#define     NEOWAY_UART_BAUD_19200         19200
#define     NEOWAY_UART_BAUD_28800         28800
#define     NEOWAY_UART_BAUD_33900         33900
#define     NEOWAY_UART_BAUD_38400         38400
#define     NEOWAY_UART_BAUD_57600         57600
#define     NEOWAY_UART_BAUD_115200        115200
#define     NEOWAY_UART_BAUD_230400        230400
#define     NEOWAY_UART_BAUD_460800        460800
#define     NEOWAY_UART_BAUD_921600        921600

typedef enum 
{
    NEOWAY_FALSE,
    NEOWAY_TRUE
}NeowayBoolEnum;


typedef enum {
    len_5=5,
    len_6,
    len_7,
    len_8
} UART_bitsPerCharacter;

typedef enum {
    sb_1=1,
    sb_2,
    sb_1_5
} UART_stopBits;

typedef enum {
    pa_none=0,
    pa_odd,
    pa_even,
    pa_mark,
    pa_space
} UART_parity;

typedef enum {
    fc_none=1,
    fc_hw,
    fc_sw
} UART_flowCtrlMode;

typedef enum {
    NEOWAY_RETURN_NULL,
    NEOWAY_RETURN_EMPTY,
    NEOWAY_RETURN_ERROR,
    NEOWAY_RETURN_OK
}CommandReturn;

typedef struct
{
    NEOWAY_UART_BAUDRATE    baud; 
    UART_bitsPerCharacter   dataBits;
    UART_stopBits           stopBits;
    UART_parity             parity;
    UART_flowCtrlMode       flowControl;
    U8                      xonChar;
    U8                      xoffChar;
    NeowayBoolEnum          DSRCheck;
} UARTDCBStruct;

typedef enum 
{
    NEOWAY_INT_0=0,
    NEOWAY_INT_1=1,
    NEOWAY_INT_11=11,
    NEOWAY_INT_12=12,
    NEOWAY_INT_15=15,
    NEOWAY_INT_16=16,
    NEOWAY_INT_17=17,
    NEOWAY_INT_18=18,
    NEOWAY_INT_19=19
}NeowayIntNumEnum;

#define     NEOWAY_MOD_USER1 (NeowayModuleTypeEnum)FIX_MOD_ID_USER1
#define     NEOWAY_MOD_USER2 (NeowayModuleTypeEnum)FIX_MOD_ID_USER2
#define     NEOWAY_MOD_USER3 (NeowayModuleTypeEnum)FIX_MOD_ID_USER3
#define     NEOWAY_MOD_USER4 (NeowayModuleTypeEnum)FIX_MOD_ID_USER4
#define     NEOWAY_MOD_USER5 (NeowayModuleTypeEnum)FIX_MOD_ID_USER5
#define     NEOWAY_MOD_USER6 (NeowayModuleTypeEnum)FIX_MOD_ID_USER6
#define     NEOWAY_MOD_USER7 (NeowayModuleTypeEnum)FIX_MOD_ID_USER7
typedef enum {
    NEOWAY_MOD_NULL
} NeowayModuleTypeEnum;

typedef enum {
    NEOWAY_MSG_USER_BEGIN=26000,
    NEOWAY_MSG_ID_TIMER_EXPIRY=26001,
    NEOWAY_MSG_ID_TASK1_TASK2,
    NEOWAY_MSG_ID_TASK2_TASK3,
    NEOWAY_MSG_ID_TASK3_TASK1,
    NEOWAY_MSG_ID_TAKE_MUTEX,
    NEOWAY_MSG_ID_GAVE_MUTEX,
    NEOWAY_MSG_ID_INT_NOTIFY,
    NEOWAY_MSG_ID_INT_NOTIFY7,
    NEOWAY_MSG_ID_INT_NOTIFY10,
    //add by Tim to test the OpenCPU platform
    NEOWAY_MSG_ID_TEST,
    NEOWAY_MSG_ID_TEST1,
    NEOWAY_MSG_ID_VIRTUALUARTSEND,
	
	NEOWAY_FOTA_START_NOTIFY,/// done by V
    NEOWAY_FOTA_END_NOTIFY,/// done by V
	
	NEOWAY_MSG_ID_EIND_NOTIFY,
	NEOWAY_MSG_ID_INIT_OK,
	NEOWAY_XIIC_INIT_OK,/// done by ragu
	NEOWAY_MSG_ID_DATA_SEND_REQUIRE,
	NEOWAY_MSG_ID_AT_SEND_OK,
	NEOWAY_MSG_ID_AT_SEND_ERROR,
	NEOWAY_MSG_ID_START_REG_AUC,
	
	SD_Card_Write,
	SD_Card_Read,
	SD_Card_Write_NS_Data,
	//BAT_VOLT_READ,
	
    NEOWAY_MSG_ID_END=NEOWAY_MSG_USER_BEGIN+500
}NeowayMsgIdEnum;

typedef enum {
    NEOWAY_KB_ID_USER_TASK_1,
    NEOWAY_KB_ID_USER_TASK_2,
    NEOWAY_KB_ID_USER_TASK_3,
    NEOWAY_KB_ID_USER_TASK_4,
    NEOWAY_KB_ID_USER_TASK_5,
    NEOWAY_KB_ID_USER_TASK_6,
    NEOWAY_KB_ID_USER_TASK_7,
    NEOWAY_KB_ID_COMMAND,
    NEOWAY_KB_ID_TEST,
    NEOWAY_KB_ID_INT_RESPONSE,
    NEOWAY_KB_ID_VIRTUAL_UART_RECEIVE,
    NEOWAY_KB_ID_FTP_UPDATE,
    NEOWAY_KB_ID_IP_RECEIVE,//pangyl 120911
    NEOWAY_KB_ID_UART_RECEIVE,
    NEOWAY_KB_ID_ONOFF_STATE_RESPONSE
}NeowayCallbackIdEnum;
typedef enum 
{
    NEOWAY_UPDATE_FAILE,////
    NEOWAY_UPDATE_ALREADY,////
    NEOWAY_UPDATE_OVER,////
    NEOWAY_UPDATE_TIMEOUT////
}NeowayFtpUpdateStataEnum;
typedef enum {
    NEOWAY_UART_PORT_1,
    NEOWAY_UART_PORT_2,
    NEOWAY_UART_PORT_3
} NeowayUartPortEnum;

typedef enum {
    NEOWAY_MDI_FORMAT_WAV   = 13,   /* 13 : WAV  */
    NEOWAY_MDI_FORMAT_SMF   = 17,   /* 17 : MIDI */
    NEOWAY_MED_TYPE_PCM_8K  = 7,    /* 7  : PCM  */
    NEOWAY_MEDIA_FORMAT_DAF = 5,    /* 5  : MP3  */
    NEOWAY_MEDIA_FORMAT_AMR = 3,    /* 3  : AMR  */
} NeowayMdiFormat;

typedef struct{
    NeowayMsgIdEnum     msg_id;
    U8              *   msg_ptr;
    void            *   data_ptr;
    U16                 data_len;
}NeowayMsgTypeStruct;
typedef void(*NeowayTaskUserFptr)(NeowayMsgTypeStruct,NeowayModuleTypeEnum);
typedef int(*NeowayCommandFptr)(S8*,NeowayModuleTypeEnum);
typedef void(*NeowayTestFptr)(S8*,NeowayModuleTypeEnum);
typedef void(*NeowayIntResponseFptr)(NeowayIntNumEnum,NeowayModuleTypeEnum);
typedef void(*NeowayVirtualUartReceiveFptr)(U8 *,U16, NeowayModuleTypeEnum);
typedef void(*NeowayFtpUpdateFptr)(NeowayFtpUpdateStataEnum,NeowayModuleTypeEnum);
typedef void(*NeowayIpDataReceiveFptr)(U8,U32,S8 *, NeowayModuleTypeEnum);//TCP/UDP recv pangyl 121109
typedef void(*NeowayUartReceiveFptr)(NeowayUartPortEnum,U8 *,U16, NeowayModuleTypeEnum);
typedef void(*NeowayOnOffkeyFptr)(NeowayBoolEnum, NeowayModuleTypeEnum);
typedef struct {
    NeowayTaskUserFptr  user_task_1;
    NeowayTaskUserFptr  user_task_2;
    NeowayTaskUserFptr  user_task_3;
    NeowayTaskUserFptr  user_task_4;
    NeowayTaskUserFptr  user_task_5;
    NeowayTaskUserFptr  user_task_6;
    NeowayTaskUserFptr  user_task_7;
    NeowayCommandFptr   command;
    NeowayTestFptr      test;
    NeowayIntResponseFptr           int_response;
    NeowayVirtualUartReceiveFptr    virtual_uart_receive;
    NeowayFtpUpdateFptr             Ftp_Update_Func;
    NeowayIpDataReceiveFptr         ip_data_receive;//TCP/UDP recv pangyl 121109
    NeowayUartReceiveFptr           uart_receive;
    NeowayOnOffkeyFptr              onoff_state_response;
}NeowayCallbackFunctionStruct;
typedef struct 
{
    U8  rtc_sec;    /* sec - [0, 59 ]  */
    U8  rtc_min;    /* min - [0, 59 ]  */
    U8  rtc_hour;   /* hour - [0, 23 ]  */
    U8  rtc_day;    /* day - [1, 31 ]  */
    U8  rtc_mon;    /* month - [1, 12 ]  */
    U8  rtc_year;   /* year - [0, 127]  */
} NeowayRtcStruct;

typedef struct
{
    U8  unused;
} *NeowayMutexId;

typedef struct
{
    const U32   plmn;
    const U8  * APN;
    const U8  * USER;
    const U8  * PWD;
}neoway_apn_gprs_struct;

typedef struct
{
    U32 plmn;
    U8  APN[80];
    U8  USER[50];
    U8  PWD[50];
}neoway_apn_gprs_no_p_struct;

#if 1//pangyl 121114

/* Neoway_FSOpen flags */
#define NEOWAY_FS_READ_WRITE           0x00000000L
#define NEOWAY_FS_READ_ONLY            0x00000100L 
#define NEOWAY_FS_OPEN_SHARED          0x00000200L 
#define NEOWAY_FS_OPEN_NO_DIR          0x00000400L 
#define NEOWAY_FS_OPEN_DIR             0x00000800L 
#define NEOWAY_FS_CREATE               0x00010000L 
#define NEOWAY_FS_CREATE_ALWAYS        0x00020000L 
#define NEOWAY_FS_COMMITTED            0x01000000L 
#define NEOWAY_FS_CACHE_DATA           0x02000000L 
#define NEOWAY_FS_LAZY_DATA            0x04000000L 
#define NEOWAY_FS_NONBLOCK_MODE        0x10000000L
#define NEOWAY_FS_PROTECTION_MODE      0x20000000L
#define NEOWAY_FS_NOBUSY_CHECK_MODE    0x40000000L

#endif

typedef U32 NeowayTimerId;
#define NEOWAY_MAX_TIMER_NUM 32//You can apply for 32 timers at most



typedef enum
{
    /* Indicates no error occurs in the last operation. */
    SPI_RESULT_OK,

    /* Indicates some errors have occured in the last operation. */
    SPI_RESULT_ERROR,

    /* Indicates some errors have occured in the last operation. */
    SPI_RESULT_INVALID_ARGUMENT,  

    /* Indicates the function is not supported on the current platform. */
    SPI_RESULT_NOT_SUPPORTED
} SPI_RESULT;


/* SPI Handle.
   SPI handle can be retrieved from spi_open(). It is used for most SPI APIs.
*/
typedef U32 SPI_HANDLE;

/* <GROUP CallBackFunctions>
   FUNCTION
   SPI_CALLBACK
   DESCRIPTION
   SPI callback function
   SPI callback function is called when SPI interrupt has arrived. It indicates SPI has finished the last data transfer.
   SPI callback function is called in the context of HISR.
*/
typedef void (*SPI_CALLBACK)(void);

/* SPI transimssion bit order definition. */
typedef enum
{
    /* Transfer LSB first. */
    SPI_MSBF_LSB = 0,
    /* Transfer MSB first. */
    SPI_MSBF_MSB = 1
} SPI_MSBF_E;

/* SPI data transfer byte order definition. */
typedef enum
{
    /* Use little endian. */
    SPI_ENDIAN_LITTLE = 0,
    /* Use big endian. */
    SPI_ENDIAN_BIG = 1
} SPI_ENDIAN_E;

/* SPI clock polarity definition. */
typedef enum
{
    /* CPOL = 0. */
    SPI_CPOL_B0 = 0,
    /* CPOL = 1. */
    SPI_CPOL_B1 = 1
} SPI_CPOL_E;

/* SPI clock format definition. */
typedef enum
{
    /* CPHA = 0. */
    SPI_CPHA_B0 = 0,
    /* CPHA = 1. */
    SPI_CPHA_B1 = 1
} SPI_CPHA_E;

enum SPI_MLSB {
  SPI_LSB = 0,
  /**<
   * \ingroup spi
   * LSB.
   */
  SPI_MSB
  /**<
   * \ingroup spi
   * MSB.
   */
};
typedef enum SPI_MLSB SPI_MLSB;

/** \enum SPI_CPOL
 * \ingroup spi
 *
 * @brief
 * Choose the desired clock polarities supported by the SPI interface.
 */
enum SPI_CPOL {
    SPI_CPOL_0 = 0,
    /**<
     * \ingroup spi
     * SPI clock polarity 0.
     */
    SPI_CPOL_1
    /**<
     * \ingroup spi
     * SPI clock polarity 1.
     */
};
typedef enum SPI_CPOL SPI_CPOL;

/** \enum SPI_CPHA
 * \ingroup spi
 *
 * @brief
 * Choose the desired clock formats supported by the SPI interface.
 */
enum SPI_CPHA {
    SPI_CPHA_0 = 0,
    /**<
     * \ingroup spi
     * SPI clock format 0.
     */
    SPI_CPHA_1
    /**<
     * \ingroup spi
     * SPI clock format 1.
     */
};
typedef enum SPI_CPHA SPI_CPHA;




/************************************
 * SPI configuration parameters.
 * 
 * Remarks
 * <img name="spi_timing_diagram" />
 ************************************/
typedef struct
{
    /* CS setup time. Unit in count of SPI base clock. Range(0-255).
       The chip select setup time = (cs_setup_time+1)*CLK_PERIOD, where CLK_PERIOD is the cycle time of the clock the SPI engine adopts. */
    U32 cs_setup_time;
    /* CS hold time. Unit in count of SPI base clock. Range(0-255).
       The chip select hold time = (cs_hold_time+1)*CLK_PERIOD. */
    U32 cs_hold_time;
    /* CS idle time. Unit in count of SPI base clock. Range(0-255).
       The chip select idle time between consecutive transaction = (cs_idle_time+1)*CLK_PERIOD. */
    U32 cs_idle_time;
    /* SCK clock low time. Unit in count of SPI base clock. Range(0-255).
       The SCK clock low time = (clk_low_time+1)*CLK_PERIOD. */
    U32 clk_low_time;
    /* SCK clock high time. Unit in count of SPI base clock. Range(0-255).
       The SCK clock high time = (clk_high_time+1)*CLK_PERIOD. */
    U32 clk_high_time;
    /* Bit order setting for SPI output. */
    SPI_MSBF_E tx_msbf;
    /* Bit order setting for SPI input. */
    SPI_MSBF_E rx_msbf;
    /* Byte order setting for SPI output. */
    SPI_ENDIAN_E tx_endian;
    /* Byte order setting for SPI input. */
    SPI_ENDIAN_E rx_endian;
    /* SPI clock polarity. */
    SPI_CPOL_E clk_polarity;
    /* SPI clock format. */
    SPI_CPHA_E clk_fmt;
} SPI_CONFIG_PARAM_T;

#define NEOWAY_USER_APP_LENGTH            200*1024//200KB  Warning:Not to be changed
extern U8* custom_app_bin_buffer;
//extern U32 custom_app_flag;


#ifndef NEOWAY_NODEFINED
#include "neoway_nocare.h"
#else
extern S32 memcmp(const void*, const void*, U32 len);
extern void* memcpy (void*, const void*, U32 len);
extern void* memset (void*, S32, U32 len);
extern S32 strcmp (const S8*, const S8*);
extern S8* strcpy (S8*, const S8*);
extern U32 strlen (const S8*);
extern S8* strncpy (S8*, const S8*, U32 len);
extern S8* strcat (S8*, const S8*);
extern S8* strchr (const S8*, S32);
extern U32 strcspn (const S8*, const S8*);
extern S8* strncat (S8*, const S8*, U32);
extern S32 strncmp (const S8*, const S8*, U32);
extern S8* strrchr (const S8*, S32);
extern U32 strspn (const S8*, const S8*);
extern S32 sprintf(S8 *, const S8 *, ...);
extern S32 snprintf(S8* s, U32 n, const S8*  format, ...);
extern S32 vsprintf(S8 *, const S8 *, ...);
extern S32 vsnprintf(S8* s, U32 n, const S8*  format, ...);
/*****************************************************************************
 * Definition :
 *   Writes app data which saved in custom_app_bin_buffer[NEOWAY_USER_APP_LENGTH]
 *   to a specific flash region.
 * Parameter :
 *   custom_app_flag           Length of app data
 * Return value :
 *   void
 * Note :
 *   Before you execute this function, save the app data in 
 *   custom_app_bin_buffer[NEOWAY_USER_APP_LENGTH].
 *****************************************************************************/
extern void Neoway_WriteAppToFlash(U32 custom_app_flag);

//#endif
/*****************************************************************************
 * Definition :
 *   Register the CallBack function
 * Parameter :
 *   call_back_id                  Registration ID
 *   call_back_function         Callback interface
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_PARAM
 *****************************************************************************/
extern S32 Neoway_RegisterCallBack(NeowayCallbackIdEnum call_back_id,U32 call_back_function);

/*****************************************************************************
 * Definition :
 *   Source Task send a message to destination Task.
 * Parameter :
 *   src_mod_id                 Identification of Source Task
 *   des_mod_id                Identification of Destination Task
 *   msg_id                      Messages to be sent
 *   data                          A pointer to data sent out with the message. if no data you want to send,it could be NULL.
 *                                   The data space must be applied by the client himself, 
 *					     and the space should be released after the message processing has been completed.
 *   data_len                     The length of the data. It is set to 0 with no data.
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_PARAM
 *****************************************************************************/
extern S32 Neoway_SendMsgTask(NeowayModuleTypeEnum src_mod_id, NeowayModuleTypeEnum des_mod_id, NeowayMsgIdEnum msg_id,void *data,U16 data_len);

/*****************************************************************************
 * Definition :
 *   Initializes a timer.
 * Parameter :
 *   timer_id                    A pointer to Timer id which user wants to use
 *   mod_id                      Task ID￡?The timeout message will be sent to the assigned task for processing
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_TIMER_REINIT
 *   NEOWAY_RET_ERR_TIMER_FULL
 *****************************************************************************/
extern S32 Neoway_InitTimer(NeowayTimerId *timer_id,NeowayModuleTypeEnum mod_id);

/*****************************************************************************
 * Definition :
 *   Start the Timer
 * Parameter :
 *   timer_id                   Point to the initialized Timer ID
 *   Tick                       Time.The unit is TICK, and 216 ticks equal to one second.
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_INVALID_TIMER
 *****************************************************************************/
extern S32 Neoway_StartTimer(NeowayTimerId *timer_id,U32 tick);

/*****************************************************************************
 * Definition :
 *   Stop the Timer
 * Parameter :
 *   timer_id                   Point to the initialized Timer ID
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_INVALID_TIMER
 *****************************************************************************/
extern S32 Neoway_StopTimer(NeowayTimerId *timer_id);

/*****************************************************************************
 * Definition :
 *   Extract timer ID from the received message.
 * Parameter :
 *   msg                        The message received by the current task
 * Return value :
 *   Pointer to timeout Timer ID.
 *****************************************************************************/
extern NeowayTimerId * Neoway_GetTimerId(NeowayMsgTypeStruct msg);

/*****************************************************************************
 * Definition :
 *   Determines whether the specified timer timeout message is still valid, and if invalid, it doesn't need to be processed.
 * Parameter :
 *   timer_id                   Point to the initialized Timer ID
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_INVALID_TIMER
 *   NEOWAY_RET_ERR_INVALID_TIME_OUT 
 *****************************************************************************/
extern S32 Neoway_IsTimeExpiredValid(NeowayTimerId *timer_id);

/*****************************************************************************
 * Definition :
 *   Restart the module
 * Parameter :
 *   void
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_Reset(void);

/*****************************************************************************
 * Definition :
 *   Shut down the module.
 * Parameter :
 *   void
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_Shutdown(void);

/*****************************************************************************
 * Definition :
 *   Control module goes into sleep mode or not
 * Parameter :
 *   is_sleep           NEOWAY_FALSE        Exit sleep mode           
 *                         NEOWAY_TRUE         Enter sleep mode
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_PARAM
 *****************************************************************************/
extern S32 Neoway_Sleep(NeowayBoolEnum is_sleep);

/*****************************************************************************
 * Definition :
 *   Soft watchdog will automatically open after the boot.If the upper software execution shutdown watchdog function, 
 *   you can open the watchdog through this function.
 * Parameter :
 *   expire_time                   Expiry time, and the unit is seconds.
						 The default timeout of watchdog is 180 seconds and the range 1~65535.
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_PARAM
 *****************************************************************************/
extern S32 Neoway_StartWatchdog(U32 expire_time);

/*****************************************************************************
 * Definition :
 *   Shut down the watchdog.
 * Parameter :
 *   void
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_StopWatchdog(void);

/*****************************************************************************
 * Definition :
 *   If the upper software watchdog has been turned on, the dog must be fed regularly, otherwise the module will restart.
 * Parameter :
 *   void
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_FeedWatchdog(void);

/*****************************************************************************
 * Definition :
 *   Set the time of the module.
 * Parameter :
 *   rtc_time                   A pointer to rtc time
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_SetTime(NeowayRtcStruct * rtc_time);

/*****************************************************************************
 * Definition :
 *   Get the time of the module.
 * Parameter :
 *   rtc_time                   A pointer to rtc time
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_GetTime(NeowayRtcStruct * rtc_time);

/*****************************************************************************
 * Definition :
 *   Determine if the time is valid.
 * Parameter :
 *   rtc_time                   A pointer to rtc time
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_INVALID_TIME
 *****************************************************************************/
extern S32 Neoway_IsTimeValid(NeowayRtcStruct * rtc_time);

/*******************************************************************
* Definition :
*   Get the current time of the module.
* Parameter :
*   void
* Return value :
*   U32                         The time from starting up to the present. Per 32768 is 1s. 
********************************************************************/
extern U32 Neoway_GetCurrentTime(void);

/*****************************************************************************
 * Definition :
 *   Apply for memory
 * Parameter :
 *   len                        Size of memory requested
 * Return value :
 *   Memory address or NULL
 *****************************************************************************/
extern void *Neoway_GetMemory(U32 len);

/*****************************************************************************
 * Definition :
 *   Release the memory
 * Parameter :
 *   buff_ptr                   A pointer to memory requested
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_ReleaseMemory(void *address);

/*****************************************************************************
 * Definition :
 *   Get the remaining sapce of memory size
 * Parameter :
 *   void
 * Return value :
 *   Bytes remaining in memory
 *****************************************************************************/
extern U32 Neoway_GetLeftMemory(void);

/*****************************************************************************
 * Definition :
 *   Read data from NV, the length of data is 512 bytes.
 * Parameter :
 *   buff_ptr                   A pointer to NV parameter ,and the space after buff_ptr 512 Bytes must be available.
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_OPERATE_FAIL
 *****************************************************************************/
extern S32 Neoway_GetNvParam(U8*buff_ptr );

/*****************************************************************************
 * Definition :
 *   Store NV Parameter with the length of 512 bytes
 * Parameter :
 *   buff_ptr                   A pointer to NV parameter
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_OPERATE_FAIL
 *****************************************************************************/
extern S32 Neoway_SaveNvParam(U8*buff_ptr );

/*****************************************************************************
 * Definition :
 *   Set GPIO input mode,and enable GPIO to pull down
 * Parameter :
 *   pin                Pin of GPIO
 *   pull_en            0           unenable to set pull-up or drop-down mode
 *                      1           enable to set pull-up or drop-down mode
 *   pull_up            0           drop-down
 *                      1           pull-up
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_GpioInputMode(U8 pin, U8 pull_en, U8 pull_up);

/*****************************************************************************
 * Definition :
 *   Set GPIO output mode, and set GPIO output high or low level
 * Parameter :
 *   pin                Pin of GPIO
 *   data               0       Low level
 *                      1       High level
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_GpioOutputMode(U8 pin, U8 data);

/*****************************************************************************
 * Definition :
 *   Set GPIO mode
 * Parameter :
 *   pin                        Pin of GPIO
 *   pin_mode                   You can only set NEOWAY_MODE_GPIO at this point.
 * Return value :
 *   NEOWAY_RET_OK
 *****************************************************************************/
extern S32  Neoway_GpioModeConfigure(U8 pin,U8 pin_mode);

/*****************************************************************************
 * Definition :
 *   Configure the GPIO input and output directions
 * Parameter :
 *   pin                        Pin of GPIO
 *   direction                  input and output directions        0   input
 *                                                                 1   output
 * Return value :
 *   NEOWAY_RET_OK
 *****************************************************************************/
extern S32  Neoway_GpioDirectionConfigure(U8 pin,U8 direction);

/*****************************************************************************
 * Definition :
 *   Enable to set pull-up or drop-down mode
 * Parameter :
 *   pin                        Pin of GPIO
 *   pull_en                    0   unenable to set pull-up or drop-down mode
 *                              1   enable to set pull-up or drop-down mode
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_GpioPullEnable(U8 pin, U8 pull_en);

/*****************************************************************************
 * Definition :
 *   Set pull-up or drop-down mode
 * Parameter :
 *   pin                        Pin of GPIO
 *   pull_up                    0   drop down
 *                              1   pull up
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_GpioPullSelect(U8 pin,U8 pull_up);

/*****************************************************************************
 * Definition :
 *   Set GPIO high or low level
 * Parameter :
 *   pin                        Pin of GPIO
 *   data                       0   Low level
 *                              1   High level
 * Return value :
 *   void
 *****************************************************************************/
extern void  Neoway_GpioWrite(U8 pin,U8 data);

/*****************************************************************************
 * Definition :
 *   Read the value of GPIO
 * Parameter :
 *   pin                        Pin of GPIO
 * Return value :
 *   0  Low level
 *   1  High level
 *****************************************************************************/
extern U8 Neoway_GpioRead(U8 pin);

/*****************************************************************************
*Definition :
*  ADC detection
*Parameter :
*  sel  : The number of ADC channels detected
*  0    : ADC0 PIN
*  1    : ADC1 PIN
*  2    : ADC2 PIN
*Return value :
*  -1   : Invalid input
*  >0   : The value read form ADC
******************************************************************************/
extern U16 Neoway_ReadAdcValue(U8 sel);

/*****************************************************************************
*Definition :
*  Get voltage value
*Return value :
*  -1   : Invalid input
*  >0   : voltage value    Unit: mV
******************************************************************************/
extern U16 Neoway_GetPowerSupply();

/*****************************************************************************
 * Definition :
 *   Initialize an interrupt
 * Parameter :
 *   pin                        PIN
 *   int_no                     INT Number
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_InterruptInit(U16 pin,NeowayIntNumEnum int_no);

/*****************************************************************************
 * Definition :
 *   Set the time of interrupting to remove jitter time
 * Parameter :
 *   int_no                     INT Number
 *   debounce_time              Unit: tick  The parameter is recommended to be set more than 10.
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_InterruptSetDebounceTime(NeowayIntNumEnum int_no,U8 debounce_time);

/*****************************************************************************
 * Definition :
 *   Configure interrupt polarity
 * Parameter :
 *   int_no                     Int Number
 *   interrupt_polarity         Interrupt polarity    NEOWAY_FALSE    Falling edge or low level
 *                                                    NEOWAY_TRUE     Rising edge or high level
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_InterruptSetPolarity(NeowayIntNumEnum int_no,NeowayBoolEnum interrupt_polarity);

/*****************************************************************************
 * Definition :
 *   Set Interrupt mode
 * Parameter :
 *   int_no                     Int Number
 *   mode                       Interrupt mode    NEOWAY_FALSE    Level interrupt
 *                                                NEOWAY_TRUE     Edge interrupt
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_InterruptSetTriggerMode(NeowayIntNumEnum int_no,NeowayBoolEnum mode);

/*****************************************************************************
 * Definition :
 *   Create mutex
 * Parameter :
 *   mutex_name_ptr             Its name should be unique.
 * Return value :
 *   Mutex ID
 *****************************************************************************/
extern NeowayMutexId Neoway_CreateMutex(S8 * mutex_name_ptr);

/*****************************************************************************
 * Definition :
 *   Lock  resources
 * Parameter :
 *   ext_mutex_id_ptr           Mutex ID
 * Return value :
 *   void 
 *****************************************************************************/
extern void Neoway_TakeMutex(NeowayMutexId ext_mutex_id_ptr);

/*****************************************************************************
 * Definition :
 *   Unlock resources
 * Parameter :
 *   ext_mutex_id_ptr           Mutex ID
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_GiveMutex(NeowayMutexId ext_mutex_id_ptr);

/*****************************************************************************
 * Definition :
 *   Send data to module by virtual serial port
 * Parameter :
 *   mod_id                     ID of the current task
 *   data_ptr                   Point to the data to be sent to the Uart
 *   data_len                   Length of data sent
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_VirtualUartSend(NeowayModuleTypeEnum mod_id,char *cmd_ptr,U32 cmd_len);

/*****************************************************************************
 * Definition :
 *   Erase the FLASH and erase the block corresponding to the current address
 * Parameter :
 *   flash_addr                 The flash block in which the address is located (a block is 4096 bytes)
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_OPERATE_FAIL
 *****************************************************************************/
extern S32 Neoway_EraseFlash(U32 flash_addr );

/*****************************************************************************
 * Definition :
 *   Read FLASH
 * Parameter :
 *   flash_addr                 Point to the FLASH address to read
 *   data_ptr                    Buffer
 *   len                           Length of data
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_OPERATE_FAIL
 *****************************************************************************/
extern S32 Neoway_ReadFlash(U32 flash_addr ,U8 * data_ptr, U32 len);

/*****************************************************************************
 * Definition :
 *   Write 4096 bytes of data to FLASH
 * Parameter :
 *   flash_addr                 Point to the FLASH address to write
 *   data_ptr                   Buffer
 *   len                        Length of data 
 * Return value :
 *   NEOWAY_RET_OK
 *   NEOWAY_RET_ERR_OPERATE_FAIL
 *****************************************************************************/
extern S32 Neoway_WriteFlash(U32 flash_addr ,U8 * data_ptr, U32 len);

/*****************************************************************************
 * Definition :
 *   Print data to Uart 1.
 * Parameter :
 *   data_ptr                   Buffer
 *   data_len                   Length of data
 * Return value :
 *   void 
 *****************************************************************************/
extern void Neoway_WriteUart1(U8 *data_ptr,U16 data_len);

/*****************************************************************************
 * Definition :
 *   Print data to Uart 1.
 * Parameter :
 *   fmt                        Data to be printed
 * Return value :
 *   void 
 *****************************************************************************/
extern void Neoway_Print(S8 *fmt,...);

/*****************************************************************************
 * Definition :
 *   Set parameter of FTP remote upgrade
 * Parameter :
 *   Addr_mode                  When it is set as 1,use IP as address. If 2, use domain name as address.
 *   Ftp_addr                     Server address
 *   Ftp_port                      Port number
 *   Ftp_username               User name
 *   Ftp_password               password
 * Return value :
 *   kal_uint8                  If success it returns 1 ,otherwise it returns to other values. 
								When fail, the server's Parameter was the value set last time
 *****************************************************************************/

extern kal_uint8 Neoway_remote_param_setting(kal_uint8 Addr_mode,const char *Ftp_addr,const char *Ftp_port,const char *Ftp_username,const char *Ftp_password);
/*****************************************************************************
 * Definition :
 *   Set the storage path of the upgrade file when the FTP is remotely upgraded. 
 *   The default execution is to specify the FTP server root directory when it is not set
 * Parameter :
 *   Ftp_remote_file_path         The storage path of the upgrade file(It should be end with"\\")	
						    The first level directory defaults to the root directory of the specified FTP server.
 * Return value :
 *   void 
 *****************************************************************************/
extern void Neoway_remote_path_set(const char *Ftp_remote_file_path);

/*****************************************************************************
 * Definition :
 *   When the function is called, the module will automatically connect to the specified FTP to upgrade.
 * Parameter :
 *   void
 * Return value :
 *   void 
 *****************************************************************************/
extern void Neoway_StartFtpUpdate(void);

/*****************************************************************************
 * Definition :
 *   Determines whether the received GPRS data is received by virtual serial port or by callback function.
 * Parameter :
 *   flag                       If flag equals to 1,the user receives the  data through the callback function Neoway_IpdataRecieve;
 *                              If flag equals to 0,the  data is received directly in the virtual serial port.
 *   void 
 *****************************************************************************/
extern void Neoway_SetIpDataShowFlag(U8 flag);

/*****************************************************************************
 * Definition :
 *   Set the Uart 1 as the AT system use-only or configured for the user's own use
 * Parameter :
 *   flag                       If flag equals to 1,user can configure the Uart1 and process the data of the Uart1.
 *                              If flag equals to 0,Uart1 can only be used as the AT dedicated channel of the system, in which the default is 0
 * Return value :
 *   void 
 *****************************************************************************/
extern void Neoway_OpenUart1_toClient_Flag(U8 flag);

/*****************************************************************************
 * Definition :
 *   Create a new file or open an existing file.
 * Parameter :
 *   FileName                   File path and file name.
 *   Flag                       File operation type.NEOWAY_FS_READ_WRITE?￠NEOWAY_FS_CREATE etc.
 * Return value :
 *   File handler               0 means create or open a file successfully.
 *                                <0 means failure.
 *****************************************************************************/
extern S32 Neoway_FSOpen(const U16 * FileName, U32 Flag);

/*****************************************************************************
 * Definition￡o
 *   close file.
 * Parameter￡o
 *   FileHandle                
 * Return value￡o
 *   0 means success,otherwise it means failure.
 *****************************************************************************/
extern S32 Neoway_FSClose(S32 FileHandle);

/*****************************************************************************
 * Definition￡o
 *   Read file.
 * Parameter￡o
 *   FileHandle                 
 *   DataPtr                    A pointer to a buffer which stores data.
 *   Length                     The length of data
 *   Read                       The number of bytes are read actually.
 * Return value￡o
 *   0 means success,otherwise it means failure.
 *****************************************************************************/
extern S32 Neoway_FSRead(S32 FileHandle, void * DataPtr, U32 Length, U32 * Read);

/*****************************************************************************
 * Definition￡o
 *   Write file 
 * Parameter￡o
 *   FileHandle                 
 *   DataPtr                    A pointer to a buffer which stores data.
 *   Length                     The length of data
 *   Written                    The number of bytes are written actually.
 * Return value￡o
 *   0 means success,otherwise it means failure.
 *****************************************************************************/
extern S32 Neoway_FSWrite(S32 FileHandle, void * DataPtr, U32 Length, U32 * Written);

/*****************************************************************************
 * Definition￡o
 *   The file pointer points to a specific location.
 * Parameter￡o
 *   FileHandle                 
 *   Offset                     Pointer offset. The forward offset is negative, and the backward offset is positive.
 *   Whence                   0 : Beginning of file
 *                                 1 : File current position
 *                                 2 : end of file
 * Return value￡o
 * 0 means success,otherwise it means failure.
 *****************************************************************************/
extern S32 Neoway_FSSeek(S32 FileHandle, S32 Offset, S32 Whence);

/*****************************************************************************
 * Definition￡o
 *   Ensure that data is written to buffer and it is generally used after Neoway_FSWrite.
 * Parameter￡o
 *   FileHandle                 
 * Return value￡o
 *   0 means success,otherwise it means failure.
 *****************************************************************************/
extern S32 Neoway_FSCommit(S32 FileHandle);

/*****************************************************************************
 * Definition￡o
 *   Get file size.
 * Parameter￡o
 *   FileHandle                 
 *   Size                       File size
 * Return value￡o
 *   0 means success,otherwise it means failure.
 *****************************************************************************/
extern S32 Neoway_FSGetFileSize(S32 FileHandle, U32 * Size);

/*****************************************************************************
 * Definition￡o
 *   Delete file
 * Parameter￡o
 *   FileHandle                 
 * Return value￡o
 *   0 means success,otherwise it means failure.
 *****************************************************************************/
extern S32 Neoway_FSDelete(const U16 * FileName);

/*****************************************************************************
 * Definition￡o
 *   Get the remaining space of file system
 * Parameter￡o
 *   FileHandle                
 * Return value￡o
 *   Size of remaining space
 *****************************************************************************/
extern S32 Neoway_FSLeftSpace();

/*****************************************************************************
 * Definition :
 *   Open Uart, the module currently supports Uart one and two
 * Parameter :
 *   port                       Port number
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_UartOpen(NeowayUartPortEnum port);

/*****************************************************************************
 * Definition :
 *   Set Uart baud rate,the module currently supports Uart one and two
 * Parameter :
 *   port                       
 *   baudrate                   NEOWAY_UART_BAUD_115200 etc.
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_SetBaudrate(NeowayUartPortEnum port,NEOWAY_UART_BAUDRATE baudrate);

/*****************************************************************************
 * Definition :
 *   Set Uart baud rate,the module currently supports Uart one and two
 * Parameter :
 *   port                       
 *   uart_dcb                   Pointer to parameter
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_UartConfig(NeowayUartPortEnum port,UARTDCBStruct *uart_dcb);

/*****************************************************************************
 * Definition :
 *   Send data by Uart,the module currently supports Uart one and two
 * Parameter :
 *   port                       Port number
 *   buffer                     
 *   length                    The length of data
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_UartSend(NeowayUartPortEnum port,U8*buffer,U16 length);

/*****************************************************************************
 * Definition￡o
 *   Read user software version
 * Parameter￡o
 *   buff_ptr                   User software version
 * Return value￡o
 *   void
 *****************************************************************************/
extern void Neoway_ReadAppVersion(U8*buff_ptr);

/*****************************************************************************
 * Definition￡o
 *   Building UDP links
 * Parameter￡o
 *   str_id   :                 link number0~4
 *   str_ip   :                 IP address
 *   str_port :                Server's port
 *   str_local_port :        Local port number
 * Return value￡o
 *   0 : Fail
 *   1 : Success
 *****************************************************************************/
extern bool neoway_user_udp_setup_func(char *str_id,char *str_ip,char *str_port, char *str_local_port);

/*****************************************************************************
 * Definition :
 *   Send data by UDP
 * Parameter :
 *   str_id :                   link number0~4
 *   string :                   data 
 *   len    :                   The length of data
 * Return value :
 *   0 : Fail
 *   1 : Success
 *****************************************************************************/
extern bool neoway_user_udp_send_func(char *str_id,char *string,int len);

/*****************************************************************************
 * Definition :
 *   Close UDP link
 * Parameter :
 *   str_id :                   link number0~4
 * Return value :
 *   0 : Fail
 *   1 : Success
 *****************************************************************************/
extern bool neoway_user_udp_close_func(char *str_id);

/*****************************************************************************
 * Definition￡o
 *   Build TCP link
 * Parameter￡o
 *   str_id   :                 link number0~4
 *   str_ip   :                 IP address
 *   str_port :                 Server's port
 * Return value￡o
 *   0 : Fail
 *   1 : Success
 *****************************************************************************/
extern bool neoway_user_tcp_setup_func(char *str_id,char *str_ip,char *str_port);

/*****************************************************************************
 * Definition :
 *   Send data by TCP
 * Parameter :
 *   str_id :                   link number0~4
 *   string :                   data
 *   len    :                   The length of data
 * Return value :
 *   0 : Fail
 *   1 : Success
 *****************************************************************************/
extern bool neoway_user_tcp_send_func(char *str_id,char *string,int len);

/*****************************************************************************
 * Definition :
 *   Close TCP link
 * Parameter :
 *   str_id :                   link number0~4
 * Return value :
 *   0 : Fail
 *   1 : Success
 *****************************************************************************/
extern bool neoway_user_tcp_close_func(char *str_id);

/*****************************************************************************
 * Definition :
 *   The settings that must be set before the I2C device communicates.
 * Parameter :
 *   slave_addr :               8 bit valid address of I2C device
 *                              (the value of the actual 7 bit physical address shifted one bit to the left)
 *   speed :                    The communication rate is 10K~100K, corresponding to the clock frequency.
 * Return value :
 *   void 
 *****************************************************************************/
extern void Neoway_i2c_configure(kal_uint32 slave_addr, kal_uint32 speed);

/*****************************************************************************
 * Definition :
 *   The module writes data to the I2C slave device.
 * Parameter :
 *   ucBufferIndex :             Register address to receive data from device
 *   pucData       :               The starting address of the data buffer
 *   unDataLength  :            The length of data
 * Return value :
 *   1 Success
 *   0 Fail
 *****************************************************************************/
extern void Neoway_i2c_send_ext( U16 ucBufferIndex, kal_uint8* pucData, kal_uint32 unDataLength);

/*****************************************************************************
 * Definition :
 *   The module reads the data from the I2C slave device
 * Parameter :
 *   ucBufferIndex :             Register address to receive data from device
 *   pucData       :               The starting address of the data buffer
 *   unDataLength  :            The length of data
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_i2c_receive_ext(U16 ucBufferIndex, kal_uint8* pucData, kal_uint32 unDataLength);

/*****************************************************************************
 * Definition :
 *   The module writes data to the I2C slave device
 * Parameter :
 *   ucBufferIndex :            Register address to receive data from device(1 byte)
 *   pucData       :              The starting address of the data buffer
 *   unDataLength  :           The length of data
 * Return value :
 *   1  Success
 *   0  Fail
 *****************************************************************************/
extern void Neoway_i2c_send_ext8( U8 ucBufferIndex, kal_uint8* pucData, kal_uint32 unDataLength);

/*****************************************************************************
 * Definition :
 *   The module writes data to the I2C slave device
 * Parameter :
 *   ucBufferIndex :            Register address to receive data from device(1 byte)
 *   pucData       :              The starting address of the data buffer
 *   unDataLength  :           The length of data
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_i2c_receive_ext8(U8 ucBufferIndex, kal_uint8* pucData, kal_uint32 unDataLength);

/*****************************************************************************
 * Definition :
 *   The module opens the SPI device
 * Parameter :
 *   port                       There is only one port for SPI devices: 0
 * Return value :
 *   Not 0                    Successfully access to SPI device handle
 *   0                          Indicates failure to open SPI device
 *****************************************************************************/
extern U32 Neoway_SPI_Open(U32 port);

/*****************************************************************************
 * Definition :
 *   Module closes SPI device
 * Parameter :
 *   handle	                    SPI device handle
 * Return value :
 *   1                          Indicates success to close SPI device
 *   0                          Indicates failure to close SPI device
 *****************************************************************************/
extern U32 Neoway_SPI_Close(SPI_HANDLE handle);

/*****************************************************************************
 * Definition :
 *   Configure SPI device information
 * Parameter :
 *   handle       :                SPI device handle
 *   pConfigParam :             Parameter configuration
 * Return value :
 *   1                          Indicates success to configure SPI device
 *   0                          Indicates failure to configure SPI device
 *****************************************************************************/
extern U32 Neoway_SPI_Configure(SPI_HANDLE handle, SPI_CONFIG_PARAM_T * pConfigParam);//, SPI_CONFIG_PARAM_T* pConfigParam

/*****************************************************************************
 * Function :
 *   Neoway_spi_write
 * Description :
 *   The module writes data to SPI slave device.
 * Parameter :
 *   handle  :                  SPI device handle. Return by spi_open().
 *   pBuffer :                  The data buffer used for output
 *   length  :                  The data length of a package.(Unit: bytes) If count >1, the length must be multiples of 4. 
 *   count   :                  Package number. If count >1, the length must be multiples of 4.
 *   fCB     :                  When the transport completes, this callback function is specified
 *                              If fCB is specified, the SPI device uses the interrupt mode. This API is asynchronous.
 *                              If fCB is NULL, the SPI device uses polling mode. This API is synchronous.
 * Return value :
 *   Returns a SPI result code
 * Example :
 *  <code>
 *   SPI_HANDLE handle;
 *   SPI_CONFIG_PARAM_T param;
 *   handle = spi_open(0);
 *   // ...
 *   spi_configure(handle, &amp;param);
 *   
 *   // Synchronous call.
 *   spi_write(handle, spi_test_buffer1, 1024, 1, NULL);
 *   
 *   // Asynchronous call.
 *   spi_write(handle, spi_test_buffer1, 1024, 1, spi_test_cb);
 *   //Waiting for events to be set up in callback functions
 *   // ...
 *   spi_close(handle);
 *  </code> 
 *****************************************************************************/
extern U32 Neoway_SPI_Write(SPI_HANDLE handle, void* pBuffer, U32 length, U32 count, SPI_CALLBACK fCB);

/*****************************************************************************
 * Function  :
 *   Neoway_spi_read
 * Description :
 *   The module reads data from SPI slave device.
 * Parameter :
 *   handle  :                  SPI device handle. Return by spi_open().
 *   pBuffer :                  The data buffer used for input.
 *   length  :                  The data length of a package.(Unit: bytes) If count >1, the length must be multiples of 4.
 *   count   :                  Package number. If count >1, the length must be multiples of 4.
 *   fCB     :                  When the transport completes, this callback function is specified
 * 		                        If fCB is specified, the SPI device uses the interrupt mode. This API is asynchronous. 
 * 		                        If fCB is NULL, the SPI device uses polling mode. This API is synchronous.
 * Return value :
 *   Returns a SPI result code
 * Example :
 *  <code>
 *   SPI_HANDLE handle;
 *   SPI_CONFIG_PARAM_T param;
 *   handle = spi_open(0);
 *   // ...
 *   spi_configure(handle, &amp;param);
 * 
 *   // Synchronous call.
 *   spi_read(handle, spi_test_buffer2, 1024, 1, NULL);
 * 
 *   // Asynchronous call.
 *   spi_read(handle, spi_test_buffer2, 1024, 1, spi_test_cb);
 *   //Waiting for events to be set up in callback functions
 *   // ...
 *   spi_close(handle);
 *  </code>
 *****************************************************************************/
extern U32 Neoway_SPI_Read(SPI_HANDLE handle, void* pBuffer, U32 length, U32 count, SPI_CALLBACK fCB);

/*****************************************************************************
 * Definition :
 *   Microsecond delay
 * Parameter :
 *   delay                      U32  Unit: Microsecond
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_us_delay(kal_uint32 delay);

/*****************************************************************************
 * Definition :
 *   Set trigger time and trigger condition of alarm clock
 * Parameter :
 *   rtc_time  :                Trigger time
 *   condition :                Trigger condition
 *                              0 : Not trigger
 *                              1 : The alarm clock is triggered by the same seconds.
 *                              2 : The alarm clock is triggered by both the same minutes and seconds.
 *                              3 : The alarm clock is triggered by the same hours,minutes and seconds.
 *                              4 : The alarm clock is triggered by the same days,hours,minutes and seconds.
 *                              6 : The alarm clock is triggered by the same months,days,hours,minutes and seconds.
 *                              7 : The alarm clock is triggered by the same years,months,days,hours,minutes and seconds.
 * Return value :
 *   void
 *****************************************************************************/
extern void Neoway_SetAlarm(NeowayRtcStruct * rtc_time,U8 condition);

/*****************************************************************************
 * Definition :
 *   Output control of module VMC pin
 * Parameter :
 *   enable  : Open VMS or not
 *        0  : Close
 *        1  : Open
 *   voltage : Voltage setting of VMC
 *        0  : 2.8V(default)
 *        1  : 3.0V
 *        2  : 3.3V
 * Return value :
 *   1 Success
 *   0 Fail
 *****************************************************************************/
extern void Neoway_VMC_enable(kal_bool enable, U8 voltage);

/*****************************************************************************
 * Definition :
 *   MD5 check computation
 * Parameter :
 *   databuf     :                Checked data
 *   md5_out[32] :             Output result
 *   size        :                  The size of the input data
 * Return value :
 *   void
 *****************************************************************************/
extern void  neoway_caculate_md5_checksum(kal_uint8 *databuf, kal_uint8 md5_out[32],kal_uint16 size);

/*****************************************************************************
 * Definition :
 *   Play audio via file path
 * Parameter :
 *   file_name :                The path to play audio is wide characters￡?L"C://test.amr"
 * Return value :
 *   0->success
 *****************************************************************************/
S32 neoway_audio_play_file(void *file_name);

/*****************************************************************************
 * Definition :
 *   Play audio by specifying data format
 * Parameter :
 *   data     :                  Playing data such as mp3/amr, etc.
 *   data_len :                The length of data
 *   format   :                 Like NeowayMdiFormat
 * Return value :
 *   0->success
 *****************************************************************************/
S32 neoway_audio_play_string(U8 *data, U32 data_len, U8 format);
/*****************************************************************************
 * Definiton :
 *   Login the FTP server by the ip address, port, user name and password
 * Parameter :
 *   str_ip                      ip address    
 *   str_port                   port              
 *   str_user                   user name
 *   str_pwd                   password
 * Return value :
 *   0                            success
 *****************************************************************************/
extern bool neoway_user_ftp_login_func(char *str_ip,char *str_port,char *str_user,char *str_pwd);
/*****************************************************************************
 * Definiton :
 *   Exit the FTP server that is currently logged in by the user
 * Parameter :
 *   void
 * Return value  :
 *   0                            success            
 *****************************************************************************/
extern bool neoway_user_ftp_logout_func(void);
/*****************************************************************************
 * Definiton:
 *   Uploading data to the FTP server
 * Parameter:
 *   str_filename :          filename
 *   str_type :                File transfer mode      1:ASCII  2:Binary
 *   str_mode :              Operation mode         1:STOR   2:APPE
 *   str_size :                Data length, the maximum length must not exceed 1024
 * Return value :
 *   0                            success
 *****************************************************************************/
extern bool neoway_user_ftp_put_func(char *str_filename,char *str_type,char *str_mode,char *str_size);
/*****************************************************************************
 * 定义 :
 *   初始化PWM函数
 * 参数 :
 *   freq:  pwm频率，4K~13M
 *   duty:  占空比， 0~100
 *   pin:  GPIO，只支持NEOWAY_GPIO_3和NEOWAY_GPIO_13
 * 返回值 :
 *   void
 * 注意 :
 *****************************************************************************/
extern void Neoway_PWM_13M_Configure(U32 freq, U8 duty,U8 pin);

/*****************************************************************************
 * 定义 :
 *   启动PWM函数
 * 参数 :
 *   pin:  GPIO，只支持NEOWAY_GPIO_3和NEOWAY_GPIO_13
 * 返回值 :
 *   void
 * 注意 :
 *****************************************************************************/
extern void Neoway_PWM_Start(U8 pin);

/*****************************************************************************
 * 定义 :
 *   停止PWM函数
 * 参数 :
 *   pin:  GPIO，只支持NEOWAY_GPIO_3和NEOWAY_GPIO_13
 * 返回值 :
 *   void
 * 注意 :
 *****************************************************************************/
extern void Neoway_PWM_Stop(U8 pin);
#endif
#endif
