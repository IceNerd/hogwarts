/*************************************************************************
Alberto Martinez
04/10/2005

netpacket.h

Conatiner class for managing different parses of sniffed packets.
**************************************************************************/
#ifndef NETPACKET_H
#define NETPACKET_H

/***** winpcap library must be installed *****/
/***********/#include <pcap.h>/***************/
/*********************************************/

#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <string>

#include "property.h"
#include "exception.h"
#include "hexfun.h"
#include "frame_ethernet.h"
//#include "frame_ip.h"

	class NetPacket
	{
	public:
	//--- Constructor ----------------------------------------------------
		NetPacket( const std::string&  = "ethtype.dat" );

	//--- Deconstructor --------------------------------------------------
		~NetPacket();

	//--- Input ----------------------------------------------------------
		void NewPacket( struct pcap_pkthdr*, unsigned char* );

	//--- Output ---------------------------------------------------------
		unsigned char* GetPacket();
		std::string DestAddr();
		std::string SrcAddr();
		std::string* FindTypeDesc( const int& );
		std::string LenTypeHex();

	//--- Properties -----------------------------------------------------
		Property< int > Size;
		Property< int > LenType;
		Property< unsigned char* > Packet;

	private:
	//--- Private Members ------------------------------------------------
		int iSize;
		int iLenType;
		unsigned char* ptr_Packet;

		//--- Packet Frames ----------------------------------------------
		frame_EtherNet* EFrame;

	protected:
	//--- Protected Members ----------------------------------------------
		std::map< int, std::string* > mapTypes;
		std::list< std::string* > lstTypeDesc;

	//--- Protected Functions --------------------------------------------
		void PropogateTypes( const std::string& );

	};

#endif