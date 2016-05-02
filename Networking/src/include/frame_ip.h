/*************************************************************************
Alberto Martinez
04/10/2005

frame_ip.h

Structure of the ip frame to be captured from packet data
*************************************************************************/
#ifndef FRAME_IP_H
#define FRAME_IP_H

#include <iostream>
#include <string>
#include <winsock2.h>

#include "property.h"
#include "hexfun.h"
#include "frame_ip_struct.h"

class frame_IP
{
	public:
	//--- Constructor ----------------------------------------------------
		frame_IP();
		frame_IP( const frame_IP& );
	//--- Deconstructor --------------------------------------------------
		virtual ~frame_IP();

	//--- Input ----------------------------------------------------------
		void NewPacket( unsigned char* );

	//--- Output ---------------------------------------------------------
		std::string Version() const;
		std::string IHL() const;
		std::string TypeOfService() const;
		int Precedence() const;
		bool Delay() const;
		bool Throughput() const;
		bool Reliability() const;
		std::string TotalLength() const;
		std::string Identification() const;
		bool Flag01() const;
		bool Flag02() const;
		std::string FragmentOffset() const;
		std::string TimeToLive() const;
		std::string Protocol() const;
		int ProtocolNum() const;
		std::string HeaderChksum() const;
		std::string SrcAddr() const;
		std::string SrcName() const;
		std::string DestAddr() const;
		std::string DestName() const;
		std::string Options() const;

		unsigned char* DataPtr() const;

	//--- Properties -----------------------------------------------------
		Property< unsigned char* > Packet;

	private:
		unsigned char* ptr_Packet;
		frame_IP_struct* IPFrame;
	//--- Private Functions ----------------------------------------------

	protected:
	//--- Protected Members ----------------------------------------------

};

#endif