/*************************************************************************
Alberto Martinez
05/02/2005

frame_ip_struct.h

This is the initial "laydown" structure for parsing the IP header.
The reason this is seperate is because there must be a parent to handle
the flags portion of the header.
**************************************************************************/
#ifndef FRAME_IP_STRUCT_H
#define FRAME_IP_STRUCT_H

	struct frame_IP_struct
	{
		unsigned char VandIHL;
		unsigned char TypeOfService;
		unsigned char TotalLength[2];
		unsigned char Identification[2];
		unsigned char FlagsAndFragOff[2];
		unsigned char TimeToLive;
		unsigned char Protocol;
		unsigned char HeaderChkSum[2];
		unsigned char SrcAddr[4];
		unsigned char DestAddr[4];
		unsigned char Options[3];
		unsigned char Padding;
	};

#endif