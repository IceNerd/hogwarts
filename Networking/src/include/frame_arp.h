/*************************************************************************
Alberto Martinez
04/10/2005

frame_arp.h
*************************************************************************/
#ifndef FRAME_ARP_H
#define FRAME_ARP_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <vector>

#include "property.h"
#include "hexfun.h"
#include "frame_arp_struct.h"

class frame_ARP
{
public:
	frame_ARP();
	~frame_ARP();

	//--- Input ----------------------------------------------------------
	void NewPacket( unsigned char* );

	//--- Output ---------------------------------------------------------
	int HWAddr() const;
	std::string ProtoAddr() const;
	int HAddrLen() const;
	int PAddrLen() const;
	int Operation() const;
	std::string HAddrSender() const;
	std::string PAddrSender() const;
	std::string HAddrTarget() const;
	std::string PAddrTarget() const;

	void PrintCache() const;


private:
	unsigned char* ptr_Packet;
	frame_ARP_struct* ARPFrame;

	std::vector< std::vector< std::string > > tblARPCache;

protected:

};

#endif