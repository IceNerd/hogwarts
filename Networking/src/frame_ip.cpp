#include "frame_ip.h"

//Location of the IP header is after the Ethernet header.  The size
//of the ethernet header is 14 bytes.
const unsigned int ETHERNET_HEADER_SIZE( 14 );
const unsigned int IP_HEADER_SIZE( 20 );

//--- Constructor --------------------------------------------------------
	frame_IP::frame_IP()
	:Packet( &ptr_Packet )
	{
	}

	frame_IP::frame_IP( const frame_IP& cpyMe )
	:Packet( &ptr_Packet )
	{
	}

//--- Deconstructor ------------------------------------------------------
	frame_IP::~frame_IP()
	{
	}

//--- Input --------------------------------------------------------------

	/*** NewPacket *******************************************************
	This function lays down the initial structure over the incoming
	 packet for future parsing.
	*********************************************************************/
	void frame_IP::NewPacket( unsigned char* ptr_NewPacket )
	{
		ptr_Packet = ptr_NewPacket;
		ptr_Packet += ETHERNET_HEADER_SIZE;

		IPFrame = (frame_IP_struct*)ptr_Packet;
	}

//--- Output -------------------------------------------------------------
	/*** Version *********************************************************
	Getter function for retrieving the Version out of the IP packet.
	*********************************************************************/
	std::string frame_IP::Version() const
	{
		std::string strReturn;

		strReturn = HexAlphabet[(((int)IPFrame->VandIHL >> 4) & 0xF)];

		return strReturn;
	}

	/*** IHL *************************************************************
	Getter function for retrieving the IHL out of the IP packet.
	*********************************************************************/
	std::string frame_IP::IHL() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( ByteToDecimal( IPFrame->VandIHL & 0x0F ) * 4, buffer, 10 );
		strReturn = buffer;

		return strReturn;
	}

	/*** TypeOfService **************************************************
	Getter function for retrieving the type of service out of the IP
	 packet.
	*********************************************************************/
	std::string frame_IP::TypeOfService() const
	{
		std::string strReturn;

		strReturn = ToHex( IPFrame->TypeOfService );

		return strReturn;
	}

	/*** Precedence **************************************************
	Getter function for retrieving the precedence out of the IP
	 packet.
	*********************************************************************/
	int frame_IP::Precedence() const
	{
		int iReturn;

		iReturn = ByteToDecimal( (IPFrame->TypeOfService >> 5) & 0xF );

		return iReturn;
	}

	/*** Delay ***********************************************************
	Getter function for retrieving the delay out of the Type of Service
	 portion of the IP Header.
	*********************************************************************/
	bool frame_IP::Delay() const
	{
		bool bReturn( false );

		if( ((IPFrame->TypeOfService >> 4) & 0xE) )
		{
			bReturn = true;
		}

		return bReturn;
	}

	/*** ThroughPut ******************************************************
	Getter function for retrieving the throughput out of the Type of
	 Service portion of the IP Header.
	*********************************************************************/
	bool frame_IP::Throughput() const
	{
		bool bReturn( false );

		if( ((IPFrame->TypeOfService >> 3) & 0xE) )
		{
			bReturn = true;
		}

		return bReturn;
	}

	/*** Reliability *****************************************************
	Getter function for retrieving the reliability out of the Type of
	 Service portion of the IP Header.
	*********************************************************************/
	bool frame_IP::Reliability() const
	{
		bool bReturn( false );

		if( ((IPFrame->TypeOfService >> 2) & 0xE) )
		{
			bReturn = true;
		}

		return bReturn;
	}

	/*** TotalLength *****************************************************
	Getter function for retrieving the total length out of the IP packet.
	*********************************************************************/
	std::string frame_IP::TotalLength() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( TwoByteToDecimal( IPFrame->TotalLength[0], IPFrame->TotalLength[1] ), buffer, 10 );
		strReturn = buffer;

		return strReturn;
	}

	/*** Identification **************************************************
	Getter function for retrieving the identification out of the IP
	 packet.
	*********************************************************************/
	std::string frame_IP::Identification() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( TwoByteToDecimal( IPFrame->Identification[0], IPFrame->Identification[1] ), buffer, 10 );
		strReturn = buffer;

		return strReturn;
	}

	/*** Flag01 **********************************************************
	Getter function for retrieving the first flag out of the IP packet.
	*********************************************************************/
	bool frame_IP::Flag01() const
	{
		bool bReturn( false );

		if( (((int)IPFrame->FlagsAndFragOff[0] >> 6) & 0x1) == 1 )
		{
			bReturn = true;
		}

		return bReturn;
	}

	/*** Flag02 **********************************************************
	Getter function for retrieving the second flag out of the IP packet.
	*********************************************************************/
	bool frame_IP::Flag02() const
	{
		bool bReturn( false );

		if( (((int)IPFrame->FlagsAndFragOff[0] >> 5) & 0x1) == 1 )
		{
			bReturn = true;
		}
		return bReturn;
	}

	/*** FragmentOffset **************************************************
	Getter function for retrieving the fragment offset out of the IP
	 packet.
	*********************************************************************/
	std::string frame_IP::FragmentOffset() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( TwoByteToDecimal( IPFrame->FlagsAndFragOff[0], ((int)IPFrame->FlagsAndFragOff[1]) & 0x1F ), buffer, 10 );
		strReturn = buffer;

		return strReturn;
	}

	/*** TimeToLive ******************************************************
	Getter function for retrieving the time the IP packet is to live out
	 of the IP packet.
	*********************************************************************/
	std::string frame_IP::TimeToLive() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( ByteToDecimal( IPFrame->TimeToLive ), buffer, 10 );
		strReturn = buffer;

		return strReturn;
	}

	/*** Protocol ********************************************************
	Getter function for retrieving the protocol out of the IP packet.
	*********************************************************************/
	std::string frame_IP::Protocol() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( ByteToDecimal( IPFrame->Protocol ), buffer, 10 );
		strReturn = buffer;

		return strReturn;
	}

	int frame_IP::ProtocolNum() const
	{
		return ByteToDecimal( IPFrame->Protocol );
	}

	/*** HeaderChksum ****************************************************
	Getter function for retrieving the checksum of the IP packet.
	*********************************************************************/
	std::string frame_IP::HeaderChksum() const
	{
		std::string strReturn;

		strReturn = ToHex( IPFrame->HeaderChkSum[0] );
		strReturn += ToHex ( IPFrame->HeaderChkSum[1] );

		return strReturn;
	}

	/*** SrcAddr *********************************************************
	Getter function for retrieving the source IP out of the IP packet.
	*********************************************************************/
	std::string frame_IP::SrcAddr() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( ByteToDecimal( IPFrame->SrcAddr[0] ), buffer, 10 );
		strReturn += buffer;
		strReturn += ".";

		_itoa_s( ByteToDecimal( IPFrame->SrcAddr[1] ), buffer, 10 );
		strReturn += buffer;
		strReturn += ".";

		_itoa_s( ByteToDecimal( IPFrame->SrcAddr[2] ), buffer, 10 );
		strReturn += buffer;
		strReturn += ".";
		
		_itoa_s( ByteToDecimal( IPFrame->SrcAddr[3] ), buffer, 10 );
		strReturn += buffer;

		return strReturn;
	}

	/*** SrcName *********************************************************
	Getter function for retrieving the source IP resolution out of the IP
	 header.
	*********************************************************************/
	std::string frame_IP::SrcName() const
	{
		std::string strReturn;

		//Resolve Source IP
		hostent* HostInfo;
		HostInfo = gethostbyaddr( (char*)IPFrame->SrcAddr, 4, AF_INET );
		if( HostInfo )
		{
			strReturn = HostInfo->h_name;
		}
		else
		{
			strReturn = "Unknown";
		}

		return strReturn;
	}

	/*** DestAddr ********************************************************
	Getter function for retrieving the destination IP out of the IP
	 packet.
	*********************************************************************/
	std::string frame_IP::DestAddr() const
	{
		std::string strReturn;
		char buffer[25];

		_itoa_s( ByteToDecimal( IPFrame->DestAddr[0] ), buffer, 10 );
		strReturn += buffer;
		strReturn += ".";

		_itoa_s( ByteToDecimal( IPFrame->DestAddr[1] ), buffer, 10 );
		strReturn += buffer;
		strReturn += ".";

		_itoa_s( ByteToDecimal( IPFrame->DestAddr[2] ), buffer, 10 );
		strReturn += buffer;
		strReturn += ".";
		
		_itoa_s( ByteToDecimal( IPFrame->DestAddr[3] ), buffer, 10 );
		strReturn += buffer;

		return strReturn;
	}

	/*** DestName ********************************************************
	Getter function for retrieving the destination IP resolution out of
	 the IP header.
	*********************************************************************/
	std::string frame_IP::DestName() const
	{
		std::string strReturn;

		//Resolve Destination IP
		hostent* HostInfo;
		HostInfo = gethostbyaddr( (char*)IPFrame->DestAddr, 4, AF_INET );
		if( HostInfo )
		{
			strReturn = HostInfo->h_name;
		}
		else
		{
			strReturn = "Unknown";
		}

		return strReturn;
	}

	/*** Options *********************************************************
	Getter function for retrieving the options out of the IP packet.
	*********************************************************************/
	std::string frame_IP::Options() const
	{
		std::string strReturn;

		strReturn = ToHex( IPFrame->Options[0] );
		strReturn += ToHex( IPFrame->Options[1] );
		strReturn += ToHex( IPFrame->Options[2] );

		return strReturn;
	}

	unsigned char* frame_IP::DataPtr() const
	{
		unsigned char* ptr_Data = ptr_Packet;

		ptr_Data += IP_HEADER_SIZE;

		return ptr_Data;
	}

//--- Private Functions --------------------------------------------------