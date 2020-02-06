/******************************************************************************
* File Name	: acc_gyro.c
* Author	: Joe Joy 
*			  Software Engineer, Royal Elegance Technologies, Bangalore.
* Description	: Finding angle,acceleration & velocity from accelerometer & gyroscope (upside down)
******************************************************************************/

#include <math.h>
#include<stdlib.h>
#include "i2c.h"
#include "acc_gyro.h"

unsigned char RP_Buff[50];
unsigned char Acc_Buff[50];

U32 prev_time,current_time;
float time_sec;
U8 first=1;  //for checking first iteration
char Buffer[8],i2c_buf;
S16 resx,resy,resz;
float dpsx,dpsy,dpsz,roll_acc,pitch_acc;
float accx,accy,accz,mod_accz,vel_x,vel_y,vel_z;
const float accx_avg_const,accy_avg_const,accz_avg_const;
float accx_var,accy_var,accz_var,vel_ms;

float y,vel_max;
float accx_factor,accy_factor,accz_factor;

const float accx_avg_const=0.4867,accy_avg_const=.0001,accz_avg_const=9.9242;
float accx_var,accy_var,accz_var;
float acc_x,acc_y,acc_z,mod_acc_z,vel_x,vel_y,vel_z,acc_x_avg,acc_y_avg,acc_z_avg;
float roll=0.0,pitch=0.0,roll_acc=0.0,pitch_acc=0.0;
float acc,vel_kh,vel_ms;
float resf,g,dpsx,dpsy,dpsz,k,pitch_1,yaw=0;
float dpsx_avg,dpsx_var,dpsy_avg,dpsy_var,dpsz_avg,dpsz_var;
const float dpsx_avg_const=2.8013,dpsy_avg_const=-6.0169,dpsz_avg_const=-0.8835;
float test;
float vel_ms_prev,vel_min;
S16 resx,resy,resz,new_resz;
U8 flag=0,flag_a=0;

void get_accelerometer_data(S16* resx,S16* resy,S16* resz)
{
	i2c_read(0x28,&i2c_buf);
	Buffer[2]=i2c_buf;
	i2c_read(0x29,&i2c_buf);
	Buffer[3]=i2c_buf;
	
	*resx=Buffer[3];
	*resx=*resx<<8;
	*resx=*resx|Buffer[2];
	
	i2c_read(0x2A,&i2c_buf);
	Buffer[2]=i2c_buf;
	i2c_read(0x2B,&i2c_buf);
	Buffer[3]=i2c_buf;
	
	*resy=Buffer[3];
	*resy=*resy<<8;
	*resy=*resy|Buffer[2];
	*resy=-*resy;                              //since accelerometer upside down
	
	i2c_read(0x2C,&i2c_buf);
	Buffer[2]=i2c_buf;
	i2c_read(0x2D,&i2c_buf);
	Buffer[3]=i2c_buf;
	
	*resz=Buffer[3];
	*resz=*resz<<8;
	*resz=*resz|Buffer[2];
	*resz=-*resz;                             //since accelerometer upside down
}
void get_gyro_data(S16* resx,S16* resy,S16* resz)
{
		i2c_read(0x22,&i2c_buf);
		Buffer[2]=i2c_buf;
		i2c_read(0x23,&i2c_buf);
		Buffer[3]=i2c_buf;
		
		*resx=Buffer[3];
		*resx=*resx<<8;
		*resx=*resx|Buffer[2];
				
		i2c_read(0x24,&i2c_buf);
		Buffer[2]=i2c_buf;
		i2c_read(0x25,&i2c_buf);
		Buffer[3]=i2c_buf;
		
		*resy=Buffer[3];
		*resy=*resy<<8;
		*resy=*resy|Buffer[2];
		
		i2c_read(0x26,&i2c_buf);
		Buffer[2]=i2c_buf;
		i2c_read(0x27,&i2c_buf);
		Buffer[3]=i2c_buf;
		
		*resz=Buffer[3];
		*resz=*resz<<8;
		*resz=*resz|Buffer[2];
}
void find_dps(float* dpsx,float* dpsy,float* dpsz)
{
	get_gyro_data(&resx,&resy,&resz);
	
	*dpsx=(resx*8.75)/1000.0;					
	*dpsy=(resy*8.75)/1000.0;	
	*dpsz=(resz*8.75)/1000.0;
}
void find_angle_with_only_gyro(void)
{
	dpsx_var=dpsx-dpsx_avg_const;
	if((dpsx_var>0.4)||(dpsx_var<-0.4))
	pitch+= dpsx*(.038);
	
	dpsy_var=dpsy-dpsy_avg_const;
	if((dpsy_var>0.4)||(dpsy_var<-0.4))
	roll+= dpsy*(.038);
		
	dpsz_var=dpsz-dpsz_avg_const;
	if((dpsz_var>0.4)||(dpsz_var<-0.4))
	yaw+= dpsz*(.038);
	
}
void find_acceleration(void)
{	
	find_angle_using_filter(&roll,&pitch,.93); 
	
	accx=resx*((9.8*0.061)/1000);              // converting acceleration to in units of m/s^2
	accy=resy*((9.8*0.061)/1000);              
	accz=resz*((9.8*0.061)/1000);              
	
	//Neoway_Print("before acc x,y,z:%f,%f,%f\r",accx,accy,accz);	
	//Neoway_Print("roll,pitch:%f,%f\r",roll,pitch);
	
	accx=(9.8*sin(roll*(3.14/180))-accx)/cos(roll*(3.14/180.0));           //finding x direction acceleration even if tilted
	
	accy=(9.8*sin(pitch*(3.14/180))-accy)/cos(pitch*(3.14/180.0));         //finding y direction acceleration even if tilted
	
	acc=sqrt(accx*accx + accy*accy);               // final acceleration
	
	/* Neoway_UartSend(NEOWAY_UART_PORT_2,"**********************\r",strlen("**********************\r"));
	sprintf(RP_Buff,"Roll ,pitch : %f, %f\r",roll,pitch);					
	Neoway_UartSend(NEOWAY_UART_PORT_2,RP_Buff,strlen(RP_Buff));
	sprintf(Acc_Buff,"Accelerometer : %f\r",acc);
	Neoway_UartSend(NEOWAY_UART_PORT_2,Acc_Buff,strlen(Acc_Buff));
	memset(RP_Buff,0,sizeof(RP_Buff));
	memset(Acc_Buff,0,sizeof(Acc_Buff)); */
	
	/* if(abs(roll)>abs(pitch))
	accz=(accz-9.8*cos(roll*(3.14/180)))*sin(roll*(3.14/180));
    else if(abs(pitch)>abs(roll))
	accz=(accz-9.8*cos(pitch*(3.14/180)))*sin(pitch*(3.14/180)); */

	//Neoway_Print("acc y:%f\r",accy);

	//accx=prec(accx);
	//accy=prec(accy);
	//accz=prec(accz);
	//mod_accz=prec(mod_accz);
	
}
void find_dsp_avg(void)
{	
	if(flag==0)
	{
		dpsx_avg=dpsx;
		dpsy_avg=dpsy;
		dpsz_avg=dpsz;
	}	
	flag=1;
    dpsx_avg=(dpsx+dpsx_avg)/2;
    dpsx_var=dpsx-dpsx_avg;
	
    dpsy_avg=(dpsy+dpsy_avg)/2;    
    dpsy_var=dpsy-dpsy_avg;
	
    dpsz_avg=(dpsz+dpsz_avg)/2;   
    dpsz_var=dpsz-dpsz_avg;	
}
void find_roll_pitch_from_accelerometer(float* roll_acc,float* pitch_acc)
{
	get_accelerometer_data(&resx,&resy,&resz);
	*pitch_acc = atan2(resy,resz) * 57.3; 
	*roll_acc = atan2((resx) , sqrt(resy*resy + resz*resz))*57.3;
	
}
void find_angle_using_filter(float* roll,float* pitch,float k)
{
	find_dps(&dpsx,&dpsy,&dpsz);
	find_roll_pitch_from_accelerometer(&roll_acc,&pitch_acc);

    current_time=Neoway_GetCurrentTime()-prev_time;	
	time_sec=current_time*(1.0/32768.0);
	if(first==1)
		time_sec=0;
	*pitch = pitch_acc*(1.0-k)+ (*pitch+dpsx*time_sec)*k;//0.038
	*roll  = roll_acc*(1.0-k)+(*roll+dpsy*time_sec)*k;
	first=0;
	prev_time=Neoway_GetCurrentTime();			
}

void set_start_angle(void)
{
	find_roll_pitch_from_accelerometer(&roll_acc,&pitch_acc);
	roll = roll_acc+2.6742;  
	pitch = pitch_acc-1.8968;
}
float find_avg(float x)
{
	static int flag=0;
	static float avg;
	
	if(flag==0)
	{		
		avg=x;		
	}
	flag=1;
	avg=(x+avg)/2;	
	//Neoway_Print("avg is %f\r",avg);
	return avg;	
}

float prec(float x)
{
	if(x<0)
		x=-floor(-x*10)/10;
	else 
		x=floor(x*10)/10;
	
	y=x-(int)x;	
	if((y>.0999f && y<.1f)||(y>.1999f && y<.2f)||(y>.2999f && y<.3f)||(y>.3999f && y<.4f)||(y>.4999f && y<.5f)||(y>.5999f && y<.6f)||(y>.6999f && y<.7f)||(y>.7999f && y<.8f)||(y>.8999f && y<.9f)||(y>.9999f && y<1.0f))
	{		
		x=x+0.0001;
	}
    else if((y<-.0999f && y>-.1f)||(y<-.1999f && y>-.2f)||(y<-.2999f && y>-.3f)||(y<-.3999f && y>-.4f)||(y<-.4999f && y>-.5f)||(y<-.5999f && y>-.6f)||(y<-.6999f && y>-.7f)||(y<-.7999f && y>-.8f)||(y<-.8999f && y>-.9f)||(y<-.9999f && y>-1.0f))
	{			
     x=x-0.0001;
	}
	return x;	
}

void find_velocity(void)
{
	static int count=0;
	find_acceleration();	
    //Neoway_Print("res x,y,z:%x,%x,%x\r",resx,resy,resz);
	//Neoway_Print("roll,pitch(degree):%f,%f\r",roll,pitch);
	//Neoway_Print("acc x,y,z(m/s^2):%f,%f,%f\r",accx,accy,(accz-9.8));
	
	if((accx<0.6f&&accx>-0.6f&&accy<0.4f&&accy>-0.4f)==0)
	{		
		vel_y=vel_y+((accy)*(1.0/26.0));	
		vel_x=vel_x+((accx)*(1.0/26.0));
	}

	if(vel_y>vel_max)
		vel_max=vel_y;	
	if(vel_y<vel_min)
		vel_min=vel_y;
	
	//Neoway_Print("Acc_Gyo.C-acc:%f\r",acc);
	//Neoway_Print("vel_y is %f Km_hr\r",(vel_y*18)/5);
	
	//Neoway_Print("vel_y is %f Km_hr\r",(vel_y*18)/5);
	//Neoway_Print("vel_x is %f Km_hr\r",(vel_x*18)/5);
	//Neoway_Print("maximum velocity is %f Km_hr\r",(vel_max*18)/5);
	//Neoway_Print("minimum velocity is %f Km_hr\r",(vel_min*18)/5);
	//current_value();	
}
void current_value(void)
{
	//Neoway_Print("accx,y,z:%f,%f,%f\r",accx,accy,accz);	
	//Neoway_Print("roll,pitch:%f,%f\r",roll,pitch);	
	//Neoway_Print("roll_acc,pitch_acc:%f,%f\r",roll_acc,pitch_acc);	
}