#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"
 

typedef enum 
{
	/*******************HTTP*******************************/
	SM_HTTP_IDLE,  //// First HTTP command, URl with data should send ,sizeof(data_to_server)
	SM_HTTP_DATA_SENDING,
	SM_HTTP_DATA_SEND_OK,
	SM_HTTP_PORT_SENDING,
	SM_HTTP_PORT_SEND_OK,
	SM_HTTP_SETUP_SENDING,
	SM_HTTP_SETUP_SEND_OK,
	SM_HTTP_ACTION_SENDING,
	SM_HTTP_ACTION_SEND_OK,
	SM_HTTP_CLOSE_SENDING,
	SM_HTTP_CLOSE_SEND_OK,
	SM_HTTP_INIT_OK
	/*******************************************************/
}NeowayHTTPStateMachineEnum;//Initialize HTTP state machine

/****************************variable declaration********************************************/
extern unsigned char Server_URL[100];
extern unsigned char HttpAction_Buff[50]; 
extern unsigned char data_to_server[500];
/********************************************************************************************/

extern NeowayHTTPStateMachineEnum HTTP_Server_State; 


#endif