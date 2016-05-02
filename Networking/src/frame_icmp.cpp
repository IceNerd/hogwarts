#include "frame_icmp.h"

const unsigned int ICMP_HEADER_SIZE( 4 );

//--- Constructor --------------------------------------------------------
frame_ICMP::frame_ICMP( unsigned char* ptr_newPacket )
{
	ptr_Packet = ptr_newPacket;

	ICMPFrame = (frame_ICMP_struct*)ptr_Packet;
}

//--- Deconstructor ------------------------------------------------------
frame_ICMP::~frame_ICMP()
{
}

int frame_ICMP::Type() const
{
	return ByteToDecimal( this->ICMPFrame->Type );
}

int frame_ICMP::Code() const
{
	return ByteToDecimal( this->ICMPFrame->Code );
}

std::string frame_ICMP::CheckSum() const
{
	std::string strReturn;

	strReturn = ToHex( this->ICMPFrame->CheckSum[0] );
	strReturn += ToHex( this->ICMPFrame->CheckSum[1] );

	return strReturn;
}

unsigned char* frame_ICMP::Data() const
{
	unsigned char* ptr_Data = ptr_Packet;

	ptr_Data += ICMP_HEADER_SIZE;

	return ptr_Data;
}