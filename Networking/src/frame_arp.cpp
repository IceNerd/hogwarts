#include "frame_arp.h"

#define IPADDR 0
#define HWADDR 1

#define MYIPADDR "140.211.142.107"
#define MYPHYSADDR "00-11-F5-A5-4C-E4"

//Location of the IP header is after the Ethernet header.  The size
//of the ethernet header is 14 bytes.
const unsigned int ETHERNET_HEADER_SIZE( 14 );


	frame_ARP::frame_ARP()
	{
	}

	frame_ARP::~frame_ARP()
	{
	}

	void frame_ARP::NewPacket( unsigned char* ptr_NewPacket )
	{
		bool bMerge( false );
		int iFound( -1 );
		//parse it here
		ptr_Packet = ptr_NewPacket;
		ptr_Packet += ETHERNET_HEADER_SIZE;

		ARPFrame = (frame_ARP_struct*)ptr_Packet;

		//ARP Algorithm
		//yes:yes
		bMerge = false;
		for( int i = 0; i < this->tblARPCache.size() && iFound == -1; ++i )
		{
			if( this->tblARPCache[i][HWADDR] == this->PAddrSender() )
			{
				iFound = i;
				this->tblARPCache[i][HWADDR] = this->HAddrSender();
				bMerge = true;
			}
		}

		//am I the target protocol address?
		if( this->PAddrTarget() == MYIPADDR )
		{
			//If Merge_flag is false, add the triplet <protocol type,
			//sender protocol address, sender hardware address> to the
			//translation table.
			if( !bMerge )
			{
				std::vector< std::string > lstItem;
				lstItem.push_back( this->PAddrSender() );
				lstItem.push_back( this->HAddrSender() );
				bMerge = true;
				for( int i = 0; i < this->tblARPCache.size() && bMerge; ++i )
				{
					if( this->tblARPCache[i][IPADDR] == this->PAddrSender() )
					{
						bMerge = false;
					}
				}

				if( bMerge )
				{
					tblARPCache.push_back( lstItem );
				}
			}

			if( this->Operation() == 1 )
			{
				//Generate Response
				/*Swap hardware and protocol fields, putting the local
	    				hardware and protocol addresses in the sender fields.
				Set the ar$op field to ares_op$REPLY
				Send the packet to the (new) target hardware address on
	    				the same hardware on which the request was received*/

				std::cout<<"\n--- ARP Response -----------------------------------------\n";
					
				std::cout<<"Hardware Address: "<<this->HWAddr()<<"\n"
						 <<"Protocol Address: "<<this->ProtoAddr()<<"\n"
						 <<"H Addr Len: "<<this->HWAddr()<<" bytes\n"
						 <<"P Addr Len: "<<this->ProtoAddr()<<" bytes\n"
						 <<"Operation: "<<"2 (ARP Response)"<<"\n"
						 <<"Hardware Address of Sender: "<<MYPHYSADDR<<"\n"
						 <<"Protocol Address of Sender: "<<MYIPADDR<<"\n"
						 <<"Hardware Address of Target: "<<this->HAddrSender()<<"\n"
						 <<"Protocol Address of Target: "<<this->PAddrSender()<<"\n";
			}
		}
	}



	int frame_ARP::HWAddr() const
	{
		return TwoByteToDecimal( ARPFrame->HWAddr[0], ARPFrame->HWAddr[1] );
	}

	std::string frame_ARP::ProtoAddr() const
	{
		std::string strReturn;

		strReturn = ToHex( ARPFrame->ProtoAddr[0] );
		strReturn += ToHex( ARPFrame->ProtoAddr[1] );

		return strReturn;
	}

	int frame_ARP::HAddrLen() const
	{
		return ByteToDecimal( ARPFrame->HAddrLen );
	}

	int frame_ARP::PAddrLen() const
	{
		return ByteToDecimal( ARPFrame->PAddrLen );
	}

	int frame_ARP::Operation() const
	{
		return TwoByteToDecimal( ARPFrame->Operation[0], ARPFrame->Operation[1] );
	}

	std::string frame_ARP::HAddrSender() const
	{
		std::string strReturn;

		if( this->Operation() != 3 )
		{
			for( int i = 0; i < this->HAddrLen(); ++i )
			{
				strReturn += ToHex( ARPFrame->HeadOfAddrs[i] );
				if( i < this->HAddrLen() - 1 )
				{
					strReturn += "-";
				}
			}
		}
		else
		{
			strReturn = "none";
		}

		return strReturn;
	}

	std::string frame_ARP::PAddrSender() const
	{
		std::string strReturn;
		char buffer[25];
		int iOffset(0);

		//check to see if there was an HAddrSender
		if( this->Operation() != 3 )
		{
			iOffset += this->HAddrLen();
		}

		for( int i = 0; i < this->PAddrLen(); ++i )
		{
			_itoa_s( ByteToDecimal( ARPFrame->HeadOfAddrs[i + iOffset] ), buffer, 10 );
			strReturn += buffer;
			if( i < this->PAddrLen() - 1 )
			{
				strReturn += ".";
			}
		}

		return strReturn;
	}

	std::string frame_ARP::HAddrTarget() const
	{
		std::string strReturn;

		if( this->Operation() == 1 )
		{
			strReturn = "?";
		}
		else
		{
			//Offset = Hardware Addres of Sender + Protocol
			//Address of sender since operation = 2
			for( int i = 0; i < this->HAddrLen(); ++i )
			{
				strReturn += ToHex( ARPFrame->HeadOfAddrs[i + this->HAddrLen() + this->PAddrLen()] );
				if( i < this->HAddrLen() - 1 )
				{
					strReturn += "-";
				}
			}
		}

		return strReturn;
	}

	std::string frame_ARP::PAddrTarget() const
	{
		std::string strReturn;
		int iOffset(0);
		char buffer[25];

		if( this->Operation() < 3 )
		{
			iOffset += this->HAddrLen() + this->PAddrLen() + this->HAddrLen();

			for( int i = 0; i < this->PAddrLen(); ++i )
			{
				_itoa_s( ByteToDecimal( ARPFrame->HeadOfAddrs[i + iOffset] ), buffer, 10 );
				strReturn += buffer;
				if( i < this->PAddrLen() - 1 )
				{
					strReturn += ".";
				}
			}

		}
		else
		{
			strReturn = "undefined";
		}

		return strReturn;
	}

	void frame_ARP::PrintCache() const
	{
		std::cout<<"\nIP Address-------------------PHYS Address\n";
		for( int i = 0; i < tblARPCache.size(); ++i )
		{
			std::cout<<tblARPCache[i][IPADDR]<<"  "<<tblARPCache[i][HWADDR]<<"\n";
		}
	}