#ifndef __NEOWAY_MESSAGE_H__
#define __NEOWAY_MESSAGE_H__

#include "neoway_openplatform.h"
#include "neoway_analysis_sms.h"

/*******************************************************************************************/
// Here NEO_MAX_SEND_AT_LEN is changed from 120 to 600
#define NEO_MAX_SEND_AT_LEN  500  	// The maximum length of the AT command character string
#define NEO_MAX_SEND_DATA_LEN  600  // The maximum length of the data sent by AT commands
/*******************************************************************************************/

typedef enum 
{
	AT_IDLE,//Idle status. No AT command is sent.
	AT_SENDING,//Sending
	AT_WAIT_DATA,//Waiting for data input
	AT_SENDING_DATA//Sending data
}NeowayAtSendStateEnum;//AT data sending

typedef enum
{
	GSM_IDLE,
	GSM_START,
	GSM_ALERING,
	GSM_RING,
	GSM_NOSIM,
	GSM_CONNECT,
	GSM_SIGNAL_BAD,
	GSM_NORMAL,
	GSM_REP
}NeowayGSMLedStateMachineEnum;

typedef enum 
{
	CMD_NULL,
	CMD_CSQ,
	CMD_CREG,
	CMD_TCPSEND,
	CMD_CMGS,
	CMD_GPSPWR,
	CMD_PHONE,
	CMD_AT,
	CMD_INIT,
	CMD_TCP0,
	CMD_TCP0_SETUP,
	CMD_TCP1,
	CMD_TCP1_SETUP,
	/*****************/
	CMD_HTTP,
	CMD_HTTP_SETUP,
	/*****************/
	CMD_MQTT,
	CMD_MQTT_SETUP,
	/*****************/
}NeowayCmdEnum;//State machine

typedef struct 
{
	S8 send_str[NEO_MAX_SEND_AT_LEN];
	U32 str_length;
	S8 send_data[NEO_MAX_SEND_DATA_LEN];
	U32 data_length;
	NeowayCmdEnum cmd;//Commands to be sent
	NeowayAtSendStateEnum at_send_state;
}Neo_Send_At_Info;

typedef struct 
{
	Neo_Send_At_Info * head_position;
	Neo_Send_At_Info * end_position;
	int				  total_item;
}NeowaySendAtInfoState;

typedef struct
{
	S8 buffer[2048+2];
	U16 last_lenth;//Length of character strings that has not been processed last time. If OD OA is not found at the end of data processed last time, the remaining character string will be processed next time.
	U16 start_position;//The start position of the response character string (excluding 0D 0A), 0 by default
	U16 column;//The sequence of the character after 0d0a, 0 by default
	U8 tag_num;//End symbol, 1 for 0D, otherwise 0
}Neo_AtResponseDistill;//Extract OK  ERROR from the response

/**************************timer_id's declaration*********************************************/
extern NeowayTimerId neoway_at_stream;
extern NeowayTimerId neoway_to_send_at;//Send AT commands in the queue.
extern NeowayTimerId neoway_at_send_overtime;
extern NeowayTimerId neoway_fota_strart;
/******************************************************************************************/
extern Neo_Send_At_Info gNeo_send_at_info_link[20];	//Send SMS. Making call through TCP data is in the saving queue.
extern NeowaySendAtInfoState gNeo_send_at_info_state;
extern Neo_Send_At_Info gNeo_at_info;

extern NeowayGSMLedStateMachineEnum gNeo_gsm_state_machine;

extern U8 XIIC_register_state,Module_IMEI_Number[50];
extern U8 gNeo_register_state, gNeo_signal_strong; // network control flags 

extern U16 RF_Id_count;// control flag related to house count
extern U8 server_data[500]; // temperory buffer to hold data
extern U16 SEND_DATA;// control flag related to immediate data send

extern char gNeo_imei_str[16];
extern char gNeo_local_ip[16];

extern S8 send_at_command[NEO_MAX_SEND_AT_LEN];
extern S8 send_at_data[NEO_MAX_SEND_DATA_LEN];

extern unsigned char gNeo_MSG_send_count;	// Count message sent to prevent the queue from overflow.
extern Neo_AtResponseDistill gNeo_at_response_parser;

extern BOOL	gNeo_isWatchDog ;
extern BOOL	gNeo_isTcplinkOk ;

extern unsigned char writeData[12];
extern unsigned char readData[1024];
extern unsigned int lenth,readLen;

/**************************Function declaration*********************************************/

extern void Neoway_MessageTimersInit(void);
extern void Neo_SearchAtResponse(U8 *Buffaddr, U16 Length, NeowayModuleTypeEnum mod_id);
extern void Neo_AT_ReceiveManage(U8 *buff_ptr, U16 len, NeowayModuleTypeEnum mod_id);
extern void Neo_AtInit(void);
extern NeowayBoolEnum Neo_SendAT(NeowayCmdEnum cmd,S8* send_str,U32 str_length,S8* send_data,U32 data_length);
extern void Neo_ATSendCmd(void);
extern void Neo_ATSendData(void);
extern void Neo_ATSendError(void);
extern void Neo_ATSendOvertime(void);
extern void Neo_ATSendOK(void);
extern void Neo_SendNextAT(void);


#endif  // End-of __NEOWAY_MESSAGE_H__

