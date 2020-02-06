/*==========================================================================
 |               Neoway OpenCPU --  User API
 |
 |              Copyright (c) 2013 Neoway Ltd.
 |
 |--------------------------------------------------------------------------
 | File Description
 | ----------------
 |      Basic data type definition
 |
 |--------------------------------------------------------------------------
 |
 |  Designed by     :   
 |  Coded    by     :   
 |  Tested   by     :   
 |
 \=========================================================================*/

#ifndef __NEOWAY_TYPE_H__
#define __NEOWAY_TYPE_H__

#ifndef FALSE
#define FALSE    0
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef NULL
#define NULL    ((void *) 0)
#endif


/****************************************************************************
 * Type Definitions
 ***************************************************************************/
typedef unsigned char		bool;
typedef unsigned char		BOOL;
typedef unsigned char		U8;
typedef signed   char 		S8;
typedef unsigned short   	U16;
typedef short   			S16;
typedef unsigned int    	U32;
typedef int    			S32;
typedef unsigned long long  U64;


/* portable 8-bit unsigned integer */
typedef unsigned char           kal_uint8;
/* portable 8-bit signed integer */
typedef signed char             kal_int8;
/* portable 16-bit unsigned integer */
typedef unsigned short int      kal_uint16;
/* portable 16-bit signed integer */
typedef signed short int        kal_int16;
/* portable 32-bit unsigned integer */
typedef unsigned int            kal_uint32;
/* portable 32-bit signed integer */
typedef signed int              kal_int32;
typedef enum 
{
    KAL_FALSE,
    KAL_TRUE
} kal_bool;

#endif  // End-of __NEOWAY_TYPE_H__

