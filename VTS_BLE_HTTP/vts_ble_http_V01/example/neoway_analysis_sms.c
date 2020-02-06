#include "neoway_analysis_sms.h"



NeowayTimerId neoway_timer_sms;

S8 sz_pdu_str[512] = {0};
Neoway_SM_PARAM_Struct sm_para_req;
BOOL gNeo_sms_state = FALSE;	//Receive the SMS.
U8 nv_num_buf[21]="9916533410";	//Initial number


void Neoway_SMSTimersInit(void)
{
	Neoway_InitTimer(&neoway_timer_sms,NEOWAY_MOD_USER2);
}


//Transfer the byte data to character string that can be printed.
//Return the length of the target character string.
int Neoway_PduBytes2String(const U8* p_src, S8* p_dst, int n_src_length)
{
	int i;
	const S8 tab[] = "0123456789ABCDEF";	// 0x0 to 0xf character table

	for (i = 0; i < n_src_length; i++)
	{
		*p_dst = tab[*p_src >> 4];
		p_dst++;
		*p_dst++ = tab[*p_src & 0x0f];
		p_src++;
	}
	return 2*n_src_length;
}

//Transfer character string that can be printed to byte data.
//Return the length of the target data.
int Neoway_PduString2Bytes(const S8* p_src, U8* p_dst, int n_src_length)
{
	int i;
	for (i = 0; i < n_src_length; i+=2)
	{
		//Output first 4 bits.

		if ( *p_src >= '0' && *p_src <= '9')
		{
			*p_dst = (*p_src - '0') << 4;
		}
		else
		{
			*p_dst = (*p_src - 'A' + 10) << 4;
		}
		p_src++;
		//Output last 4 bits.
		if ( *p_src >= '0' && *p_src <= '9')
		{
			*p_dst |= *p_src - '0';
		}
		else
		{
			*p_dst |= *p_src - 'A' + 10;
		}
		p_src++;
		p_dst++;
	}
	return n_src_length/2;
}

//7-bit coding
//Return:  The length of the target code plus 1. There are bytes for remaining data.
int Neoway_PduEncode7bit(const S8* p_src, U8* p_dst, int n_src_length)
{
	int		n_src;	//Count of the source character strings
	int		n_dst;	//Count of the destiniation character strings
	int		n_S8;	//ID of the byte in the processsing array, 0 to 7.
	U8 		c_left;	//Data remained by last byte

	//Initialize count value
	n_src = 0;
	n_dst = 0;

	//Group the source string in 8 bytes and compress the groups into 7 bytes.
	//Circulating
	while ( n_src < n_src_length )
	{
		//Obtain the last three bits of the source character string count to complete the circulating.
		n_S8 = n_src & 7;

		//Process each byte of the source character string.
		if ( n_S8 == 0 )
		{
			//Leave the first byte in the array.
			c_left = *p_src;
		}
		else
		{
			//For other bytes in the array, add the right part to the remaining data to complete the target coding bytes.
			*p_dst = (*p_src << (8-n_S8)) | c_left;

			//Save the left part of the byte as the remaining data.
			c_left = *p_src >> n_S8;

			//Modify the pointer and count value of the target string.
			p_dst++;
			n_dst++;
		}
		//Modify the pointer and count value of the source string.
		p_src++;
		n_src++;
		
	}

	//Return the length of the target string.
	return n_dst;
}

//7-bit decoding
//Return the length of the target string.
int Neoway_PduDecode7bit(const U8* p_src, S8* p_dst, int n_src_length)
{
	int 		n_src;		//Count of the source character strings
	int 		n_dst;		//Count of the destiniation decoding strings
	int 		n_S8;		//ID of the byte in the processsing array, 0 to 6.
	U8 		c_left;	//Data remained by last byte
	
	//Initialize count value
	n_src = 0;
	n_dst = 0;
	
	//Byte ID in the array and initialization of the remaining data
	n_S8 = 0;
	c_left = 0;
	
	//Group the source data together in 7 bytes and decompress them to 8 bytes.
	//Circulate the processing until all source data is processed.
	//Even though the group contains less than 7 bytes, the source data can be processed correctly.
	while( n_src < n_src_length )
	{
		//Obtain a target decoding byte by removing the left bit after adding the right part of the source byte  to the remaining data.
		*p_dst = ( ( *p_src << n_S8 ) | c_left ) & 0x7f;
		
		//Save the left part of the byte as the remaining data.
		c_left = *p_src >> ( 7-n_S8 );
		
		//Modify the pointer and count value of the target string.
		p_dst++;
		n_dst++;
		
		//Modify the byte count.
		n_S8++;
		
		//The last byte of one group
		if( n_S8 == 7 )
		{
			//Obtain an additinal target decoding byte.
			*p_dst = c_left;
			
			//Modify the pointer and count value of the target string.
			p_dst++;
			n_dst++;
			
			//Byte ID in the array and initialization of the remaining data
			n_S8 = 0;
			c_left = 0;
		}
		
		//Modify the pointer and count value of the source string.
		p_src++;
		n_src++;
	}
	
	//Add an end symbol to the output character string.
	*p_dst = '\0';
	
	//Return the length of the target string.
	return n_dst;
} 

//8-bit coding
//Return:  the length of the target string.
int Neoway_PduEncode8bit(const S8* p_src, U8* p_dst, int n_src_length)
{
	//Simple copy
	memcpy(p_dst, p_src, n_src_length);
	
	return n_src_length;
}

//8-bit decoding
//Return the length of the target string.
int Neoway_PduDecode8bit(const U8* p_src, S8* p_dst, int n_src_length)
{
	memcpy(p_dst, p_src, n_src_length);
	*p_dst = '\0';
	return n_src_length;
}

//Convert the character strings in normal sequence into character strings in opposite order. If the length is an odd number, add F to make it an even number.
//Return:  the length of the target character string.
int Neoway_PduInvertNumbers(const S8* p_src, S8* p_dst, int n_src_length)
{
	int	nDstLength;		//The length of the target character string.
	int 	i;
	S8	ch;				//Used to save one character
	
	//Copy the length of the string
	nDstLength = n_src_length;
	
	//Reverse every two character strings.
	for (i=0; i<n_src_length; i+=2)
	{
		ch = *p_src++;			//Save the characters first printed.
		*p_dst++ = *p_src++;	//Copy the characters printed later.
		*p_dst++ = ch;			//Copy the characters first printed.
	}
	
	//Is the length of the source string an odd number?
	if ( n_src_length & 1 )
	{
		*(p_dst-2) = 'F';	//Add F.
		nDstLength++;		//Add 1 to the lengh of the target string.
	}
	
	//Add an end symbol to the output character string.
	*p_dst = '\0';
	
	//Return the length of the target character string.
	return nDstLength;
}

//Convert the reverse character strings in to strings in normal sequence.
//Return:  the length of the target string.
int Neoway_PduSerializeNumbers(const S8* p_src, S8* p_dst, int n_src_length)
{
	int nDstLength;		//The length of the target string.
	int i;
	S8 ch;			//Used to save one character
	
	//Copy the length of the string
	nDstLength = n_src_length;
	
	//Reverse every two character strings.
	for (i=0; i<n_src_length; i+=2)
	{
		ch = *p_src++;		//Save the characters first printed.
		*p_dst++ = *p_src++;	//Copy the characters printed later.
		*p_dst++ = ch;		//Copy the characters first printed.
	}
	
	//Is the last character F?
	if ( *(p_dst-1) == 'F' )
	{
		p_dst--;
		nDstLength--;		//The length of the target string minus 1
	}
	
	//Add an end symbol to the output character string.
	*p_dst = '\0';
	
	//Return the length of the target character string.
	return nDstLength;
}

//PDU code, used to compile and send SMS messages
// p_src: The pointer of the source PDU parameter
// p_dst: The pointer of the target PDU string
//Return:  the length of the target PDU
int Neoway_SmsEncodePdu(const Neoway_SM_PARAM_Struct* p_src, S8* p_dst)
{
	int n_length;				//String length used internally
	int n_dst_length;			//the length of the target PDU string
	U8 buf[256];				//Buffer used internally

	memset(buf, 0, 256);
	
	//SMSC address information field
	if (strlen(p_src->SCA) == 0)
	{
		buf[0] = 0;
		n_dst_length = Neoway_PduBytes2String(buf, p_dst, 1);		//Convert two bytes into target PDU string.
//		n_dst_length += pduInvertNumbers(p_src->SCA, &p_dst[n_dst_length], 0);	//Convert SMSC number into the target PDU string.
	}
	else
	{	
		n_length = strlen(p_src->SCA);	//The length of the SMSC address character string	
		buf[0] = (S8)((n_length & 1) == 0 ? n_length : n_length + 1) / 2 + 1;	//The length of the SMSC address information
		buf[1] = p_src->SCA_TYPE;		//Fixed: number in international format
		n_dst_length = Neoway_PduBytes2String(buf, p_dst, 2);		//Convert two bytes into target PDU string.
		n_dst_length += Neoway_PduInvertNumbers(p_src->SCA, &p_dst[n_dst_length], n_length);	//Convert SMSC number into the target PDU string.
	}
	
	//The basic parameters and target address of the TPDU field
	n_length = strlen(p_src->TPA);	//The length of the TP-DA address character string
	buf[0] = p_src->TP_PDUType;		//8-bit PDU-Type array
	buf[1] = p_src->TP_MR;			// TP-MR=0
	buf[2] = (S8)n_length;		//Digital number of the target address (the actual length of the TP-DA address character string)
	buf[3] = p_src->TP_DAType;					//TP-DA type 
	n_dst_length += Neoway_PduBytes2String(buf, &p_dst[n_dst_length], 4);		//Convert four bytes into target PDU string.
	n_dst_length += Neoway_PduInvertNumbers(p_src->TPA, &p_dst[n_dst_length], n_length);	//Convert TP-DA number into the target PDU string.
	
	//TP-DU field protocol, coding, user information, etc.
	n_length = strlen(p_src->TP_UD);//The length of the user information character string
	buf[0] = p_src->TP_PID;			//Protocol label (TP-PID)
	buf[1] = p_src->TP_DCS;			//User information coding (TP-DCS)
	buf[2] = p_src->VP[0];			//The valid period (TP-VP) is 5 minutes
	if(p_src->TP_DCS == PDU_7BIT)	
	{
		//7-bit coding
		buf[3] = n_length;			//The length before coding
		n_length = Neoway_PduEncode7bit(p_src->TP_UD, &buf[4], n_length+1) + 4;	//Convert TP-DA number into the target PDU string.
		n_dst_length += Neoway_PduBytes2String(buf, &p_dst[n_dst_length], n_length);		//Convert the data into the target PDU string.
	}
	else if(p_src->TP_DCS == PDU_UCS2)
	{
		buf[3] = n_length / 2;
		//UCS2 coding
//		buf[3] = pduEncodeUcs2(p_src->TP_UD, &buf[4], n_length);	//Convert TP-DA number into the target PDU string.
//		n_length = buf[3] + 4;		//n_length is the length of the data
		n_dst_length += Neoway_PduBytes2String(buf, &p_dst[n_dst_length], 4);		//Convert the data into the target PDU string.
		strcpy(p_dst + n_dst_length, p_src->TP_UD);
		n_dst_length += strlen(p_src->TP_UD);
	}
	else
	{
		//8-bit coding
		buf[3] = Neoway_PduEncode8bit(p_src->TP_UD, &buf[4], n_length);	//The number of the coding bytes after converting TP-DA into the tartet PDU character string
		n_length = buf[3] + 4;
		n_dst_length += Neoway_PduBytes2String(buf, &p_dst[n_dst_length], n_length);		//Convert the data into the target PDU string.
	}

//	n_dst_length += Neoway_PduBytes2String(buf, &p_dst[n_dst_length], n_length);		//Convert the data into the target PDU string.

	//Return the length of the target character string.
	return n_dst_length;
}

//PDU decoding, used to receive and read SMS messages
// p_src: The pointer of the source PDU string
// p_dst: The pointer of the target PDU parameter
//Return:  The length of the user information string
int Neoway_SmsDecodePdu(const S8* p_src, Neoway_SM_PARAM_Struct* p_dst)
{
	int n_dst_length;			//the length of the target PDU string
	S8 sz_sca[21] = {0};
	U8 tmp;			//Temporary byte character variables used internally
	U8 buf[256];		//Buffer used internally
	
	//SMSC address information field
	Neoway_PduString2Bytes(p_src, &tmp, 2);	//The length
	tmp = (tmp - 1) * 2;	//The length of the SMSC numebr string
	p_src += 4;			//The pointer moves afterwards, ignoring teh SMSC address format, 0891, and number type of the SMS center.
	Neoway_PduSerializeNumbers(p_src, /*p_dst->SCA*/sz_sca, tmp);	//Convert SMSC number into the target PDU string.
	//Neoway_Print(sz_sca);
	p_src += tmp;		//The pointer moves afterwards
	//The basic parameters and reply address of the TPDU field.
	Neoway_PduString2Bytes(p_src, &tmp, 2);	//The basic parameters
	p_src += 2;		//The pointer moves afterwards
	//Include the reply address, using the reply address information
	Neoway_PduString2Bytes(p_src, &tmp, 2);	//The length
	if (tmp % 2 != 0)
    		tmp += 1;	//Adjust the parity
	p_src += 4;			//The pointer move afterwards, ignoring the reply address (TP-RA) format.
	Neoway_PduSerializeNumbers(p_src, p_dst->TPA, tmp);	//TP-RA number
	//Neoway_Print(p_dst->TPA);
	p_src += tmp;		//The pointer moves afterwards
	//}
	
	//TP-DU field protocol, coding, user information, etc.
	Neoway_PduString2Bytes(p_src, (U8*)&p_dst->TP_PID, 2);	//Protocol label (TP-PID)
	//Neoway_Print("%d", p_dst->TP_PID);
	p_src += 2;		//The pointer moves afterwards
	Neoway_PduString2Bytes(p_src, (U8*)&p_dst->TP_DCS, 2);	//Coding manner (TP-DSC)
//	Neoway_Print("%d", p_dst->TP_DCS);
	p_src += 2;		//The pointer moves afterwards
	Neoway_PduSerializeNumbers(p_src, p_dst->TP_SCTS, 14);		//Character string of the service time stamp (TP_SCTS) 
	p_src += 14;		//The pointer moves afterwards
	Neoway_PduString2Bytes(p_src, &tmp, 2);	//The length of the user information (TP-UDL)
	p_src += 2;		//The pointer moves afterwards
	if(p_dst->TP_DCS == PDU_7BIT)	
	{
		//7-bit decoding
		n_dst_length = Neoway_PduString2Bytes(p_src, buf, tmp & 7 ? (int)tmp * 7 / 4 + 2 : (int)tmp * 7 / 4);	//Format conversion
		Neoway_PduDecode7bit(buf, p_dst->TP_UD, n_dst_length);	//Convert to TP-DU
		n_dst_length = tmp;
	}
	else if(p_dst->TP_DCS == PDU_UCS2)
	{
		//UCS2 coding
//		Neoway_Print("DCS 08 invalid");
		Neoway_UartSend(0, "DCS 08 invalid\r\n", 16);
		strcpy(p_dst->TP_UD, "invalid");
//		n_dst_length = Neoway_PduString2Bytes(p_src, buf, tmp * 2);			//Format conversion
//		n_dst_length = Neoway_pduDecodeUcs2(buf, p_dst->TP_UD, n_dst_length);	//Convert to TP-DU
	}
	else
	{
		//8-bit decoding
	//	n_dst_length = Neoway_PduString2Bytes(p_src, buf, tmp * 2);			//Format conversion
	//	n_dst_length = Neoway_PduDecode8bit(buf, p_dst->TP_UD, n_dst_length);	//Convert to TP-DU
//		Neoway_Print("DCS 08 invalid");
		Neoway_UartSend(0, "DCS 08 invalid\r\n", 16);
		strcpy(p_dst->TP_UD, "invalid");
	}

	
	//Return the length of the target character string.
	return n_dst_length;
}

BOOL Neoway_GetPDUString(const char* p_src, S8* p_dst)
{
	S8 sz_tmp[6] = {0};

	memcpy(sz_tmp, p_src, 5);
	if (strcmp(sz_tmp, "+CMT:") != 0)
	{
		return FALSE;
	}
	while (1)
	{
		 if (*p_src == '\r')
			break;
		p_src++;
	}
	p_src += 2;
	strcpy(p_dst, p_src);

	return TRUE;
}

void Neoway_SM_Struc_Init(Neoway_SM_PARAM_Struct* p_sm_param)
{
	memset(p_sm_param->SCA, 0, 21);
	memset(p_sm_param->TPA, 0, 21);
	p_sm_param->SCA_TYPE = 0x91;
	p_sm_param->TP_MR = 0x00;
	p_sm_param->TP_PID = 0x00;
	p_sm_param->TP_PDUType = 0x11;
	p_sm_param->TP_DAType = 0x91;
	p_sm_param->VP[0] = 0;
	memset(p_sm_param->TP_UD, 0, 281);
}

//Determine how many # characters in the command
BOOL GetFlagNumber(const char* p_ud, int* p_count)
{
	*p_count = 0;
	while (*p_ud != '\0')
	{
		if (*p_ud == '#')
			*p_count += 1;
		p_ud++;
	}	
	if (*(p_ud -3) != '#' && *(p_ud - 2) == '#' && *(p_ud - 1) == '#')
		return TRUE;
	return FALSE;
}

extern S8 gNeo_oil_rep;
//Determine the command code of the UD field
Neoway_CustomCmdEnum Neoway_GetCustomCmd(S8* p_ud)
{
	S8 sz_cmd[5] = {0};
	S8* p_point;
	S32 n_count;
	p_point = p_ud;
	if (*p_point == '#')
	{
		p_point++;
		memcpy(sz_cmd, p_point, 4);
		if (*p_point == '#')
			return SET_FORMAT_ERR_CMD;
		else if (strcmp(sz_cmd, "710#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 5)
				return SET_FORMAT_ERR_CMD;
			return SET_SCA_NUM_CMD;
		}
		else if (strcmp(sz_cmd, "711#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 7)
				return SET_FORMAT_ERR_CMD;
			return SET_DIAL_CMD;
		}
		else if (strcmp(sz_cmd, "730#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 6)
				return SET_FORMAT_ERR_CMD;
			return SET_ECHO_DATA_CMD;
		}
		else if (strcmp(sz_cmd, "735#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 6)
				return SET_FORMAT_ERR_CMD;
			return SET_TIME_CONFIG_CMD;
		}
		else if (strcmp(sz_cmd, "751#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 8)
				return SET_FORMAT_ERR_CMD;
			return SET_FENCE_CMD;
		}
		else if (strcmp(sz_cmd, "752#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 4)
				return SET_FORMAT_ERR_CMD;
			return SET_READ_FENCE_CMD;
		}
		else if (strcmp(sz_cmd, "760#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 4)
				return SET_FORMAT_ERR_CMD;
			return SET_CANCEL_FENCE_CMD;
		}
		else if (strcmp(sz_cmd, "770#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 5)
				return SET_FORMAT_ERR_CMD;
			return SET_PSD_CHANGE_CMD;
		}
		else if (strcmp(sz_cmd, "801#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 5)
				return SET_FORMAT_ERR_CMD;
			return SET_USERNAME_CMD;
		}
		else if (strcmp(sz_cmd, "802#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 7)
				return SET_FORMAT_ERR_CMD;
			return SET_APN_CONFIG_CMD;
		}
		else if (strcmp(sz_cmd, "803#") == 0)
		{	
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 6)
				return SET_FORMAT_ERR_CMD;
			return SET_SVR_ADDR_CMD;
		}
		else if (strcmp(sz_cmd, "988#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 6)
				return SET_FORMAT_ERR_CMD;
			return SET_SVR_POSI_SCH_CMD;
		}
		else if (strcmp(sz_cmd, "901#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 3)
				return SET_FORMAT_ERR_CMD;
			return SET_SMS_READ1;
		}
		else if (strcmp(sz_cmd, "902#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 3)
				return SET_FORMAT_ERR_CMD;
			return SET_SMS_READ2;
		}
		else if (strcmp(sz_cmd, "567#") == 0)
		{
			if (!GetFlagNumber(p_ud, &n_count) || n_count != 6)
				return SET_FORMAT_ERR_CMD;
			return SET_TIME_CMD;
		}
		else
			return SET_INVALID_CMD;	//Invalid command
	}
	
}

//Obtain the SMS center number and return the length of the number
S32 Neoway_GetSCANum(S8* p_ud, S8* p_sca_num)
{
	S32 n_num_len = 0;
	memset(p_sca_num, 0, strlen(p_sca_num));
	p_ud += 5;
	/*
	if ((*p_ud != '8' || *(p_ud + 1) != '6') && *p_ud != '#')
	{
		*p_sca_num++ = '8';
		*p_sca_num++ = '6';
	}
	*/
	while (*p_ud != '#')
	{
		*p_sca_num++ = *p_ud++;
		n_num_len++;
	}
	return n_num_len;
}

//Obtain the dialing number
S32 Neoway_GetDailNumber(S8* p_ud, S8* p_num1, S8* p_num2, S8* p_num3/*, S8* p_num4*/)
{
	S32 n_num_len = 0;
	p_ud += 5;
	while (*p_ud != '#')
	{
		*p_num1++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_num2++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_num3++ = *p_ud++;
		n_num_len++;
	}
	/*
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_num4++ = *p_ud++;
		n_num_len++;
	}
	*/
	return n_num_len;
}
//Obtain the recirculation interval and array count
S32 Neoway_GetEchoParam(S8* p_ud, S8* p_echo_time, S8* p_echo_num)
{
	S32 n_num_len = 0;
	p_ud += 5;
	while (*p_ud != '#')
	{
		*p_echo_time++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_echo_num++ = *p_ud++;
		n_num_len++;
	}
	return n_num_len;
}

//Obtain the time period count and the peiod.
S32 Neoway_GetTimeRange(S8* p_ud, S32* p_num, S8* p_time_data)
{
	S32 n_num_len = 0;
	p_ud += 5;
	*p_num = 0;
	while (*p_ud != '#')
	{
		*p_num = *p_num * 10 + (*p_ud - '0');
		p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_time_data++ = *p_ud++;
		n_num_len++;
	}
	return n_num_len;
}

//Obtain the radius of the fence, sampling interval, latitude, and longitude.
S32 Neoway_GetOUTParam(S8* p_ud, S8* p_radius, S8* p_time, S8* p_latitude, S8* p_longitude, S8* p_flaglat, S8* p_flaglng)
{
	S32 n_num_len = 0;
	p_ud += 5;
	*p_radius = 0;
	*p_time = 0;
	while (*p_ud != '#')
	{
		*p_radius++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_time++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		if (*p_ud != 'N' && *p_ud != 'S' && *p_ud != 'n' && *p_ud != 's')
		{
			*p_latitude++ = *p_ud++;
			n_num_len++;
		}
		else
		{
			*p_flaglat = *p_ud;
			p_ud++;
			n_num_len++;
		}
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		if (*p_ud != 'E' && *p_ud != 'W' && *p_ud != 'e' && *p_ud != 'w')
		{
			*p_longitude++ = *p_ud++;
			n_num_len++;
		}
		else
		{
			*p_flaglng = *p_ud;
			p_ud++;
			n_num_len++;
		}
	}
	return n_num_len;
}

//Determine whether the latitude and longitude of the fence is proper or not.
BOOL Neoway_IsLONAndLAT(S8* buffer)
{
	S8 i_spot_count = 0;
	while (*buffer != '\0')
	{
		if (*buffer == '.')
			i_spot_count++;
		else if (*buffer > '9' || *buffer < '0')
			return FALSE;
		buffer++;
	}
	if (i_spot_count != 1)
		return FALSE;
	return TRUE;
}

//Obtain the passwords of new and old users.
S32 Neoway_GetNewAndOldPassword(S8* p_ud, S8* p_new_psd, S8* p_old_psd)
{
	S32 n_num_len = 0;
	p_ud += 5;
	while (*p_ud != '#')
	{
		*p_new_psd++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_old_psd++ = *p_ud++;
		n_num_len++;
	}
	return n_num_len;
	p_ud++;
}

//Obtain the user names.
S32 Neoway_GetUserName(S8* p_ud, S8* p_username)
{
	S32 n_num_len = 0;
	memset(p_username, 0, strlen(p_username));
	p_ud += 5;
	while (*p_ud != '#')
	{
		*p_username++ = *p_ud++;
		n_num_len++;
	}
	return n_num_len;
}

//Obtain the APN.
S32 Neoway_GetAPN(S8* p_ud, S8* p_apn, S8* p_username, S8* p_login_psd)
{
	S32 n_num_len = 0;
	p_ud += 5;
	while (*p_ud != '#')
	{
		*p_apn++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_username++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_login_psd++ = *p_ud++;
		n_num_len++;
	}
	return n_num_len;
}



//Obtain the server address and port number.
S32 Neoway_GetCenterSVRAddrPort(S8* p_ud, S8* p_addr, S8* p_port)
{
	S32 n_num_len = 0;
	memset(p_addr, 0, strlen(p_addr));
	memset(p_port, 0, strlen(p_port));
	p_ud += 5;
	while (*p_ud != '#')
	{
		*p_addr++ = *p_ud++;
		n_num_len++;
	}
	p_ud++;
	n_num_len++;
	while (*p_ud != '#')
	{
		*p_port++ = *p_ud++;
		n_num_len++;
	}
	return n_num_len;
}


//Obtain the password of the command.
BOOL Neoway_GetCmdPassword(S8* p_ud, S8* p_psd, int n_len)
{
	int i_count = 0;
	p_ud += n_len;
	while (*p_ud != '#')
	{
		*p_psd++ = *p_ud++;
		i_count++;
		if (i_count > 4)
			return FALSE;
	}
	if (i_count != 4)
		return FALSE;
	return TRUE;
}

//Obtain the password that controls operation commands 988/987.
BOOL Neoway_GetCtrPassword(S8* p_ud, S8* p_psd, int n_len)
{
	int i_count = 0;
	p_ud += n_len;
	while (*p_ud != '\0')
	{
		*p_psd++ = *p_ud++;
		i_count++;
	}
	if (i_count != 4)
		return FALSE;
	return TRUE;
}

//Check the input password.
BOOL Neoway_CheckCmdPassword(S8* p_psd_send, S8* p_psd_cek)
{
	if (strcmp(p_psd_send, p_psd_cek) == 0)
		return TRUE;
	return FALSE;
}

//Obtain the incoming call number.
void Neoway_GetCallNumber(S8* p_clip ,S8* p_phone)
{
	p_clip += 8;
	while (*p_clip != '\"')
	{
		*p_phone++ = *p_clip++;
	}
}

/* double atof(char* p_val)
{
	double val, power = 1.0;
	while (*p_val != '.')
	{
		val = 10.0 * val + (*p_val - '0');
		p_val++;
	}
	p_val++;
	while (*p_val != '\0')
	{
		val = 10.0 * val + (*p_val - '0');
		power *= 10.0;
		p_val++;
	}
	return val / power;
}
 */


#define NEOWAY_RET_ERR_PASSWORD_ERROR		1
#define NEOWAY_RET_ERR_RET_OK	2
#define NEOWAY_RET_ERR_RET_OPERATE_FAIL 	3

void Neoway_SendSMSContent(Neoway_SM_PARAM_Struct* p_sm_param, Neoway_CustomCmdEnum cmd, int cmd_state)
{
	memset(p_sm_param->TP_UD, 0, 128);
	p_sm_param->TP_DCS = 0x08;
	switch(cmd)
	{
	case SET_SCA_NUM_CMD:// 710
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");
		break;
	case SET_DIAL_CMD:// 711
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");
		break;
	case SET_ECHO_DATA_CMD:// 730
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");
		break;
	case SET_TIME_CONFIG_CMD:// 735
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");
		break;
	case SET_PSD_CHANGE_CMD:	// 770
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");
		break;
	case SET_USERNAME_CMD:		// 801
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");
		break;
	case SET_APN_CONFIG_CMD:// 802
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");
		break;
	case SET_SVR_ADDR_CMD:	// 803
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");	
		break;
	case SET_SVR_POSI_SCH_CMD:	// 988
		if (cmd_state == NEOWAY_RET_ERR_RET_OK)
			strcpy(p_sm_param->TP_UD, "002600370031003000268BBE7F6E6210529F00260026");
		else if (cmd_state == NEOWAY_RET_ERR_PASSWORD_ERROR)
			strcpy(p_sm_param->TP_UD, "002600370031003000265BC6780195198BEF00260026");
		else
			strcpy(p_sm_param->TP_UD, "00260037003100300026004E00568BBE7F6E59318D2500260026");	
		break;
	case SET_INVALID_CMD:
		
		break;
	default:
		strcpy(p_sm_param->TP_UD, "002663074EE4683C5F0F4E0D6B63786EFF0C8BF768C067E5FF0100260026");
		break;
	}
}


void Neoway_SendSMS(Neoway_SM_PARAM_Struct* p_sm_param)
{
	S32 n_pdu_len;
	S32 n_send_len;
	U8 n_smsc_len;	//SMSC string length
	S8 sz_pdu[512] = {0};
	S8 sz_at_send_sms[16]= "AT+CMGS=";
	
	if ((p_sm_param->TPA[0] != 56) || (p_sm_param->TPA[1] != 54))
		p_sm_param->TP_DAType = 0xA1;
	else if ((p_sm_param->TPA[0] == 56) && (p_sm_param->TPA[1] == 54))
		p_sm_param->TP_DAType = 0x91;

	n_pdu_len = Neoway_SmsEncodePdu(p_sm_param, sz_pdu);	//Obtain the packets to be sent
	Neoway_PduString2Bytes(sz_pdu, &n_smsc_len, 2);	//Parse the packet length.
	n_send_len = n_pdu_len/2 - (n_smsc_len+1);

	sz_pdu[strlen(sz_pdu)] = '\x01A';
	if (n_send_len < 100)
	{
		sz_at_send_sms[8] = (int)(n_send_len /10) + 48;
		sz_at_send_sms[9] = (int)(n_send_len %10) + 48;
		sz_at_send_sms[10] = 0x0d;
	}
	else
	{
		sz_at_send_sms[8] = (int)(n_send_len /100) + 48;
		sz_at_send_sms[9] = (int)((n_send_len %100) / 10) + 48;
		sz_at_send_sms[10] = (int)((n_send_len %100) % 10) + 48;
		sz_at_send_sms[11] = 0x0d;
	}
//	Neoway_Print(sz_at_send_sms);
//	Neoway_Print(sz_pdu);
//	Neoway_Print("Neoway_SendAT");
	Neo_SendAT(CMD_CMGS,sz_at_send_sms,strlen(sz_at_send_sms),sz_pdu,strlen(sz_pdu));
}


