/******************************************************************************
* File Name	: i2c.c
* Author	: Joe Joy 
*			  Software Engineer, Royal Elegance Technologies, Bangalore.
* Description	: I2C driver codes for Neoway N10.
******************************************************************************/



#include "i2c.h"

U8 ret;


void i2c_pin_config(void)
{
	
	Neoway_GpioModeConfigure(scl,0);				//Configure GPIO 43 as SCL of I2C.
	Neoway_GpioDirectionConfigure(scl,1);			//Output

	Neoway_GpioModeConfigure(sda,0);				//Configure GPIO 44 as SDA of I2C
	Neoway_GpioDirectionConfigure(sda,1);			//Output
	
	Neoway_GpioWrite(scl,1);
	Neoway_GpioWrite(sda,1);
	
}

void i2c_start(void)                                        
{
	//Neoway_Print("inside i2c_start\r");
	Neoway_GpioWrite(sda,1);            
	Neoway_us_delay(10);
	//ret=Neoway_GpioRead(sda);

	Neoway_GpioWrite(scl,0);
	Neoway_us_delay(clk_low_time);

	Neoway_GpioWrite(scl,1);
	Neoway_us_delay(clk_high_time);

	Neoway_GpioWrite(sda,0); 
	Neoway_us_delay(10);

	Neoway_GpioWrite(scl,0);
	Neoway_us_delay(clk_low_time);

	Neoway_GpioWrite(sda,1); 
	Neoway_us_delay(10);

}


void i2c_stop(void)                         
{
	//Neoway_Print("inside i2c_stop\r");
	Neoway_GpioWrite(sda,0); 
	Neoway_us_delay(10);             

	Neoway_GpioWrite(scl,1);
	Neoway_us_delay(clk_high_time);
	Neoway_GpioWrite(sda,1); 
	Neoway_us_delay(10); 
	Neoway_GpioWrite(scl,0);
	Neoway_us_delay(clk_low_time);
}



U8 i2c_tx(unsigned char d)                                    
{
	
	char x;
	U8 b;
	//Neoway_Print("inside i2c_tx\r");
	for(x=8; x; x--) 
	{
		if(d&0x80) 
		Neoway_GpioWrite(sda,1);
		else 
		Neoway_GpioWrite(sda,0);
		Neoway_GpioWrite(scl,1);
		Neoway_us_delay(clk_high_time);
		ret=Neoway_GpioRead(sda);
		//Neoway_Print("%d",ret);
		d <<= 1;
		Neoway_GpioWrite(scl,0);
		Neoway_us_delay(clk_low_time);
	}
	Neoway_GpioWrite(sda,1);
	Neoway_GpioWrite(scl,1);
	Neoway_us_delay(clk_high_time);
	b = Neoway_GpioRead(sda);         // possible ACK bit
	Neoway_GpioWrite(scl,0);
	return b;
}


U8 i2c_rx(char ack)                         
{
	
	U8 x, d=0;
	//Neoway_Print("inside i2c_rx\r");
	Neoway_GpioWrite(sda,1); 
	for(x=0; x<8; x++) 
	{
		d <<= 1;
		do {
			Neoway_GpioWrite(scl,1);
		}
		while(Neoway_GpioRead(scl)==0);    // wait for any SCL clock stretching
		Neoway_us_delay(10);
		ret = Neoway_GpioRead(sda);
		//Neoway_Print("%d",ret);
		if(Neoway_GpioRead(sda)==1) 
		d |= 1;
		Neoway_GpioWrite(scl,0);
	} 
	if(ack) 
	Neoway_GpioWrite(sda,0);
	else 
	Neoway_GpioWrite(sda,1);
	Neoway_GpioWrite(scl,1);
	Neoway_us_delay(clk_high_time);             
	Neoway_GpioWrite(scl,0);
	Neoway_GpioWrite(sda,1); 
	Neoway_us_delay(10);
	return d;
}

void i2c_read(U8 read_adr,char* buf)                   
{
	
	i2c_start();                         
	ret=i2c_tx(0xD6);
	//Neoway_Print("slave address ack bit is %d\r",ret);
	i2c_tx(read_adr);
	i2c_start();
	ret=i2c_tx(0xD7);
	*buf=i2c_rx(0);
	//Buffer[1]=i2c_rx(0);
	i2c_stop();
		
}
void i2c_write(U8 write_adr,U8 write_value)
{
	i2c_start();
	ret=i2c_tx(0xD6);
	//Neoway_Print("slave address ack bit is %d\r",ret);
	ret=i2c_tx(write_adr);
	//Neoway_Print("register address ack bit is %d\r",ret);
	ret=i2c_tx(write_value);
	//Neoway_Print("write value ack bit is %d\r",ret);
	i2c_stop();
}