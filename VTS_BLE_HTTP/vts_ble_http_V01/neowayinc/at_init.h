#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"

typedef enum 
{
	SM_IDLE,
	SM_AT_SENDING,
	SM_AT_SEND_OK,
	SM_CSCS_SENDING,
	SM_CSCS_SEND_OK,
	SM_CNMI_SENDING,
	SM_CNMI_SEND_OK,
	SM_IMEI_SENDING,
	SM_IMEI_SEND_OK,
	SM_CGSN_SENDING,
	SM_CGSN_SEND_OK,
	SM_CCID_SENDING,
	SM_CCID_SEND_OK,
	SM_CSQ_SENDING,
	SM_CSQ_SEND_OK,
	SM_CREG_SENDING,
	SM_CREG_SEND_OK,
	SM_GPS_SENDING,
	SM_GPS_SEND_OK,
	SM_IPR_SENDING,
	SM_IPR_SEND_OK,
	SM_INIT_OK,
	SM_XIIC_SENDING,
	SM_XIIC_SEND_OK,
	SM_XIIC_Q_SENDING,
	SM_XIIC_Q_SEND_OK,
	SM_UPDATETIME_SENDING,
	SM_UPDATETIME_SEND_OK,
	SM_CIPGSMLOC_SENDING,
	SM_CIPGSMLOC_SEND_OK,
	
}NeowayATInitStateMachineEnum;//Initialize AT state machine

/**************************function declaration*********************************************/

/********************************************************************************************/

/**************************message id variable declaration***********************************/
extern NeowayATInitStateMachineEnum gNeo_at_init_state_machine;
/********************************************************************************************/
#endif