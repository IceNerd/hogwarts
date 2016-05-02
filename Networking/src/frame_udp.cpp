#include "frame_udp.h"

const unsigned int UDP_HEADER_SIZE( 8 );

//--- Constructor --------------------------------------------------------
frame_UDP::frame_UDP( unsigned char* ptr_NewPacket )
{
	ptr_Packet = ptr_NewPacket;

	UDPFrame = (frame_UDP_struct*)ptr_Packet;
}

//--- Deconstructor ------------------------------------------------------
frame_UDP::~frame_UDP()
{
}

int frame_UDP::SourcePort() const
{
	return TwoByteToDecimal( this->UDPFrame->SrcPort[0],  this->UDPFrame->SrcPort[1] );
}

int frame_UDP::DestinationPort() const
{
	return TwoByteToDecimal( this->UDPFrame->DestPort[0], this->UDPFrame->DestPort[1] );
}

int frame_UDP::Length() const
{
	return TwoByteToDecimal( this->UDPFrame->Length[0],  this->UDPFrame->Length[1] );
}

std::string frame_UDP::CheckSum() const
{
	std::string strReturn;

	strReturn = ToHex( this->UDPFrame->CheckSum[0] );
	strReturn += ToHex( this->UDPFrame->CheckSum[1] );

	return strReturn;
}

unsigned char* frame_UDP::Data() const
{
	unsigned char* ptr_Data = ptr_Packet;

	ptr_Data += UDP_HEADER_SIZE;

	return ptr_Data;
}