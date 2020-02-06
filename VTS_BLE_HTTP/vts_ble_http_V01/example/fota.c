#ifdef __EXAMPLE_HELLWORLD__

#include "neoway_openplatform.h"
#include "fota.h"

/****************************Used functions***************************************************/
void update_available(void);
void Neoway_FtpUpdate(NeowayFtpUpdateStataEnum stata,NeowayModuleTypeEnum mod);
/********************************************************************************************/
/****************************variable declaration***************************************************/
 U8 app_ver[10]={0};
 U8 app_version[21]={0};
/********************************************************************************************/
/****************************CONTROL FLAG'S**************************************************/
 U16 update_fail_count=0;
/********************************************************************************************/

/*****************************************************************************
 * Definition: update_available
 * Parameter: void
 * Return value: void
 *****************************************************************************/
void update_available(void)
{
	Neoway_Print("enter to update_available function");
	Neoway_Print("Neoway SETUP");
	Neoway_remote_param_setting (1,"49.206.24.160","21","ftp1user","RETFTP");// set the remote address, port number, user_id, password 
	Neoway_Print("Neoway PATH SETUP");
	Neoway_remote_path_set("ble//"); // Set the storage path of the upgrade file when the FTP is remotely upgraded
	Neoway_Print("Wait.....");
	Neoway_StartFtpUpdate(); // When the function is called, the module will automatically connect to the specified FTP to upgrade
}

/*****************************************************************************
 * Definition: Neoway_FtpUpdate
 * Parameter: NeowayFtpUpdateStataEnum stata,NeowayModuleTypeEnum mod
 * Return value: void
 *****************************************************************************/
void Neoway_FtpUpdate(NeowayFtpUpdateStataEnum stata,NeowayModuleTypeEnum mod)
{
	switch(stata)
	{
		case NEOWAY_UPDATE_FAILE:
				Neoway_Print("Update Fail!");
				if(update_fail_count == 1){
					Neoway_SendMsgTask(mod,NEOWAY_MOD_USER1,NEOWAY_FOTA_END_NOTIFY,NULL,0);
					update_fail_count=0;
				}
				else {
					update_fail_count += 1;
					Neoway_StartFtpUpdate();
				}
	   		break;
		case NEOWAY_UPDATE_ALREADY:
				Neoway_Print("Don't need Update!");	
				Neoway_ReadAppVersion(app_ver);
			    sprintf(app_version,"\"app_version\":\"%s\"", app_ver);
				Neoway_SendMsgTask(mod,NEOWAY_MOD_USER1,NEOWAY_FOTA_END_NOTIFY,NULL,0);
	   		break;
		case NEOWAY_UPDATE_OVER:
				Neoway_Print("Update Success!!!");
				Neoway_Print("\r*****Module Restarting*****\r");
				Neoway_Reset(); // Restart the module
	   		break;
		default :
			break;
	}
}

#endif