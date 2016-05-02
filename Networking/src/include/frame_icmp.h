/*************************************************************************
Alberto Martinez
04/10/2005

frame_ip.h

Structure of the ip frame to be captured from packet data
*************************************************************************/

#ifndef FRAME_ICMP_H
#define FRAME_ICMP_H

#include <string>

#include "hexfun.h"

struct frame_ICMP_struct
{
	unsigned char Type;
	unsigned char Code;
	unsigned char CheckSum[2];
	unsigned char Data;
};

	class frame_ICMP
	{
		public:
			frame_ICMP( unsigned char* );
			~frame_ICMP();

			int Type() const;
			int Code() const;
			std::string CheckSum() const;

			unsigned char* Data() const;

		protected:

		private:
			frame_ICMP_struct* ICMPFrame;
			unsigned char* ptr_Packet;
	};

#endif