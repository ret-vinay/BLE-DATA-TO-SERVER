/******************************************************************************
* File Name	: i2c.c
* Author	: Joe Joy 
*			  Software Engineer, Royal Elegance Technologies, Bangalore.
* Description	: SPI driver codes for Neoway N10.
******************************************************************************/
#include "spi.h"
#include "neoway_openplatform.h"

U8 spi_ret;
U8 count=0;

void spi_config(void)
{
	
	Neoway_GpioModeConfigure(sck,0);				
	Neoway_GpioDirectionConfigure(sck,1);			

	Neoway_GpioModeConfigure(cs,0);				
	Neoway_GpioDirectionConfigure(cs,1);			
	
	Neoway_GpioModeConfigure(miso,0);				
	Neoway_GpioDirectionConfigure(miso,1);
	
	Neoway_GpioModeConfigure(mosi,0);				
	Neoway_GpioDirectionConfigure(mosi,1);
	
	
	
	Neoway_GpioWrite(sck,0);
	Neoway_GpioWrite(miso,1);
	
	
}

void spi_write(U8 buff)
{
	int i;
	U8 spi_ret=0;
	//Neoway_Print("spi write buff is %x\r",buff);
	for(i=0;i<8;++i)
	{
	spi_ret=spi_ret<<1;	
	Neoway_GpioWrite(sck,0);	
	if(buff & 0x80)
	Neoway_GpioWrite(mosi,1);
    else
	Neoway_GpioWrite(mosi,0);
    if(count==0)
    Neoway_us_delay(2);
    else
		spi_delay();
    Neoway_GpioWrite(sck,1);
	
	spi_ret = Neoway_GpioRead(miso)|spi_ret;
	
	if(count==0)
    Neoway_us_delay(2);
    else
		spi_delay();
	
    buff=buff<<1;
	
	
	}
	
}

U8 spi_read(void)
{
	int i;
	U8 spi_ret=0;
	U8 buff=0xFF;
	
	for(i=0;i<8;++i)
	{
	spi_ret=spi_ret<<1;	
	Neoway_GpioWrite(sck,0);	
	if(buff & 0x80)
	Neoway_GpioWrite(mosi,1);
    else
	Neoway_GpioWrite(mosi,0);
	
	
	if(count==0)
    Neoway_us_delay(2);
    else
		spi_delay();
    Neoway_GpioWrite(sck,1);
	
	spi_ret = Neoway_GpioRead(miso)|spi_ret;
	
	if(count==0)
	Neoway_us_delay(2);
    else
		spi_delay();
	
	
    buff=buff<<1;
	
	
	}
	
	return spi_ret;
}




void spi_pin_config(void)
{
	
	Neoway_GpioModeConfigure(sck,0);				
	Neoway_GpioDirectionConfigure(sck,1);			
    
	Neoway_GpioModeConfigure(cs,0);				
	Neoway_GpioDirectionConfigure(cs,1);			
	
	Neoway_GpioModeConfigure(miso,0);				
	Neoway_GpioDirectionConfigure(miso,1);
	
	Neoway_GpioModeConfigure(mosi,0);				
	Neoway_GpioDirectionConfigure(mosi,1);
	
	
	
	Neoway_GpioWrite(sck,0);
	
	
}

//************************************************************************************
//Function: set_spi_delay_count
//         Use this function only if spi write and read speed is low
//************************************************************************************


void set_spi_delay_count(unsigned char set_value)         
{
count= set_value;

}
void spi_delay(void)                              
{
	volatile int i,j;
	
	for(i=0;i<count;++i)
		for(j=0;j<255;++j);
	
}

