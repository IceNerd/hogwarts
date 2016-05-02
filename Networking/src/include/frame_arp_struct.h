/*************************************************************************
Alberto Martinez
05/10/2005

frame_arp_struct.h
**************************************************************************/
#ifndef FRAME_ARP_STRUCT_H
#define FRAME_ARP_STRUCT_H

	struct frame_ARP_struct
	{
		unsigned char HWAddr[2];
		unsigned char ProtoAddr[2];
		unsigned char HAddrLen;
		unsigned char PAddrLen;
		unsigned char Operation[2];
		unsigned char HeadOfAddrs[20];
		//unsigned char PAddrSender[4];
		//unsigned char HAddrTarget[4];
		//unsigned char PAddrTarget[4];
	};

#endif