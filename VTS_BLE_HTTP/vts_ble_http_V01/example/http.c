#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"
#include "http.h"

/****************************variable declaration********************************************/
unsigned char Server_URL[]="AT+HTTPPARA=url,103.5.134.141/api/update_scanned_houses\r";
unsigned char HttpAction_Buff[50]={0};
unsigned char data_to_server[500]={0}; // ="\{ \"data\":\[ \{ \"_id\":\"11145390\", \"scan_time_stamp\":\"11:1:0,30-12-19\" \},\{ \"_id\":\"03802115\", \"scan_time_stamp\":\"11:1:8,30-12-19\" \}, \{ \"_id\":\"11145390\", \"scan_time_stamp\":\"11:1:13,30-12-19\" \} \] \}\r";
/********************************************************************************************/
NeowayHTTPStateMachineEnum HTTP_Server_State = SM_HTTP_INIT_OK;

#endif