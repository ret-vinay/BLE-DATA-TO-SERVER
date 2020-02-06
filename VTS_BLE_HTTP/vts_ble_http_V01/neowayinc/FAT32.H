/******************************************************************************
* File Name	: FAT32.H
* Author	: Hari Babu T D. 
*			  Software Engineer, Elegance Technologies, Bangalore.
* Description	: FAT32 file system structure and prototypes.
******************************************************************************/


#ifndef _FAT32_H_
#define _FAT32_H_

#define TX_NEWLINE Neoway_Print("\r")
#define transmitString Neoway_Print

//Structure to access Master Boot Record for getting info about partioions
struct MBRinfo_Structure{
unsigned char	nothing[446];		//ignore, placed here to fill the gap in the structure
unsigned char	partitionData[64];	//partition records (16x4)
unsigned short	signature;		//0xaa55
}__attribute__((packed));

//Structure to access info of the first partioion of the disk 
struct partitionInfo_Structure{ 				
unsigned char	status;				//0x80 - active partition
unsigned char 	headStart;			//starting head
unsigned short	cylSectStart;		//starting cylinder and sector
unsigned char	type;				//partition type 
unsigned char	headEnd;			//ending head of the partition
unsigned short	cylSectEnd;			//ending cylinder and sector
unsigned long	firstSector;		//total sectors between MBR & the first sector of the partition
unsigned long	sectorsTotal;		//size of this partition in sectors
}__attribute__((packed));                         //to take care of structure padding

//Structure to access boot sector data
struct BS_Structure{
unsigned char jumpBoot[3]; //default: 0x009000EB
unsigned char OEMName[8];
unsigned short bytesPerSector; //deafault: 512
unsigned char sectorPerCluster;
unsigned short reservedSectorCount;
unsigned char numberofFATs;
unsigned short rootEntryCount;
unsigned short totalSectors_F16; //must be 0 for FAT32
unsigned char mediaType;
unsigned short FATsize_F16; //must be 0 for FAT32
unsigned short sectorsPerTrack;
unsigned short numberofHeads;
unsigned long hiddenSectors;
unsigned long totalSectors_F32;
unsigned long FATsize_F32; //count of sectors occupied by one FAT
unsigned short extFlags;
unsigned short FSversion; //0x0000 (defines version 0.0)
unsigned long rootCluster; //first cluster of root directory (=2)
unsigned short FSinfo; //sector number of FSinfo structure (=1)
unsigned short BackupBootSector;
unsigned char reserved[12];
unsigned char driveNumber;
unsigned char reserved1;
unsigned char bootSignature;
unsigned long volumeID;
unsigned char volumeLabel[11]; //"NO NAME "
unsigned char fileSystemType[8]; //"FAT32"
unsigned char bootData[420];
unsigned short bootEndSignature; //0xaa55
}__attribute__((packed));                                                                    //to take care of structure padding


//Structure to access FSinfo sector data
struct FSInfo_Structure
{
unsigned long leadSignature; //0x41615252
unsigned char reserved1[480];
unsigned long structureSignature; //0x61417272
unsigned long freeClusterCount; //initial: 0xffffffff
unsigned long nextFreeCluster; //initial: 0xffffffff
unsigned char reserved2[12];
unsigned long trailSignature; //0xaa550000
}__attribute__((packed));                        //to take care of structure padding

//Structure to access Directory Entry in the FAT
struct dir_Structure{
unsigned char name[11];
unsigned char attrib; //file attributes
unsigned char NTreserved; //always 0
unsigned char timeTenth; //tenths of seconds, set to 0 here
unsigned short createTime; //time file was created
unsigned short createDate; //date file was created
unsigned short lastAccessDate;
unsigned short firstClusterHI; //higher word of the first cluster number
unsigned short writeTime; //time of last write
unsigned short writeDate; //date of last write
unsigned short firstClusterLO; //lower word of the first cluster number
unsigned long fileSize; //size of file in bytes
}__attribute__((packed));                     //to take care of structure padding

//Attribute definitions for file/directory
#define ATTR_READ_ONLY     0x01
#define ATTR_HIDDEN        0x02
#define ATTR_SYSTEM        0x04
#define ATTR_VOLUME_ID     0x08
#define ATTR_DIRECTORY     0x10
#define ATTR_ARCHIVE       0x20
#define ATTR_LONG_NAME     0x0f


#define DIR_ENTRY_SIZE     0x32
#define EMPTY              0x00
#define DELETED            0xe5
#define GET     0
#define SET     1
#define READ	0
#define VERIFY  1
#define ADD		0
#define REMOVE	1
#define LOW		0
#define HIGH	1	
#define TOTAL_FREE   1
#define NEXT_FREE    2
#define GET_LIST     0
#define GET_FILE     1
#define DELETE		 2
#define EOF1		0x0fffffff


//************* external variables *************
extern volatile unsigned long firstDataSector, rootCluster, totalClusters;
extern volatile unsigned short  bytesPerSector, sectorPerCluster, reservedSectorCount;
extern unsigned long unusedSectors, appendFileSector, appendFileLocation, fileSize, appendStartCluster;

extern struct BS_Structure *bpb;
extern struct MBRinfo_Structure *mbr;
//global flag to keep track of free cluster count updating in FSinfo sector




//************* functions *************
unsigned char getBootSectorData (void);
unsigned long getFirstSector(unsigned long clusterNumber);
unsigned long getSetFreeCluster(unsigned char totOrNext, unsigned char get_set, unsigned long FSEntry);
struct dir_Structure* findFiles (unsigned char flag, unsigned char *fileName);
unsigned long getSetNextCluster (unsigned long clusterNumber,unsigned char get_set,unsigned long clusterEntry);
unsigned char readFile (unsigned char flag, unsigned char *fileName,unsigned char *disp_buf);
unsigned char convertFileName (unsigned char *fileName);
void writeFile (unsigned char *fileName,unsigned char *file_data);
void appendFile (void);
unsigned long searchNextFreeCluster (unsigned long startCluster);
void memoryStatistics (void);
void displayMemory (unsigned char flag, unsigned long memory);
void deleteFile (unsigned char *fileName);
void freeMemoryUpdate (unsigned char flag, unsigned long size);

unsigned char receiveByte(unsigned char *temp);
void transmitByte(unsigned char temp);


unsigned long from_LE_32(char *ptr );
unsigned  int from_LE_16(char *ptr);
struct A
{
unsigned char 	Num_Fats; 						// Total Number of Fats
unsigned long 	Fat_Start[2]; 			// Start Location of each fat here
unsigned long 	P_Start; 							// this is the start of the partition block
unsigned char 	Secs_Cluster; 					// This is the number of sectors per cluster
int 				Bytes_Sector; 					// This is the number of bytes per cluster (defaut 512)
unsigned long 	Secs_Fat; 						// The number of sectors per fat Table
unsigned long 	Root_Start;						// This is the start of the root directory
unsigned short 	Res_Secs; 						// The number of reserved sectors
unsigned long	data_start;
}__attribute__((packed));                       //to take care of structure padding

typedef struct A fat_t;

struct B
{
unsigned char 	File_Name[32]; 					// Name of the File
unsigned long	 start_cluster; 						// Cluster in which the file begins
}__attribute__((packed));                        //to take care of structure padding

typedef struct B file_t;
#endif
