/*************************************************************************
Alberto Martinez
04/10/2005

frame_ethernet.h

Structure of the ethernet frame to be captured from packet data
**************************************************************************/
#ifndef FRAME_ETHERNET_H
#define FRAME_ETHERNET_H

	struct frame_EtherNet
	{
		unsigned char DestAddr[6];
		unsigned char SrcAddr[6];
		unsigned char LenType[2];
	};

#endif