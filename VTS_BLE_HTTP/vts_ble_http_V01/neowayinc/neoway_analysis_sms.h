#ifndef __NEOWAY_ANALYSIS_MSG_H__
#define __NEOWAY_ANALYSIS_MSG_H__

#include "neoway_message.h"
#include "neoway_openplatform.h"
#include "neoway_type.h"

//User information coding
#define PDU_7BIT		0
#define PDU_8BIT		4
#define PDU_UCS2		8

//SMS parameter structure,used for both coding and decoding
//Character strings end with 0
typedef struct {
	S8 SCA[21];			//SMS service center number (SMSC address)	
	S8 TPA[21];			//Destination number or reply number (TP-DA or TP-RA)
	U8 SCA_TYPE;		//SCA_TYPE field
	U8 TP_PDUType;		//The first 8-bit array in the TP-DU field
	U8 TP_MR;				//Information verificaton bit
	U8 TP_DAType;			//Sending number type
	U8 TP_PID;			//User information protocol label (TP-PID)
	S8 TP_DCS;			//User information coding (TP-DCS)
	U8 VP[8];				//Validity period. 0, 1, or 7 bytes
	S8 TP_SCTS[16];		//Service time stamp character string (TC_SCTS), used when receiving
	S8 TP_UD[281];		//Original user information (TP-UD before coding or after decoding)
	S8 index;				//SMS No.,used when reading the SMS message
} Neoway_SM_PARAM_Struct;

//Parsed command types
typedef enum{
	SET_SCA_NUM_CMD,// 710
	SET_DIAL_CMD,// 711
	SET_ECHO_DATA_CMD,
	SET_TIME_CONFIG_CMD,	// 735
	SET_FENCE_CMD,// 751
	SET_READ_FENCE_CMD,// 752
	SET_CANCEL_FENCE_CMD,// 760
	SET_PSD_CHANGE_CMD,	// 770
	SET_USERNAME_CMD,		// 801
	SET_APN_CONFIG_CMD,	// 802
	SET_SVR_ADDR_CMD,	// 803
	SET_SVR_POSI_SCH_CMD,	// 988
	SET_SMS_POSI_SCH_A_CMD,	// 988
	SET_SMS_POSI_SCH_B_CMD,	// 987
	SET_SMS_READ1,		// 901
	SET_SMS_READ2,		// 902
	SET_RESET_PARAM,	// 903
	SET_TIME_CMD,// 567
	SET_OIL_OUT_CMD,//223
	SET_CLOSE_OIL_CMD,//233
	SET_LISTEN_CMD,// 555
	SET_LAC_CI_CMD,// 666
	SET_RESET_CMD,//reset
	SET_INVALID_CMD, //Invalid command
	SET_FORMAT_ERR_CMD, //Command format error
	SET_OIL_OUT_REP,	//Determine the oil and electricity cutoff.
	SET_INVALID
}Neoway_CustomCmdEnum;

typedef struct
{
	char sz_code_gbk[5];
	char sz_code_uni[5];
}NeowayCodeTransStruct;


void Neoway_SM_Struc_Init(Neoway_SM_PARAM_Struct* p_sm_param);
int Neoway_PduString2Bytes(const S8* p_src, U8* p_dst, int n_src_length);
int Neoway_SmsEncodePdu(const Neoway_SM_PARAM_Struct* p_src, S8* p_dst);
int Neoway_SmsDecodePdu(const S8* p_src, Neoway_SM_PARAM_Struct* p_dst);
void Neoway_SendSMS(Neoway_SM_PARAM_Struct* p_sm_param);

BOOL Neoway_GetPDUString(const char* p_src, S8* p_dst);

///////////////////////Protocol-related function//////////////////////////////////
void Neoway_SendSMS(Neoway_SM_PARAM_Struct* p_sm_param);
Neoway_CustomCmdEnum Neoway_GetCustomCmd(S8* p_ud);

S32 Neoway_GetSCANum(S8* p_ud, S8* p_sca_num);
S32 Neoway_GetDailNumber(S8* p_ud, S8* p_num1, S8* p_num2,S8* p_num3/*, S8* p_num4*/);
S32 Neoway_GetEchoParam(S8* p_ud, S8* p_echo_time, S8* p_echo_num);
S32 Neoway_GetTimeRange(S8* p_ud, S32* p_num, S8* p_time_data);
S32 Neoway_GetOUTParam(S8* p_ud, S8* p_radius, S8* p_time, S8* p_latitude, S8* p_longitude, S8*, S8*);
S32 Neoway_GetNewAndOldPassword(S8* p_ud, S8* p_new_psd, S8* p_old_psd);
S32 Neoway_GetUserName(S8* p_ud, S8* p_username);
S32 Neoway_GetAPN(S8* p_ud, S8* p_apn, S8* p_username, S8* p_login_psd);
S32 Neoway_GetCenterSVRAddrPort(S8* p_ud, S8* p_addr, S8* p_port);
BOOL Neoway_GetCmdPassword(S8* p_ud, S8* p_psd, int n_len);
BOOL Neoway_GetCtrPassword(S8* p_ud, S8* p_psd, int n_len);
void Neoway_GetCallNumber(S8* p_clip ,S8* p_phone);

void Neoway_Set_Invalid_Cms_Func(Neoway_SM_PARAM_Struct* p_sm_param);
void Neoway_Set_Format_ERR_Func(Neoway_SM_PARAM_Struct* p_sm_param);

void Neoway_Send_Gps_Url(Neoway_SM_PARAM_Struct* p_sm_param); // 987
void Neoway_Send_Bsc_Url(Neoway_SM_PARAM_Struct* p_sm_param); //987
void Neoway_Loc_Overtime_Req(Neoway_SM_PARAM_Struct* p_sm_param);// 988 overtime request

BOOL Neoway_IsLONAndLAT(S8* buffer);//751


//////////////////////Statement alarm function/////////////////////////
void Neoway_SOS_Gpio_Listening_Mode();
void Neoway_LDP_Listening_Mode(int num);
void Neoway_Blackout_Listening_Mode();	/*Process the alarm for oil and electricity cutoff alarm*/
void Neoway_Fire_Switch_Listening_Mode();
void Neoway_Deal_SOS_Mode();
void Neoway_DealLPDMode();
void Neoway_DealJXMode();
void Neoway_Deal_Blackout_Mode();
void Neoway_SendSOSAlarm(Neoway_SM_PARAM_Struct* p_sm_param);
void Neoway_ReportSOSAlarm();
void Neoway_SendStandbyLPDAlarm(Neoway_SM_PARAM_Struct* p_sm_param);
void Neoway_ReportStandbyLDPAlarm();
void Neoway_SendLDPAlarm(Neoway_SM_PARAM_Struct* p_sm_param);
void Neoway_ReportLDPAlarm();
void Neoway_SendJXAlarm(Neoway_SM_PARAM_Struct* p_sm_param);
void Neoway_ReportJXAlarm();
void Neoway_SendOUTAlarm(Neoway_SM_PARAM_Struct* p_sm_param);
void Neoway_ReportOUTAlarm();
void Neoway_SendBlackoutAlarm(Neoway_SM_PARAM_Struct* p_sm_param);
void Neoway_ReportBlackoutAlarm();
void Neoway_ReportFireupAlarm(BOOL is_fire_up);	 //Report fire up or off alarm to the server
//////////////////////Transparent transmission SMS function//////////////////////////
void Neoway_Trans_SMS_Func(S8* data_buffer ,Neoway_SM_PARAM_Struct* p_sm_param);

///////////////////////////
void Neoway_Set_Echo_Data_Cmd_Rep(char* buffer);//730
void Neoway_Set_OUT_Cmd_Rep(char* buffer) ;// 751
void Neoway_Set_Read_OUT_Cmd_Rep(char* buffer);// 752
void Neoway_Set_Cancel_OUT_Cmd_Rep(char* buffer);
void Neoway_Set_Blackout_Cmd_Rep(char* buffer);//223
void Neoway_Set_Close_Blkout_Cmd_Rep(char* buffer);//233

void Neoway_RepParamByGPRS();

//double atof(char* p_val);


extern NeowayTimerId neoway_timer_sms;
extern S8 sz_pdu_str[512];
extern Neoway_SM_PARAM_Struct sm_para_req;
extern BOOL gNeo_sms_state;	//Receive the SMS.
extern U8 nv_num_buf[21];	//Initial number

#endif
