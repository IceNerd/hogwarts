/*************************************************************************
Alberto Martinez
04/10/2005

frame_ip.h

Structure of the ip frame to be captured from packet data
*************************************************************************/

#ifndef FRAME_TCP_H
#define FRAME_TCP_H

#include <string>

#include "hexfun.h"

struct frame_TCP_struct
{
	unsigned char SrcPort[2];
	unsigned char DestPort[2];
	unsigned char SeqNum[4];
	unsigned char AckNum[4];
	unsigned char DO_ECN_CB[2];
		//DO = Data Offset(4 bits)
		//(3bits) reserved
		//ECN(3 bits)
		//CB = Control Bits(6 bits)
	unsigned char Window[2];
	unsigned char CheckSum[2];
	unsigned char Urgent_Ptr[2];
	unsigned char Data;
};

	class frame_TCP
	{
		public:
			frame_TCP( unsigned char* );
			~frame_TCP();

			int SourcePort() const;
			int DestinationPort() const;
			std::string SequenceNumber() const;
			std::string AckNumber() const;
			int DataOffset() const;
			bool N_ECN() const;
			bool C_ECN() const;
			bool E_ECN() const;
			bool CB0() const;
			bool CB1() const;
			bool CB2() const;
			bool CB3() const;
			bool CB4() const;
			bool CB5() const;
			int Window() const;
			std::string CheckSum() const;
			int UrgentPtr() const;
			unsigned char* Data() const;

		protected:

		private:
			frame_TCP_struct* TCPFrame;
			unsigned char* ptr_Packet;
	};

#endif