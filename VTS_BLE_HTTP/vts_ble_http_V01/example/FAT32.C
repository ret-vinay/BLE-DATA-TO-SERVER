/******************************************************************************
* File Name	    : FAT32.C
* Author	    : Hari Babu T D. 
*			      Software Engineer, Elegance Technologies, Bangalore.
* Description	: Definitions of the FAT32 file system operations  (Modified for Neoway N10).
******************************************************************************/


#include "FAT32.h"
//#include "UART_routines.h"
#include "SD_routines.h"
#include "neoway_openplatform.h"

volatile unsigned long firstDataSector, rootCluster, totalClusters;
volatile unsigned short  bytesPerSector, sectorPerCluster, reservedSectorCount;
unsigned long unusedSectors, appendFileSector, appendFileLocation, fileSize, appendStartCluster;

unsigned char freeClusterCountUpdated;
struct BS_Structure *bpb=NULL; //mapping the buffer onto the structure
struct MBRinfo_Structure *mbr;

unsigned char getBootSectorData (void)
{



struct partitionInfo_Structure *partition;
unsigned long dataSectors;
unsigned char first_byte=0x00;

unusedSectors = 0;

SD_readSingleBlock(0x00000000);                           
//Neoway_Print("Entering getBootSectorData function");

bpb = (struct BS_Structure *)buffer;

//Neoway_Print("bpb->jumpBoot[0]: %x,%x,%x\r",bpb->jumpBoot[0],bpb->jumpBoot[1],bpb->jumpBoot[2]);


if(bpb->jumpBoot[0]!=0xE9 && bpb->jumpBoot[0]!=0xEB)   //check if it is boot sector
{
  mbr = (struct MBRinfo_Structure *) buffer;       //if it is not boot sector, it must be MBR
  
  if(mbr->signature != 0xaa55) 
  {Neoway_Print("its not fat32");
	  return 1;       //if it is not even MBR then it's not FAT32
  }
  partition = (struct partitionInfo_Structure *)(mbr->partitionData);//first partition
  unusedSectors = partition->firstSector; //the unused sectors, hidden to the FAT
  
  SD_readSingleBlock(partition->firstSector);//read the bpb sector
  bpb = (struct BS_Structure *)buffer;
  
  if(bpb->jumpBoot[0]!=0xE9 && bpb->jumpBoot[0]!=0xEB) 
  {
	  Neoway_Print("Cannot access FATvolume id\r");
	  return 1;
  } 
  
  /* Neoway_Print("jumpBoot:%x%x%x\r",bpb->jumpBoot[0],bpb->jumpBoot[1],bpb->jumpBoot[2]);
Neoway_Print("OEMName:%s\r",bpb->OEMName);
Neoway_Print("bytesPerSector:%d\r",bpb->bytesPerSector);
Neoway_Print("sectorPerCluster:%d\r",bpb->sectorPerCluster);

Neoway_Print("reservedSectorCount:%d\r",bpb->reservedSectorCount);
Neoway_Print("numberofFATs:%d\r",bpb->numberofFATs);
Neoway_Print("rootEntryCount:%x\r",bpb->rootEntryCount);
Neoway_Print("totalSectors_F16:%d\r",bpb->totalSectors_F16);
Neoway_Print("mediaType:%x\r",bpb->mediaType);
Neoway_Print("FATsize_F16:%x\r",bpb->FATsize_F16);
Neoway_Print("sectorsPerTrack:%d\r",bpb->sectorsPerTrack);
Neoway_Print("numberofHeads:%d\r",bpb->numberofHeads);
Neoway_Print("hiddenSectors:%d\r",bpb->hiddenSectors);
Neoway_Print("totalSectors_F32:%d\r",bpb->totalSectors_F32);
Neoway_Print("FATsize_F32:%x\r",bpb->FATsize_F32);
Neoway_Print("extFlags:%x\r",bpb->extFlags);
Neoway_Print("FSversion:%x\r",bpb->FSversion);
Neoway_Print("rootCluster:%x\r",bpb->rootCluster);
Neoway_Print("FSinfo:%x\r",bpb->FSinfo);
Neoway_Print("BackupBootSector:%x\r",bpb->BackupBootSector);
Neoway_Print("reserved:%x\r",bpb->reserved);
Neoway_Print("driveNumber:%x\r",bpb->driveNumber);
Neoway_Print("reserved1:%x\r",bpb->reserved1);
Neoway_Print("bootSignature:%x\r",bpb->bootSignature);
Neoway_Print("volumeID:%x\r",bpb->volumeID);
Neoway_Print("volumeLabel:%x\r",bpb->volumeLabel);
Neoway_Print("fileSystemType:%s\r",bpb->fileSystemType);
Neoway_Print("bootEndSignature:%x\r",bpb->bootEndSignature); */ 
}
/*
unsigned long HiddenSectors,NumberofFATs,TotalSectors_F32,FATSize_F32;

	bytesPerSector =from_LE_16((char *)&buffer[11]);
	sectorPerCluster =buffer[13];
	reservedSectorCount = from_LE_16((char *)&buffer[14]);
	rootCluster =from_LE_32((char *)&buffer[44]);
	HiddenSectors=from_LE_32((char *)&buffer[28]);
	NumberofFATs=buffer[16] ;
	FATSize_F32=from_LE_32((char *)&buffer[36]);
	TotalSectors_F32=from_LE_32((char *)&buffer[32]);
	firstDataSector =HiddenSectors+ reservedSectorCount + (NumberofFATs*FATSize_F32);
	dataSectors = TotalSectors_F32- reservedSectorCount- (NumberofFATs*FATSize_F32);
	totalClusters = dataSectors / sectorPerCluster;

transmitString("bytes per cluster-");
transmitHex(INT, bytesPerSector); transmitByte(' ');
 transmitString("sectors per cluster-");
transmitHex(INT, sectorPerCluster); transmitByte(' ');
transmitString("reserverd sector-");
transmitHex(INT, reservedSectorCount); transmitByte(' ');
transmitString("No of FATS-");
transmitHex(INT, NumberofFATs); transmitByte(' ');

transmitString("Fat size 32-");
transmitHex(INT, FATSize_F32); transmitByte(' ');
 transmitString("total sectors-");
transmitHex(INT, TotalSectors_F32); transmitByte(' ');
transmitString("data sector-");
transmitHex(INT, firstDataSector); transmitByte(' ');
transmitString("total cluster-");
transmitHex(INT, totalClusters); transmitByte(' ');

*/
bytesPerSector = bpb->bytesPerSector;

sectorPerCluster = bpb->sectorPerCluster;

reservedSectorCount = bpb->reservedSectorCount;
rootCluster = bpb->rootCluster;// + (sector / sectorPerCluster) +1;
//Neoway_Print("bpb->hiddenSectors:%x\r",bpb->hiddenSectors);

firstDataSector = bpb->hiddenSectors + reservedSectorCount + (bpb->numberofFATs * bpb->FATsize_F32);

dataSectors = bpb->totalSectors_F32
              - bpb->reservedSectorCount
              - ( bpb->numberofFATs * bpb->FATsize_F32);
totalClusters = dataSectors / sectorPerCluster;

if((getSetFreeCluster (TOTAL_FREE, GET, 0)) > totalClusters)  //check if FSinfo free clusters count is valid
     freeClusterCountUpdated = 0;
else
	 freeClusterCountUpdated = 1;

 //Neoway_Print("freeClusterCountUpdated: %d\r",freeClusterCountUpdated);
 
 //Neoway_Print("File system type from fat32.c:%s\r",bpb->fileSystemType);

 //Neoway_Print("bytesPerSector at end:%d\r",bpb->bytesPerSector);
return 0;

}


unsigned  int from_LE_16(char *ptr)
{
	unsigned short temp=0;							//EX prt=04,ptr++=03
	unsigned char num_value=0;
	num_value=*(++ptr);
	temp|=num_value;								//mask second byte and store in temp ex . temp=0x0300
	temp=temp<<8;								//left shift temp 8 times ex 0x03<<8=0x0030
	num_value=*(--ptr);
	temp|=num_value;									//mask first byte and store in temp ex temp=0x0304
	return temp;									//return the value
}
/**********************************************************************************************************
 								Function Name 	: 	from_LE_32
  								Description	   	: 	To receive four 8bit char and merge to long 32bits
 								Arguments 		: 	recive charecter's to be merged
  								Return Type 		:	 merged value is return
***********************************************************************************************************/
unsigned long from_LE_32(char *ptr )
{
	unsigned long temp=0;
	unsigned char num_value=0;
	ptr=ptr+3;							//EX prt=06,ptr+1=05,ptr+2=0x04,ptr+3=0x03
	temp|=*(ptr);								//mask  byte and store in temp ex . temp=0x00000003
	temp=temp<<8;								//left shift temp 8 times ex 0x03<<8=0x00000030
	temp|=*(--ptr);								//mask byte and store in temp ex . temp=0x00000304
	temp=temp<<8;								//left shift temp 8 times ex 0x03<<8=0x00000304
	temp|=*(--ptr);								//mask byte and store in temp ex . temp=0x00030405
	temp=temp<<8;								//left shift temp 8 times ex 0x03<<8=0x00030405
	num_value=*(--ptr);
	temp|=num_value;								//mask  byte and store in temp ex . temp=0x03040506
	return temp;									//return the value
}
//***************************************************************************
//Function: to calculate first sector address of any given cluster
//Arguments: cluster number for which first sector is to be found
//return: first sector address
//***************************************************************************
unsigned long getFirstSector(unsigned long clusterNumber)
{
  return (((clusterNumber - 2) * sectorPerCluster) + firstDataSector);
}

//***************************************************************************
//Function: get cluster entry value from FAT to find out the next cluster in the chain
//or set new cluster entry in FAT
//Arguments: 1. current cluster number, 2. get_set (=GET, if next cluster is to be found or = SET,
//if next cluster is to be set 3. next cluster number, if argument#2 = SET, else 0
//return: next cluster number, if if argument#2 = GET, else 0
//****************************************************************************
unsigned long getSetNextCluster (unsigned long clusterNumber,
                                 unsigned char get_set,
                                 unsigned long clusterEntry)
{
unsigned short FATEntryOffset;
unsigned long FATEntryValue;               //unsigned long *FATEntryValue;
unsigned long FATEntrySector;
unsigned char retry = 0;

//get sector number of the cluster entry in the FAT

FATEntrySector = unusedSectors + reservedSectorCount + ((clusterNumber * 4) / bytesPerSector) ;
//Neoway_Print("FATEntrySector %d\r",FATEntrySector);

//get the offset address in that sector number
FATEntryOffset = (unsigned short) ((clusterNumber * 4) % bytesPerSector);
//Neoway_Print("FATEntryOffset %d\r",FATEntryOffset);
//read the sector into a buffer
while(retry <10)
{
	//Neoway_Print("retry %d\r",retry);
if(!SD_readSingleBlock(FATEntrySector)) break; 
retry++;
}

//get the cluster address from the buffer

//Neoway_Print("&buffer[FATEntryOffset+4]: %d\r",&buffer[FATEntryOffset]);
//Neoway_Print("&buffer[FATEntryOffset+4]: %d\r",&buffer[FATEntryOffset+1]);
//Neoway_Print("&buffer[FATEntryOffset+4]: %d\r",&buffer[FATEntryOffset+2]);
//Neoway_Print("&buffer[FATEntryOffset+4]: %d\r",&buffer[FATEntryOffset+3]);
//while(1);
//FATEntryValue = (unsigned long *) &buffer[FATEntryOffset];

FATEntryValue=((unsigned long)buffer[FATEntryOffset])|(((unsigned long)buffer[FATEntryOffset+1])<<8)|(((unsigned long)buffer[FATEntryOffset+2])<<16)|(((unsigned long)buffer[FATEntryOffset+3])<<24);

//Neoway_Print("clusterEntry : %x\r",clusterEntry);


if(get_set == GET)
  return ((FATEntryValue) & 0x0fffffff);
//Neoway_Print("buffer 20,21,22,23 %x %x %x %x %x\r",buffer[FATEntryOffset],buffer[FATEntryOffset+1],buffer[FATEntryOffset+2],buffer[FATEntryOffset+3],buffer[FATEntryOffset+4]);

//*FATEntryValue = clusterEntry;   //for setting new value in cluster entry in FAT

//Neoway_Print("clusterEntry : %x\r",clusterEntry);
buffer[FATEntryOffset+3]=((clusterEntry)&0xFF000000)>>24;
buffer[FATEntryOffset+2]=((clusterEntry)&0x00FF0000)>>16;
buffer[FATEntryOffset+1]=((clusterEntry)&0x0000FF00)>>8;
buffer[FATEntryOffset]=(clusterEntry)&0x000000FF;

//Neoway_Print("FATEntryValue: %x",*FATEntryValue);
//Neoway_Print("buffer 20,21,22,23 %x %x %x %x %x\r",buffer[FATEntryOffset],buffer[FATEntryOffset+1],buffer[FATEntryOffset+2],buffer[FATEntryOffset+3],buffer[FATEntryOffset+4]);
SD_writeSingleBlock(FATEntrySector);

return (0);
}

//********************************************************************************************
//Function: to get or set next free cluster or total free clusters in FSinfo sector of SD card
//Arguments: 1.flag:TOTAL_FREE or NEXT_FREE, 
//			 2.flag: GET or SET 
//			 3.new FS entry, when argument2 is SET; or 0, when argument2 is GET
//return: next free cluster, if arg1 is NEXT_FREE & arg2 is GET
//        total number of free clusters, if arg1 is TOTAL_FREE & arg2 is GET
//		  0xffffffff, if any error or if arg2 is SET
//********************************************************************************************
unsigned long getSetFreeCluster(unsigned char totOrNext, unsigned char get_set, unsigned long FSEntry)
{
struct FSInfo_Structure *FS;
unsigned char error;

SD_readSingleBlock(unusedSectors + 1);
FS=(struct FSInfo_Structure *) buffer;
//Neoway_Print("FS->leadSignature %x\r",FS->leadSignature);
if((FS->leadSignature != 0x41615252) || (FS->structureSignature != 0x61417272) || (FS->trailSignature !=0xaa550000))
{	
  Neoway_Print("Not FS info\r");
  return 0xffffffff;
}
//Neoway_Print("It is FSinfo\r");
//Neoway_Print("FS->freeClusterCount %d\r",FS->freeClusterCount);
//Neoway_Print("FS->nextFreeCluster %d\r",FS->nextFreeCluster);
 if(get_set == GET)
 {
   if(totOrNext == TOTAL_FREE)
   {
	   
      return(FS->freeClusterCount);
   }
   else // when totOrNext = NEXT_FREE
      return(FS->nextFreeCluster);
 }
 else
 {
   if(totOrNext == TOTAL_FREE)
      FS->freeClusterCount = FSEntry;
   else // when totOrNext = NEXT_FREE
	  FS->nextFreeCluster = FSEntry;
      
      error = SD_writeSingleBlock(unusedSectors + 1);	//update FSinfo
 }
 return 0xffffffff;
}

//***************************************************************************
//Function: to get DIR/FILE list or a single file address (cluster number) or to delete a specified file
//Arguments: #1 - flag: GET_LIST, GET_FILE or DELETE #2 - pointer to file name (0 if arg#1 is GET_LIST)
//return: first cluster of the file, if flag = GET_FILE
//        print file/dir list of the root directory, if flag = GET_LIST
//		  Delete the file mentioned in arg#2, if flag = DELETE
//****************************************************************************
struct dir_Structure* findFiles (unsigned char flag, unsigned char *fileName)
{
unsigned long cluster, sector, firstSector, firstCluster, nextCluster;
struct dir_Structure *dir;
unsigned short i;
unsigned char j;

cluster = rootCluster; //root cluster

while(1)
{
   firstSector = getFirstSector (cluster);

   for(sector = 0; sector < sectorPerCluster; sector++)
   {
     SD_readSingleBlock (firstSector + sector);
	

     for(i=0; i<bytesPerSector; i+=32)
     {
	    dir = (struct dir_Structure *) &buffer[i];

        if(dir->name[0] == EMPTY) //indicates end of the file list of the directory
		{
		  if((flag == GET_FILE) || (flag == DELETE))
		      Neoway_Print("File does not exist! %d\r",dir->name[0]);
		  return 0;   
		}
		if((dir->name[0] != DELETED) && (dir->attrib != ATTR_LONG_NAME))
        {
          if((flag == GET_FILE) || (flag == DELETE))
          {
            for(j=0; j<11; j++)
            if(dir->name[j] != fileName[j]) break;
            if(j == 11)
			{
			  if(flag == GET_FILE)
              {
			    appendFileSector = firstSector + sector;
				appendFileLocation = i;
				appendStartCluster = (((unsigned long) dir->firstClusterHI) << 16) | dir->firstClusterLO;
				fileSize = dir->fileSize;
			    return (dir);
			  }	
			  else    //when flag = DELETE
			  {
			     TX_NEWLINE;
				 transmitString("Deleting..");
				 TX_NEWLINE;
				 TX_NEWLINE;
				 firstCluster = (((unsigned long) dir->firstClusterHI) << 16) | dir->firstClusterLO;
                 
				 //mark file as 'deleted' in FAT table
				 dir->name[0] = DELETED;    
				 SD_writeSingleBlock (firstSector+sector);
				 			 
				 freeMemoryUpdate (ADD, dir->fileSize);
                 
				 //update next free cluster entry in FSinfo sector
				 cluster = getSetFreeCluster (NEXT_FREE, GET, 0); 
				 if(firstCluster < cluster)
				     getSetFreeCluster (NEXT_FREE, SET, firstCluster);

				 //mark all the clusters allocated to the file as 'free'
			     while(1)  
			     {
			        nextCluster = getSetNextCluster (firstCluster, GET, 0);
					getSetNextCluster (firstCluster, SET, 0);
					if(nextCluster > 0x0ffffff6) 
					   {transmitString("File deleted!");return 0;}
					firstCluster = nextCluster;
			  	 } 
			  }
            }
          }
          else  //when flag = GET_LIST
		  {
		     TX_NEWLINE;
			 //for(j=0; j<11; j++)
		     //{
			   //if(j == 8) Neoway_Print(" ");
			   //Neoway_Print("%c",dir->name[j]);
			 //}
		     transmitString("   ");
		     if((dir->attrib != 0x10) && (dir->attrib != 0x08))
			 {
			     transmitString("FILE" );
		         transmitString("   ");
			     displayMemory (LOW, dir->fileSize);
			 }
			// else
			//   transmitString_F ((dir->attrib == 0x10)? PSTR("DIR") : PSTR("ROOT"));
		  }
       }
     }
   }

   cluster = (getSetNextCluster (cluster, GET, 0));

   if(cluster > 0x0ffffff6)
   	 return 0;
   if(cluster == 0) 
   {transmitString("Error in getting cluster");  return 0;}
 }
return 0;
}

//***************************************************************************
//Function: if flag=READ then to read file from SD card and send contents to UART 
//if flag=VERIFY then functions will verify whether a specified file is already existing
//Arguments: 
//           1. flag (READ or VERIFY) and 
//           2. pointer to the file name
//           3. pointer to read buffer
//return: 0, if normal operation or flag is READ
//	      1, if file is already existing and flag = VERIFY
//		  2, if file name is incompatible
//***************************************************************************
unsigned char readFile (unsigned char flag, unsigned char *fileName, unsigned char *disp_buf)
{
	struct dir_Structure *dir;
	unsigned long cluster, byteCounter = 0, fileSize, firstSector;
	unsigned short k;
	unsigned char j, error;
	//unsigned char disp_buf[512]={0};                         // for storing file read contents

	error = convertFileName (fileName); //convert fileName into FAT format
	if(error) return 2;

	dir = findFiles (GET_FILE, fileName); //GET_FILE //get the file location
	if(dir == 0) 
	  return (0);

	if(flag == VERIFY) return (1);	//specified file name is already existing

	cluster = (((unsigned long) dir->firstClusterHI) << 16) | dir->firstClusterLO;

	fileSize = dir->fileSize;

	TX_NEWLINE;
	TX_NEWLINE;

	while(1)
	{
		firstSector = getFirstSector (cluster);

		for(j=0; j<sectorPerCluster; j++)
		{
			SD_readSingleBlock(firstSector + j);
			
			for(k=0; k<512; k++)
			{
			  //Neoway_Print("%c",buffer[k]);
			  disp_buf[k]=buffer[k];
			  if ((byteCounter++) >= fileSize ) 
			  {
				  Neoway_Print("file contents : %s \r",disp_buf);
				  return 0;
			  }
			}
		}
		cluster = getSetNextCluster (cluster, GET, 0);
		if(cluster == 0) {transmitString("Error in getting cluster"); return 0;}
	}
	return 0;
}

//***************************************************************************
//Function: to convert normal short file name into FAT format
//Arguments: pointer to the file name
//return: 0, if successful else 1.
//***************************************************************************
unsigned char convertFileName (unsigned char *fileName)
{
unsigned char fileNameFAT[11];
unsigned char j, k;

for(j=0; j<12; j++)
if(fileName[j] == '.') break;

if(j>8) {transmitString("Invalid fileName.."); return 1;}

for(k=0; k<j; k++) //setting file name
  fileNameFAT[k] = fileName[k];

for(k=j; k<=7; k++) //filling file name trail with blanks
  fileNameFAT[k] = ' ';

j++;
for(k=8; k<11; k++) //setting file extention
{
  if(fileName[j] != 0)
    fileNameFAT[k] = fileName[j++];
  else //filling extension trail with blanks
    while(k<11)
      fileNameFAT[k++] = ' ';
}

for(j=0; j<11; j++) //converting small letters to caps
  if((fileNameFAT[j] >= 0x61) && (fileNameFAT[j] <= 0x7a))
    fileNameFAT[j] -= 0x20;

for(j=0; j<11; j++)
  fileName[j] = fileNameFAT[j];

return 0;
}





//***************************************************************************
//Function: to search for the next free cluster in the root directory
//          starting from a specified cluster
//Arguments: Starting cluster
//return: the next free cluster
//****************************************************************
unsigned long searchNextFreeCluster (unsigned long startCluster)
{
  unsigned long cluster, *value, sector;
  unsigned char i;
    
	startCluster -=  (startCluster % 128);   //to start with the first file in a FAT sector
    for(cluster =startCluster; cluster <totalClusters; cluster+=128) 
    {
      sector = unusedSectors + reservedSectorCount + ((cluster * 4) / bytesPerSector);
      SD_readSingleBlock(sector);
      for(i=0; i<128; i++)
      {
       	 value = (unsigned long *) &buffer[i*4];
         if(((*value) & 0x0fffffff) == 0)
            return(cluster+i);
      }  
    } 

 return 0;
}

//***************************************************************************
//Function: to display total memory and free memory of SD card, using UART
//Arguments: none
//return: none
//Note: this routine can take upto 15sec for 1GB card (@1MHz clock)
//it tries to read from SD whether a free cluster count is stored, if it is stored
//then it will return immediately. Otherwise it will count the total number of
//free clusters, which takes time
//****************************************************************************
void memoryStatistics (void)
{
unsigned long freeClusters, totalClusterCount, cluster;
unsigned long totalMemory, freeMemory;
unsigned long sector, *value;
unsigned short i;


totalMemory = totalClusters * sectorPerCluster / 1024;
totalMemory *= bytesPerSector;

TX_NEWLINE;
TX_NEWLINE;
transmitString("Total Memory: ");

displayMemory (HIGH, totalMemory);

freeClusters = getSetFreeCluster (TOTAL_FREE, GET, 0);
//freeClusters = 0xffffffff;    

if(freeClusters > totalClusters)
{
   freeClusterCountUpdated = 0;
   freeClusters = 0;
   totalClusterCount = 0;
   cluster = rootCluster;    
    while(1)
    {
      sector = unusedSectors + reservedSectorCount + ((cluster * 4) / bytesPerSector) ;
      SD_readSingleBlock(sector);
      for(i=0; i<128; i++)
      {
           value = (unsigned long *) &buffer[i*4];
         if(((*value)& 0x0fffffff) == 0)
            freeClusters++;;
        
         totalClusterCount++;
         if(totalClusterCount == (totalClusters+2)) break;
      }  
      if(i < 128) break;
      cluster+=128;
    } 
}

if(!freeClusterCountUpdated)
  getSetFreeCluster (TOTAL_FREE, SET, freeClusters); //update FSinfo next free cluster entry
freeClusterCountUpdated = 1;  //set flag
freeMemory = freeClusters * sectorPerCluster / 1024;
freeMemory *= bytesPerSector ;
TX_NEWLINE;
transmitString(" Free Memory: ");
displayMemory (HIGH, freeMemory);
TX_NEWLINE; 
}

//************************************************************
//Function: To convert the unsigned long value of memory into 
//          text string and send to UART
//Arguments: 1. unsigned char flag. If flag is HIGH, memory will be displayed in KBytes, else in Bytes. 
//			 2. unsigned long memory value
//return: none
//************************************************************
void displayMemory (unsigned char flag, unsigned long memory)
{
  unsigned char memoryString[] = "              Bytes"; //19 character long string for memory display
  unsigned char i;
  for(i=12; i>0; i--) //converting freeMemory into ASCII string
  {
    if(i==5 || i==9) 
	{
	   memoryString[i-1] = ',';  
	   i--;
	}
    memoryString[i-1] = (memory % 10) | 0x30;
    memory /= 10;
	if(memory == 0) break;
  }
  if(flag == HIGH)  memoryString[13] = 'K';
  transmitString(memoryString);
}

//********************************************************************
//Function: to delete a specified file from the root directory
//Arguments: pointer to the file name
//return: none
//********************************************************************
void deleteFile (unsigned char *fileName)
{
  unsigned char error;

  error = convertFileName (fileName);
  if(error) return;

  findFiles (DELETE, fileName);
}

//********************************************************************
//Function: update the free memory count in the FSinfo sector. 
//			Whenever a file is deleted or created, this function will be called
//			to ADD or REMOVE clusters occupied by the file
//Arguments: #1.flag ADD or REMOVE #2.file size in Bytes
//return: none
//********************************************************************
void freeMemoryUpdate (unsigned char flag, unsigned long size)
{
  unsigned long freeClusters;
  //convert file size into number of clusters occupied
  if((size % 512) == 0) size = size / 512;
  else size = (size / 512) +1;
  if((size % 8) == 0) size = size / 8;
  else size = (size / 8) +1;

  if(freeClusterCountUpdated)
  {
	freeClusters = getSetFreeCluster (TOTAL_FREE, GET, 0);
	if(flag == ADD)
  	   freeClusters = freeClusters + size;
	else  //when flag = REMOVE
	   freeClusters = freeClusters - size;
	getSetFreeCluster (TOTAL_FREE, SET, freeClusters);
  }
}

//************************************************************************************
//Function: to create a file in FAT32 format in the root directory if given 
//			file name does not exist; if the file already exists then append the data.
//Arguments: 1. pointer to the file name  (minimum length of file name should be 8 characters including dot and extension)
//           2. pointer to data buffer to be written to file
//return: none
//************************************************************************************
void writeFile (unsigned char *fileName,unsigned char *file_data)
{
unsigned char j, data, error, fileCreatedFlag = 0, start = 0, appendFile = 0, sectorEndFlag = 0, sector;
unsigned short i, firstClusterHigh, firstClusterLow;
struct dir_Structure *dir;
unsigned long cluster, nextCluster, prevCluster, firstSector, clusterCount, extraMemory;
unsigned long startBlock;
unsigned short file_data_index=0;

unsigned char dummy_read_buf[512]={0};
//static int count_call=1;                  //for debugging

j = readFile (VERIFY, fileName,dummy_read_buf);
//Neoway_Print("j=%d\r",j);



if(j == 1) 
{
  transmitString("  File already existing, appending data.."); 
  appendFile = 1;
  cluster = appendStartCluster;
  //Neoway_Print("cluster %x\r",cluster);
  
  clusterCount=0;
  while(1)
  {
    nextCluster = getSetNextCluster (cluster, GET, 0);
	//Neoway_Print("nextCluster %x\r",nextCluster);
	
    if(nextCluster == EOF1) break;
	cluster = nextCluster;
	clusterCount++;
	//Neoway_Print("chek1\r");
  }

  sector = (fileSize - (clusterCount * sectorPerCluster * bytesPerSector)) / bytesPerSector; //last sector number of the last cluster of the file
  start = 1;
  
//  appendFile();
//  return;
}
else if(j == 2) 
   return; //invalid file name
else
{
  TX_NEWLINE;
  transmitString(" Creating File..");
  
  cluster = getSetFreeCluster (NEXT_FREE, GET, 0);
  //Neoway_Print("return getSetFreeCluster %d\r",cluster);
	//Neoway_Print("totalClusters %d\r",totalClusters);
  
  if(cluster > totalClusters)
  {
	  //Neoway_Print("inside cluster > totalClusters\r");
	  //Neoway_Print("cluster %d\r",cluster);
	   //Neoway_Print("totalClusters %d\r",totalClusters);
     cluster = rootCluster;
  }
  cluster = searchNextFreeCluster(cluster);
  //Neoway_Print("return searchNextFreeCluster %d\r",cluster);
  
   if(cluster == 0)
   {
      TX_NEWLINE;
      transmitString(" No free cluster!");
	  return;
   }
   
  getSetNextCluster(cluster, SET, EOF1);   //last cluster of the file, marked EOF1
   
  firstClusterHigh = (unsigned short) ((cluster & 0xffff0000) >> 16 );
  firstClusterLow = (unsigned short) ( cluster & 0x0000ffff);
  fileSize = 0;
}





while(1)
{
	
	
   
   if(start)
   {
      start = 0;
	  startBlock = getFirstSector (cluster) + sector;
	  SD_readSingleBlock (startBlock);
	  i = fileSize % bytesPerSector;
	  j = sector;
   }
   else
   {
	   
      startBlock = getFirstSector (cluster);
	  i=0;
	  j=0;
   }
   
   
   TX_NEWLINE;
   transmitString(" Enter text (end with ~):");
   file_data_index=0;
   
   do
   {
	   
     if(sectorEndFlag == 1) //special case when the last character in previous sector was '\r'
	 {
	 	transmitByte ('\n');
        buffer[i++] = '\n'; //appending 'Line Feed (LF)' character
		fileSize++;
	 }
     
	 
	sectorEndFlag = 0;
    
	 //data = receiveByte(file_data);
	 data=file_data[file_data_index];
	 //Neoway_Print("%c",data);
	 if(data == 0x08)	//'Back Space' key pressed
	 { 
	   if(i != 0)
	   { 
	     transmitByte(data);
		 transmitByte(' '); 
	     transmitByte(data); 
	     i--; 
		 fileSize--;
	   } 
	   continue;     
	 }
	 transmitByte(data);
	 //Neoway_Print("chek0\r");
	 
     buffer[i++] = data;
	 fileSize++;
     if(data == '\r')  //'Carriege Return (CR)' character
     {
        if(i == 512)
		   sectorEndFlag = 1;  //flag to indicate that the appended '\n' char should be put in the next sector
	    else
		{ 
		   transmitByte ('\n');
           buffer[i++] = '\n'; //appending 'Line Feed (LF)' character
		   fileSize++;
	    }
     }
	 
     if(i >= 512)   //though 'i' will never become greater than 512, it's kept here to avoid 
	 {				//infinite loop in case it happens to be greater than 512 due to some data corruption
	   i=0;
	   error = SD_writeSingleBlock (startBlock);
       j++;
	   if(j == sectorPerCluster) {j = 0; break;}
	   startBlock++; 
     }
	 
	 ++file_data_index;                                    // for incrementing file_data index number
	 
	}while (data != '~');

	//if(file_data[0]=='s')
	//while(1);
   if(data == '~') 
   {
      fileSize--;	//to remove the last entered '~' character
	  i--;
	  for(;i<512;i++)  //fill the rest of the buffer with 0x00
        buffer[i]= 0x00;
   	  error = SD_writeSingleBlock (startBlock);

      break;
   } 
     
   prevCluster = cluster;
   
   cluster = searchNextFreeCluster(prevCluster); //look for a free cluster starting from the current cluster

   if(cluster == 0)
   {
      TX_NEWLINE;
      transmitString(" No free cluster!");
	  return;
   }

   getSetNextCluster(prevCluster, SET, cluster);
   getSetNextCluster(cluster, SET, EOF1);   //last cluster of the file, marked EOF1
}        

getSetFreeCluster (NEXT_FREE, SET, cluster); //update FSinfo next free cluster entry

if(appendFile)  //executes this loop if file is to be appended
{
	
  SD_readSingleBlock (appendFileSector);   
   
  dir = (struct dir_Structure *) &buffer[appendFileLocation]; 
  extraMemory = fileSize - dir->fileSize;
  dir->fileSize = fileSize;
  
  SD_writeSingleBlock (appendFileSector);
  freeMemoryUpdate (REMOVE, extraMemory); //updating free memory count in FSinfo sector;
  
  TX_NEWLINE;
  transmitString(" File appended!");
  TX_NEWLINE;
  return;
}

//executes following portion when new file is created

prevCluster = rootCluster; //root cluster

while(1)
{
   firstSector = getFirstSector (prevCluster);

   for(sector = 0; sector < sectorPerCluster; sector++)
   {
     SD_readSingleBlock (firstSector + sector);
	
    
     for(i=0; i<bytesPerSector; i+=32)
     {
	    dir = (struct dir_Structure *) &buffer[i];
        
		if(fileCreatedFlag)   //to mark last directory entry with 0x00 (empty) mark
		 { 					  //indicating end of the directory file list
		   dir->name[0] = 0x00;
           return;
         }

        if((dir->name[0] == EMPTY) || (dir->name[0] == DELETED))  //looking for an empty slot to enter file info
		{
		  for(j=0; j<11; j++)
  			dir->name[j] = fileName[j];
		  dir->attrib = ATTR_ARCHIVE;	//settting file attribute as 'archive'
		  dir->NTreserved = 0;			//always set to 0
		  dir->timeTenth = 0;			//always set to 0
		  dir->createTime = 0x9684;		//fixed time of creation
		  dir->createDate = 0x3a37;		//fixed date of creation
		  dir->lastAccessDate = 0x3a37;	//fixed date of last access
		  dir->writeTime = 0x9684;		//fixed time of last write
		  dir->writeDate = 0x3a37;		//fixed date of last write
		  dir->firstClusterHI = firstClusterHigh;
		  dir->firstClusterLO = firstClusterLow;
		  dir->fileSize = fileSize;

		  SD_writeSingleBlock (firstSector + sector);
		  fileCreatedFlag = 1;

		  //TX_NEWLINE;
		  TX_NEWLINE;
		  transmitString(" File Created!");

		  freeMemoryUpdate (REMOVE, fileSize); //updating free memory count in FSinfo sector
	     
        }
     }
   }

   cluster = getSetNextCluster (prevCluster, GET, 0);

   if(cluster > 0x0ffffff6)
   {
      if(cluster == EOF1)   //this situation will come when total files in root is multiple of (32*sectorPerCluster)
	  {  
		cluster = searchNextFreeCluster(prevCluster); //find next cluster for root directory entries
		getSetNextCluster(prevCluster, SET, cluster); //link the new cluster of root to the previous cluster
		getSetNextCluster(cluster, SET, EOF1);  //set the new cluster as end of the root directory
      } 

      else
      {	
	    transmitString("End of Cluster Chain"); 
	    return;
      }
   }
   if(cluster == 0) {transmitString("Error in getting cluster"); return;}
   
   prevCluster = cluster;
 }
 
 //if(count_call==2)
		 //while(1);
	        
	 //++count_call;
 
 
 return;
}

unsigned char receiveByte(unsigned char *temp)              // to send each byte of data
{
	
static int i=0;
//char temp[20]="thanks~";             //give file content here

return temp[i++];
	
	
}

void transmitByte(unsigned char temp)  // to send one byte to uart
{
	//Neoway_Print("%c",temp);	
}
