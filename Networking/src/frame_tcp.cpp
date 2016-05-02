#include "frame_tcp.h"

const unsigned int TCP_HEADER_SIZE( 20 );

//--- Constructor --------------------------------------------------------
frame_TCP::frame_TCP( unsigned char* ptr_NewPacket )
{
	ptr_Packet = ptr_NewPacket;

	TCPFrame = (frame_TCP_struct*)ptr_Packet;
}

//--- Deconstructor ------------------------------------------------------
frame_TCP::~frame_TCP()
{
}

int frame_TCP::SourcePort() const
{
	return TwoByteToDecimal( this->TCPFrame->SrcPort[0],  this->TCPFrame->SrcPort[1] );
}

int frame_TCP::DestinationPort() const
{
	return TwoByteToDecimal( this->TCPFrame->DestPort[0], this->TCPFrame->DestPort[1] );
}

std::string frame_TCP::SequenceNumber() const
{
	std::string strReturn;

	strReturn = ToHex( this->TCPFrame->SeqNum[0] );
	strReturn += ToHex( this->TCPFrame->SeqNum[1] );
	strReturn += ToHex( this->TCPFrame->SeqNum[2] );
	strReturn += ToHex( this->TCPFrame->SeqNum[3] );

	return strReturn;
}

std::string frame_TCP::AckNumber() const
{
	std::string strReturn;

	strReturn = ToHex( this->TCPFrame->AckNum[0] );
	strReturn += ToHex( this->TCPFrame->AckNum[1] );
	strReturn += ToHex( this->TCPFrame->AckNum[2] );
	strReturn += ToHex( this->TCPFrame->AckNum[3] );

	return strReturn;
}

int frame_TCP::DataOffset() const
{
	return (((int)this->TCPFrame->DO_ECN_CB[0] >> 4) & 0xF);
}

bool frame_TCP::N_ECN() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[0] >> 1) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::C_ECN() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[0] ) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::E_ECN() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[1] >> 6) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::CB0() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[1] >> 5) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::CB1() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[1] >> 4) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::CB2() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[1] >> 3) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::CB3() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[1] >> 2) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::CB4() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[1] >> 1) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

bool frame_TCP::CB5() const
{
	bool bReturn( false );

	if( (((int)this->TCPFrame->DO_ECN_CB[1]) & 0x1) )
	{
		bReturn = true;
	}

	return bReturn;
}

int frame_TCP::Window() const
{
	return TwoByteToDecimal( this->TCPFrame->Window[0],  this->TCPFrame->Window[1] );
}

std::string frame_TCP::CheckSum() const
{
	std::string strReturn;

	strReturn = ToHex( this->TCPFrame->CheckSum[0] );
	strReturn += ToHex( this->TCPFrame->CheckSum[1] );

	return strReturn;
}

int frame_TCP::UrgentPtr() const
{
	return TwoByteToDecimal( this->TCPFrame->Urgent_Ptr[0],  this->TCPFrame->Urgent_Ptr[1] );
}

unsigned char* frame_TCP::Data() const
{
	unsigned char* ptr_Data = ptr_Packet;

	ptr_Data += TCP_HEADER_SIZE;

	return ptr_Data;
}