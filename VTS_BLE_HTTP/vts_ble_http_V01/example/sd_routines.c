#include "sd_routines.h"
//#include "FAT32.h"
#include "spi.h"




volatile unsigned char cardType,SDHC_flag;
volatile unsigned char  buffer[512];
//volatile unsigned char  buffer[512]; 
//******************************************************************
//Function	: to initialize the SD/SDHC card in SPI mode
//Arguments	: none
//return	: unsigned char; will be 0 if no error,
// 			  otherwise the response byte will be sent
//******************************************************************

unsigned char SD_init(void)
{
unsigned char j, response, SD_version;
unsigned int retry=0 ;


SD_CS_DEASSERT;


 for(j=0;j<10;j++)
 {
      spi_write(0xff);   //80 clock pulses spent before sending the first command
 }
      




do
{
  
   response = SD_sendCommand(GO_IDLE_STATE, 0,0x95); //send 'reset & go idle' command
   retry++;
   for(j=0;j<100;j++);
   if(retry>0x20) 
   	  return 1;   //time out, card not detected
   
} while(response != 0x01);



retry = 0;

SD_version = 2; //default set to SD compliance with ver2.x; 
				//this may change after checking the next command
do
{
response = SD_sendCommand(SEND_IF_COND,0x000001AA,0x87); //Check power supply status, mendatory for SDHC card
retry++;
if(retry>0xfe) 
   {
	 // TX_NEWLINE;
	  SD_version = 1;
	  cardType = 1;
	  break;
   } //time out

}while(response != 0x01);

retry = 0;

do
{
response = SD_sendCommand(APP_CMD,0,0x65); //CMD55, must be sent before sending any ACMD command
response = SD_sendCommand(SD_SEND_OP_COND,0x40000000,0x77); //ACMD41

retry++;
if(retry>0xfe) 
   {
     // TX_NEWLINE;
	  return 2;  //time out, card initialization failed
   } 

}while(response != 0x00);

retry = 0;
SDHC_flag = 0;

if (SD_version == 2)
{ 
   do
   {
	 response = SD_sendCommand(READ_OCR,0,0x95);
	 retry++;
	 if(retry>0xfe) 
     {
       //TX_NEWLINE;
	   cardType = 0;
	   break;
     } //time out

   }while(response != 0x00);

   if(SDHC_flag == 1) 
	cardType = 2;
	
   else 
	cardType = 3;
}





return 0; //successful return
}

//******************************************************************
//Function	: to send a command to SD card
//Arguments	: unsigned char (8-bit command value)
// 			  & unsigned long (32-bit command argument)
//return	: unsigned char; response byte
//******************************************************************
unsigned char SD_sendCommand(unsigned char cmd, unsigned long arg,unsigned char crc)
{
unsigned char response, retry=0, status;
U32 i=0;


  

SD_CS_ASSERT;

spi_write(cmd | 0x40); //send command, first two bits always '01'
spi_write(arg>>24);
spi_write(arg>>16);
spi_write(arg>>8);
spi_write(arg);

spi_write(crc);


 while((response = spi_read()) == 0xff) //wait response
 {
 Neoway_us_delay(1);
   if(retry++ > 0xfe) break; //time out error
}

if(response == 0x00 && cmd == 58)  //checking response of CMD58
{
//	for(i=0;i<1000000;i++);
  status = spi_read() & 0x40;     //first byte of the OCR register (bit 31:24)
  if(status == 0x40) 
  {SDHC_flag = 1;  //we need it to verify SDHC card
   Neoway_Print("Card is SDHC\r");
  }
  else SDHC_flag = 0;

  spi_read(); //remaining 3 bytes of the OCR register are ignored here
  spi_read(); //one can use these bytes to check power supply limits of SD
  spi_read(); 
}

spi_read(); //extra 8 CLK
SD_CS_DEASSERT;

return response; //return state
}





unsigned char SD_readSingleBlock(unsigned long startBlock)
{
unsigned char response;
unsigned int j, retry=0;
static unsigned long cnt=0;
//for(j=0;j<1000000;j++);
//Neoway_Print("startBlock %d\r",startBlock);
 response = SD_sendCommand(READ_SINGLE_BLOCK, startBlock,0xff); //read a Block command
 
 if(response != 0x00) return response; //check for SD status: 0x00 - OK (No flags set)
 
SD_CS_ASSERT;



while(spi_read() != 0xfe) //wait for start block token 0xfe (0x11111110)
  if(retry++ > 0xfffe){SD_CS_DEASSERT; return 1;} //return if time-out

for(j=0; j<512; j++) //read 512 bytes
{
	//Neoway_Print("j=%d\r",j);
	//Neoway_us_delay(1000);
	buffer[j] = spi_read();
	}
//Neoway_Print("here0\r");
spi_read(); //receive incoming CRC (16-bit), CRC is ignored here
spi_read();

spi_read(); //extra 8 clock pulses
SD_CS_DEASSERT;
//Neoway_Print("cnt:%d\r",cnt);
//cnt++;                   //to keep count of number of times function called for debugging
 /* Neoway_Print("inside read_single_block\r");

Neoway_Print("buffer is %x\r",buffer[0]);
				Neoway_Print("buffer is %x\r",buffer[1]);
				Neoway_Print("buffer is %x\r",buffer[2]);
				Neoway_Print("buffer is %x\r",buffer[3]);
				Neoway_Print("buffer is %x\r",buffer[4]); */
				//Neoway_Print("buffer 511 is %x\r",buffer[511]);
				//Neoway_Print("buffer 510 is %x\r",buffer[510]);

return 0;
}

//******************************************************************
//Function	: to write to a single block of SD card
//Arguments	: none
//return	: unsigned char; will be 0 if no error,
// 			  otherwise the response byte will be sent
//******************************************************************
unsigned char SD_writeSingleBlock(unsigned long startBlock)
{
unsigned char response;
unsigned int j, retry=0;

 response = SD_sendCommand(WRITE_SINGLE_BLOCK, startBlock,0xFF); //write a Block command
  
 if(response != 0x00) return response; //check for SD status: 0x00 - OK (No flags set)


 
SD_CS_ASSERT;

spi_write(0xfe);     //Send start block token 0xfe (0x11111110)


for(j=0; j<512; j++)    //send 512 bytes data
  spi_write(buffer[j]);

spi_write(0xff);     //transmit dummy CRC (16-bit), CRC is ignored here
spi_write(0xff);

response = spi_read();

if( (response & 0x1f) != 0x05) //response= 0xXXX0AAA1 ; AAA='010' - data accepted
{                              //AAA='101'-data rejected due to CRC error
  SD_CS_DEASSERT;              //AAA='110'-data rejected due to write error
  return response;
}

while(!spi_read()) //wait for SD card to complete writing and get idle
if(retry++ > 0xfffe){SD_CS_DEASSERT; return 1;}

SD_CS_DEASSERT;
spi_write(0xff);   //just spend 8 clock cycle delay before reasserting the CS line
SD_CS_ASSERT;         //re-asserting the CS line to verify if card is still busy

while(!spi_read()) //wait for SD card to complete writing and get idle
   if(retry++ > 0xfffe){SD_CS_DEASSERT; return 1;}
SD_CS_DEASSERT;

return 0;
}




