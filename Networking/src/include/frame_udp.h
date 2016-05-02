/*************************************************************************
Alberto Martinez
04/10/2005

frame_ip.h

Structure of the ip frame to be captured from packet data
*************************************************************************/

#ifndef FRAME_UDP_H
#define FRAME_UDP_H

#include <string>

#include "hexfun.h"

struct frame_UDP_struct
{
	unsigned char SrcPort[2];
	unsigned char DestPort[2];
	unsigned char Length[2];
	unsigned char CheckSum[2];
	unsigned char Data;
};

	class frame_UDP
	{
		public:
			frame_UDP( unsigned char* );
			~frame_UDP();

			int SourcePort() const;
			int DestinationPort() const;
			int Length() const;
			std::string CheckSum() const;
			unsigned char* Data() const;

		protected:

		private:
			frame_UDP_struct* UDPFrame;
			unsigned char* ptr_Packet;
	};

#endif