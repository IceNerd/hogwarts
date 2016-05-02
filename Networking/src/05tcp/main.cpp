/*************************************************************************
Alberto Martinez
05/02/2005

main.cpp

Lab 05 - Parsing TCP Packets
Keyboard Toggles
0 - Dump Arp Table
1 - IP
2 - ICMP
3 - UDP
4 - TCP
5 - ARP
6 - All
**************************************************************************/
#include <iostream>
#include <conio.h>//for getch()
#include <string>

#include <pcap.h>

#include "exception.h"
#include "netpacket.h"
#include "frame_ip.h"
#include "frame_icmp.h"
#include "frame_tcp.h"
#include "frame_udp.h"
#include "frame_arp.h"

#define LINE_LEN 16

void PrintRawPacket( struct pcap_pkthdr*, u_char* );
void PrintAddress( unsigned char* );
void PrintIPPacket( const frame_IP& );
void PrintICMPPacket( const frame_IP& );
void PrintTCPPacket( const frame_IP&, const bool&, const bool&, const bool& );
void PrintUDPPacket( const frame_IP& );
void PrintARPPacket( const frame_ARP& );
void PrintTCPProtocol( const int& );

int main()
{
	bool ARPInfo( false );
	bool IPInfo( false );
		bool ICMPInfo( false );
		bool UDPInfo( false );
		bool TCPInfo( false );
	bool AllInfo( false );

	pcap_if_t* alldevs;
	pcap_if_t* d;
	pcap_t* fp;
	u_int inum;
	u_int i(0);
	char errbuf[PCAP_ERRBUF_SIZE];
	int res;
	struct pcap_pkthdr* header;
	u_char* pkt_data;

	std::cout<<"prints the packets of the network using WinPcap.\n"
			 <<"   Usage: <exe> [-s source]\n\n"
             <<"   Examples:\n"
             <<"      <exe> -s file://c:/temp/file.acp\n"
             <<"      <exe> -s rpcap://\\Device\\NPF_{C8736017-F3C3-4373-94AC-9A34B7DAD998}\n\n";
try
{
	NetPacket Traffic;
	frame_IP IPFrame;
	frame_ARP ARPFrame;

    if( argc < 3 )//--- handle user input -----
    {
		printf("\nNo adapter selected: printing the device list:\n");
		/* The user didn't provide a packet source: Retrieve the local device list */
		if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
		{
			std::string strErr( "Error in pcap_findalldevs_ex: " );
			strErr += errbuf;
			throw Exception< std::string >( strErr );
		}
	    
		//--- Print the list of devices
		for( d = alldevs; d; d = d->next )
		{
			std::cout<<++i<<". "<<d->name<<"\n";

			if (d->description)
			{
				std::cout<<d->description<<"\n";
			}
			else
			{
				std::cout<<" (No description available)\n";
			}
		}
	    
		if ( i == 0 )
		{
			throw Exception< std::string >( "No interfaces found! Make sure WinPcap is installed." );
		}
		//--- Get interface number from user -----
		std::cout<<"Enter the interface number (1-"<<i<<"):";
		inum = _getch() - 48;
	    
		if(inum < 1 || inum > i)
		{
			/* Free the device list */
			pcap_freealldevs(alldevs);
			throw Exception< std::string >( "Interface number out of range." );
		}
	    
		//--- Jump to the selected adapter
		for( d = alldevs, i = 0; i < inum - 1 ; d = d->next, ++i );
	    
		//--- Open the device
		if ( (fp= pcap_open(d->name,
							100,						//snaplen
							0/*PCAP_OPENFLAG_PROMISCUOUS*/,	//flags
							20,							//read timeout
							NULL,						//remote authentication
							errbuf)
							) == NULL)
		{
			throw Exception< std::string >( "Error opening adapter" );
		}
	}
	else//--- handle the command line -----
	{
		//Do not check for the switch type ('-s')
		if ( (fp= pcap_open(argv[2],
							100,						//snaplen
							0/*PCAP_OPENFLAG_PROMISCUOUS*/,	//flags
							20,							//read timeout
							NULL,						//remote authentication
							errbuf)
							) == NULL)
		{
			std::string strErr( "Error in pcap_findalldevs_ex: " );
			strErr += errbuf;
			throw Exception< std::string >( strErr );
		}
	}

	//build data structure for types

		
//if we make it to this point in the program, we can read packets
//--- Packet Handler Here ------------------------------------------------
	while( (res = pcap_next_ex( fp, &header, (const unsigned char**)&pkt_data)) >= 0 )
	{

		if(res == 0)
		{
			//--- Timeout elapsed
			continue;
		}

		//--- Send Packet to Packet Translator
		Traffic.NewPacket( header, pkt_data );

		//--- Filter -----------------------------------------------------
		if( AllInfo )
		{
			//--- Ethernet Frame -----------------------------------------
			std::cout<<"--- Ethernet Frame -----------------------------------\n";
			//print size
			std::cout<<"Size: "<<Traffic.Size<<"\n";

			//print destination address
			std::cout<<"Destination Address: "
					 <<Traffic.DestAddr()
					 <<"\n";

			//print source address
			std::cout<<"Source Address: "
					 <<Traffic.SrcAddr()
					 <<"\n";

			//--- Type Description ---------------------------------------
				std::cout<<"Ethertype: ";
				if( Traffic.FindTypeDesc( Traffic.LenType ) )
				{
					std::cout<<Traffic.LenTypeHex()<<" - "<<(*Traffic.FindTypeDesc( Traffic.LenType ));
				}
				else
				{
					std::cout<<Traffic.LenTypeHex()<<" - unknown";
				}
				std::cout<<"\n";
		}

		//--- Type handling ------------------------------------------
		switch( Traffic.LenType )
		{
			case( 2048 )://IP
				if( IPInfo )
				{
					IPFrame.NewPacket( Traffic.Packet );
					PrintIPPacket( IPFrame, ICMPInfo, UDPInfo, TCPInfo );
				}
			break;

			case( 2054 )://ARP
				if( ARPInfo )
				{
					ARPFrame.NewPacket( Traffic.Packet );
					PrintARPPacket( ARPFrame );
				}
			break;

			default://UnhandledTypes
			break;
		}

		if( AllInfo )
		{
			std::cout<<"\n";
			PrintRawPacket( header, pkt_data );
			std::cout<<"\n\n"<<std::endl;
		}

		if( _kbhit() )
		{
			switch( _getch() - 48 )
			{
				//dump ARP cache
				case( 0 ):
					ARPFrame.PrintCache();
				break;

				//IP Switch
				case( 1 ):
					IPInfo = !IPInfo;
				break;

				//ICMP Switch
				case( 2 ):
					ICMPInfo = !ICMPInfo;
				break;

				//UDP Switch
				case( 3 ):
					UDPInfo = !UDPInfo;
				break;

				//TCP Switch
				case( 4 ):
					TCPInfo = !TCPInfo;
				break;

				//ARP Switch
				case( 5 ):
					ARPInfo = !ARPInfo;
				break;

				//All Switch
				case( 6 ):
					AllInfo = !AllInfo;
				break;

				default:
				break;
			}
		}

	}

	if(res == -1)
	{
		std::string strErr( "Error reading the packets: " );
		strErr += pcap_geterr(fp);
		throw Exception< std::string >( strErr );
	}
//--- End Packet Handler -------------------------------------------------
}
//--- Error Handler Here -------------------------------------------------
catch( Exception< std::string >& exError )
{
	std::cout<<"\n\n--- ERROR --------------------\n"<<exError.GetValue()<<"\n"
			 <<"<press any key to end>\n\n";
	_getch();
}
//--- End Error Handler --------------------------------------------------

    return 0;
}

	/*** PrintRawPacket **************************************************
	This function prints out the packet in Hex and Ascii.  The Ascii
	values are filtered to avoid printing ascii characters that are not
	friendly to the display.
	*/
	void PrintRawPacket( struct pcap_pkthdr* pkt_Header, unsigned char* pkt_Data )
	{
		char charData;
		std::vector< char > vctChars;
		std::vector< char >::iterator iter_vctChars;

		std::cout<<"--- Raw Packet Data ----------------------------------\n";

		for ( unsigned int i = 1; i < ( pkt_Header->caplen + 1 ) ; ++i )
		{
			//convert to hex, this portion of the packet
			for( int j = 1; j >= 0; --j )
			{
				std::cout << "0123456789ABCDEF"[(((int)pkt_Data[i-1] >> j*4) & 0xF)];
			}
			charData = (((int)pkt_Data[i-1] >> 1*4) & 0xF) * 16;
			charData += (((int)pkt_Data[i-1] >> 0*4) & 0xF);
			vctChars.push_back( charData );

			//every 12 blocks put a newline for organization
			if( i % 12 )
			{
				std::cout<<" ";
			}
			else
			{
				std::cout<<"  |  ";
				//print ascii equivalents
				for( iter_vctChars = vctChars.begin(); iter_vctChars != vctChars.end(); ++iter_vctChars )
				{
					if( ((*iter_vctChars) <= 126 && (*iter_vctChars) >= 32) || ((*iter_vctChars) <= 254 && (*iter_vctChars >= 128)) )
					{
						std::cout<<(*iter_vctChars);
					}
					else
					{
						std::cout<<" ";
					}
				}
				vctChars.clear();
				std::cout<<"\n";
			}
		}
	}


	/*** PrintIPPacket ***************************************************
	This function retrieves IP packet data and displays it
	*/
	void PrintIPPacket( const frame_IP& IPFrame, , const bool& bICMPInfo, const bool& bUDPInfo, const bool& bTCPInfo )
	{
		std::cout<<"\n--- IP Packet Data ------------------------------------\n";
		std::cout<<"Version: "<<IPFrame.Version()<<"\n"
				 <<"Header Length = "<<IPFrame.IHL()<<" bytes\n"
				 <<"Type of Service: 0x"<<IPFrame.TypeOfService()<<"\n";
		//Switch for Precedence portion of the packet
		std::cout<<"	Precedece: ";
		switch( IPFrame.Precedence() )
		{
			//Routine
			case( 0 ):
				std::cout<<"Routine";
			break;

			//Priority
			case( 1 ):
				std::cout<<"Priority";
			break;

			//Immediate
			case( 2 ):
				std::cout<<"Immediate";
			break;

			//Flash
			case( 3 ):
				std::cout<<"Flash";
			break;

			//Flash Override
			case( 4 ):
				std::cout<<"Flash Override";
			break;

			//CRITIC/ECP
			case( 5 ):
				std::cout<<"CRITIC/ECP";
			break;

			//Internetwork Control
			case( 6 ):
				std::cout<<"Internetwork Control";
			break;

			//Network Control
			case( 7 ):
				std::cout<<"Network Control";
			break;
		}
		std::cout<<"\n"
				 <<"	Delay: ";
		//Delay
		if( IPFrame.Delay() )
		{
			std::cout<<"Low";
		}
		else
		{
			std::cout<<"Normal";
		}
		std::cout<<"\n"
				 <<"	Throughput: ";
		//Throughput
		if( IPFrame.Delay() )
		{
			std::cout<<"High";
		}
		else
		{
			std::cout<<"Normal";
		}
		std::cout<<"\n"
				 <<"	Reliability: ";
		//Delay
		if( IPFrame.Delay() )
		{
			std::cout<<"High";
		}
		else
		{
			std::cout<<"Normal";
		}
		std::cout<<"\n"
				 <<"Total Length: "<<IPFrame.TotalLength()<<" bytes\n"
				 <<"Identification: "<<IPFrame.Identification()<<"\n"
				 <<"Flags: "<<(int)IPFrame.Flag01()<<" "<<(int)IPFrame.Flag02()<<"\n";
				if( IPFrame.Flag01() )
				{
					std::cout<<"	Do Not Fragment | ";
				}
				else
				{
					std::cout<<"	May Fragment | ";
				}
				if( IPFrame.Flag02() )
				{
					std::cout<<"More Fragments\n";
				}
				else
				{
					std::cout<<"Last Fragment\n";
				}
		std::cout<<"Fragment Offset: "<<IPFrame.FragmentOffset()<<" bytes\n"
				 <<"Time to Live: "<<IPFrame.TimeToLive()<<" seconds/hops\n"
				 <<"Protocol: "<<IPFrame.Protocol();
		switch( IPFrame.ProtocolNum() )
		{
			case( 1 ):
				std::cout<<"(ICMP)\n";
			break;

			case( 6 ):
				std::cout<<"(TCP)\n";
			break;

			case( 17 ):
				std::cout<<"(UDP)\n";
			break;
		}
		std::cout<<"Header Checksum: "<<IPFrame.HeaderChksum()<<"\n"
				 <<"Source Address: "<<IPFrame.SrcAddr()/*<<" AKA "<<IPFrame.SrcName()*/<<"\n"
				 <<"Destination Address: "<<IPFrame.DestAddr()/*<<" AKA "<<IPFrame.DestName()*/<<"\n\n";

		switch( IPFrame.ProtocolNum() )
		{
			case( 1 ):
				if( bICMPInfo )
				{
					PrintICMPPacket( IPFrame );
				}
			break;

			case( 6 ):
				if( bTCPInfo )
				{
					PrintTCPPacket( IPFrame );
				}
			break;

			case( 17 ):
				if( bUDPInfo )
				{
					PrintUDPPacket( IPFrame );
				}
			break;
		}
	}

	/*** PrintICMPPacket ***************************************************
	This function retrieves ICMP packet data and displays it
	*/
	void PrintICMPPacket( const frame_IP& IPFrame )
	{
		frame_ICMP ICMPFrame( IPFrame.DataPtr() );
		unsigned char* ptr_Data = ICMPFrame.Data();
		std::cout<<"--- ICMP Header --------------------------------------\n";
		std::cout<<"Type: "<<ICMPFrame.Type();

		switch( ICMPFrame.Type() )
		{
			case(0):
				std::cout<<"(Echo Reply)\n"
					<<"\tIdentifier: "<<TwoByteToDecimal( ptr_Data[0], ptr_Data[1] )<<"\n"
					<<"\tSequence Number: "<<TwoByteToDecimal( ptr_Data[2], ptr_Data[3] )<<"\n";
			break;

			case(3):
				std::cout<<"(Destination Unreachable)\n"
						 <<"\tNext-Hop MTU: "<<TwoByteToDecimal( ptr_Data[2], ptr_Data[3] )<<"\n";
			break;

			case(4):
				std::cout<<"(Source Quench)";
			break;

			case(5):
				std::cout<<"(Redirect)\n"
						 <<"\tIP: "<<ByteToDecimal( ptr_Data[0] )<<"."
								   <<ByteToDecimal( ptr_Data[1] )<<"."
								   <<ByteToDecimal( ptr_Data[2] )<<"."
								   <<ByteToDecimal( ptr_Data[3] )<<"\n";
			break;

			case(6):
				std::cout<<"(Alternate Host Address)";
			break;

			case(8):
				std::cout<<"(Echo)\n"
						 <<"\tIdentifier: "<<TwoByteToDecimal( ptr_Data[0], ptr_Data[1] )<<"\n"
						 <<"\tSequence Number: "<<TwoByteToDecimal( ptr_Data[2], ptr_Data[3] )<<"\n";
			break;

			case(9):
				std::cout<<"(Router Advertisement)\n"
						 <<"\tAdvertisement Count: "<<ByteToDecimal( ptr_Data[0] )<<"\n"
						 <<"\tAddress Entry Size: "<<ByteToDecimal( ptr_Data[1] )<<"\n"
						 <<"\tLifetime: "<<TwoByteToDecimal( ptr_Data[2], ptr_Data[3] )<<"\n";
			break;

			case(10):
				std::cout<<"(Router Solicitation)";
			break;

			case(11):
				std::cout<<"(Time Exceeded)";
			break;

			case(12):
				std::cout<<"(Parameter Problem)\n"
					<<"\tPointer: "<<ByteToDecimal( ptr_Data[0] )<<"\n";
			break;

			case(17):
				std::cout<<"(Address Mask Request)\n"
						 <<"\tIdentifier: "<<TwoByteToDecimal( ptr_Data[0], ptr_Data[1] )<<"\n"
						 <<"\tSequence Number: "<<TwoByteToDecimal( ptr_Data[2], ptr_Data[3] )<<"\n"
						 <<"\tAddress Mask: "<<ByteToDecimal( ptr_Data[4] )<<"."
											 <<ByteToDecimal( ptr_Data[5] )<<"."
											 <<ByteToDecimal( ptr_Data[6] )<<"."
											 <<ByteToDecimal( ptr_Data[7] )<<"\n";
			break;

			case(18):
				std::cout<<"(Address Mask Reply)\n"
						 <<"\tIdentifier: "<<TwoByteToDecimal( ptr_Data[0], ptr_Data[1] )<<"\n"
						 <<"\tSequence Number: "<<TwoByteToDecimal( ptr_Data[2], ptr_Data[3] )<<"\n"
						 <<"\tAddress Mask: "<<ByteToDecimal( ptr_Data[4] )<<"."
											 <<ByteToDecimal( ptr_Data[5] )<<"."
											 <<ByteToDecimal( ptr_Data[6] )<<"."
											 <<ByteToDecimal( ptr_Data[7] )<<"\n";
			break;

			case(30):
				std::cout<<"(Traceroute)\n"
						 <<"\tIdentifier: "<<TwoByteToDecimal( ptr_Data[0], ptr_Data[1] )<<"\n"
						 <<"Outbound Count Hop: "<<TwoByteToDecimal( ptr_Data[4], ptr_Data[5] )<<"\n"
						 <<"Return Hop Count: "<<TwoByteToDecimal( ptr_Data[6], ptr_Data[7] )<<"\n"
						 <<"Output Link Speed: "<<ToHex( ptr_Data[8] )<<ToHex( ptr_Data[9] )<<ToHex( ptr_Data[10] )<<ToHex( ptr_Data[11] )<<"\n"
						 <<"Output Link MTU: "<<ToHex( ptr_Data[12] )<<ToHex( ptr_Data[13] )<<ToHex( ptr_Data[14] )<<ToHex( ptr_Data[15] )<<"\n";
			break;
		}

		std::cout<<"\nCode: "<<ICMPFrame.Code()<<"\n"
				 <<"Checksum: "<<ICMPFrame.CheckSum()<<"\n";
	}

	/*** PrintUDPPacket ***************************************************
	This function retrieves UDP packet data and displays it
	Also prints the first 64 bytes of the UDP Packet Data
	*/
	void PrintUDPPacket( const frame_IP& IPFrame )
	{
		frame_UDP UDPFrame( IPFrame.DataPtr() );
		std::cout<<"--- UDP Header --------------------------------------\n";
		std::cout<<"Source Port: "<<UDPFrame.SourcePort()<<"\n"
				 <<"Destination Port: "<<UDPFrame.DestinationPort();

		switch( UDPFrame.DestinationPort() )
		{
			case( 80 ):
				std::cout<<"(HTTP)";
			break;

			case( 69 ):
				std::cout<<"(tftp)";
			break;

			case( 1025 ):
				std::cout<<"(network blackjack)";
			break;

			case( 7 ):
				std::cout<<"(echo)";
			break;

			case( 25 ):
				std::cout<<"(smtp)";
			break;

			case( 666 ):
				std::cout<<"(doom)";
			break;

			case( 137 ):
				std::cout<<"(Net Bios Name Service)";
			break;

			case( 2049 ):
				std::cout<<"(NFS)";
			break;

			case( 5190 ):
				std::cout<<"(AOL)";
			break;

			case( 5191 ):
				std::cout<<"(AOL1)";
			break;

			case( 5192 ):
				std::cout<<"(AOL2)";
			break;

			case( 5193 ):
				std::cout<<"(AOL3)";
			break;

			case( 22600 ):
				std::cout<<"(Quake Game Server)";
			break;

			case( 27500 ):
				std::cout<<"(Quake World)";
			break;

			case( 27015 ):
				std::cout<<"(Halflife)";
			break;

			case( 28910 ):
				std::cout<<"(Heretic2)";
			break;

			case( 27910 ):
				std::cout<<"(Quake 2)";
			break;

			case( 27960 ):
				std::cout<<"(Quake 3 Arena Server)";
			break;

			case( 31337 ):
				std::cout<<"(Backorifice)";
			break;
		}

		std::cout<<"\nLength: "<<UDPFrame.Length()<<"\n"
				 <<"Checksum: "<<UDPFrame.CheckSum()<<"\n";

		//Print first 64 bytes of Data in the Packet
		unsigned char* ptr_PktData = UDPFrame.Data();
		char charData;
		std::vector< char > vctChars;
		std::vector< char >::iterator iter_vctChars;

		std::cout<<"--- UDP Packet Data (64 bytes) ----------------------\n";

		for ( unsigned int i = 0; i < 64 ; ++i )
		{
			//convert to hex, this portion of the packet
			std::cout << ToHex( (*(ptr_PktData + i)) );

			charData = (((int)(*(ptr_PktData + i)) >> 1*4) & 0xF) * 16;
			charData += (((int)(*(ptr_PktData + i)) >> 0*4) & 0xF);
			vctChars.push_back( charData );

			//every 16 blocks put a newline for organization
			if( (i+1) % 16 )
			{
				std::cout<<" ";
			}
			else
			{
				std::cout<<"  |  ";
				//print ascii equivalents
				for( iter_vctChars = vctChars.begin(); iter_vctChars != vctChars.end(); ++iter_vctChars )
				{
					if( ((*iter_vctChars) <= 126 && (*iter_vctChars) >= 32) || ((*iter_vctChars) <= 254 && (*iter_vctChars >= 128)) )
					{
						std::cout<<(*iter_vctChars);
					}
					else
					{
						std::cout<<" ";
					}
				}
				vctChars.clear();
				std::cout<<"\n";
			}
		}
	}

	/*** PrintARPPacket ***************************************************
	This function retrieves ARP packet data and displays it
	*/
	void PrintARPPacket( const frame_ARP& ARPFrame )
	{
		std::cout<<"--- ARP Data -----------------------------------------\n";
		std::cout<<"Hardware Address: "<<ARPFrame.HWAddr()<<"\n"
				 <<"Protocol Address: "<<ARPFrame.ProtoAddr()<<"\n"
				 <<"H Addr Len: "<<ARPFrame.HAddrLen()<<" bytes\n"
				 <<"P Addr Len: "<<ARPFrame.PAddrLen()<<" bytes\n"
				 <<"Operation: ";
		switch( ARPFrame.Operation() )
		{
			case( 1 ):
				std::cout<<"1 (ARP Request)";
			break;
			case( 2 ):
				std::cout<<"2 (ARP Reply)";
			break;
			case( 3 ):
				std::cout<<"3 (RARP Request)";
			break;
			case( 4 ):
				std::cout<<"4 (RARP Reply)";
			break;
		}
		std::cout<<"Hardware Address of Sender: "<<ARPFrame.HAddrSender()<<"\n"
				 <<"Protocol Address of Sender: "<<ARPFrame.PAddrSender()<<"\n"
				 <<"Hardware Address of Target: "<<ARPFrame.HAddrTarget()<<"\n"
				 <<"Protocol Address of Target: "<<ARPFrame.PAddrTarget()<<"\n";
	}

	/*** PrintTCPPacket ***************************************************
	This function retrieves TCP packet data and displays it
	Also prints the first 64 bytes of the TCP Packet Data
	*/
	void PrintTCPPacket( const frame_IP& IPFrame )
	{
		frame_TCP TCPFrame( IPFrame.DataPtr() );
		std::cout<<"--- TCP Header --------------------------------------\n";
		std::cout<<"Source Port: "<<TCPFrame.SourcePort()<<"(";
		PrintTCPProtocol( TCPFrame.SourcePort() );
		std::cout<<")\nDestination Port: "<<TCPFrame.DestinationPort()<<"(";
		PrintTCPProtocol( TCPFrame.DestinationPort() );
		std::cout<<")\nSequence Number: "<<TCPFrame.SequenceNumber()<<"\n"
				 <<"Acknowledgement Number: "<<TCPFrame.AckNumber()<<"\n"
				 <<"Data Offset: "<<TCPFrame.DataOffset()<<"\n"
				 <<"Flags\n";

		std::cout<<"\tE = ";
		if( TCPFrame.E_ECN() )
		{
			std::cout<<"true\n";
		}
		else
		{
			std::cout<<"false\n";
		}
		std::cout<<"\tC = ";
		if( TCPFrame.C_ECN() )
		{
			std::cout<<"true\n";
		}
		else
		{
			std::cout<<"false\n";
		}
		std::cout<<"\tN = ";
		if( TCPFrame.N_ECN() )
		{
			std::cout<<"true\n\n";
		}
		else
		{
			std::cout<<"false\n\n";
		}

		std::cout<<"\tUrgent pointer valid = "<<TCPFrame.CB0()<<"\n"
				 <<"\tAcknowledgment number valid = "<<TCPFrame.CB1()<<"\n"
				 <<"\tPush = "<<TCPFrame.CB2()<<"\n"
				 <<"\tReset connection = "<<TCPFrame.CB3()<<"\n"
				 <<"\tSynchronize sequence numbers = "<<TCPFrame.CB4()<<"\n"
				 <<"\tEnd of data = "<<TCPFrame.CB5()<<"\n\n"
				 <<"Window = "<<TCPFrame.Window()<<"\n"
				 <<"Checksum = "<<TCPFrame.CheckSum()<<"\n"
				 <<"Urgent Pointer = "<<TCPFrame.UrgentPtr()<<"\n";

		//Print first 64 bytes of Data in the Packet
		unsigned char* ptr_PktData = TCPFrame.Data();
		char charData;
		std::vector< char > vctChars;
		std::vector< char >::iterator iter_vctChars;

		std::cout<<"--- TCP Packet Data (64 bytes) ----------------------\n";

		for ( unsigned int i = 0; i < 64 ; ++i )
		{
			//convert to hex, this portion of the packet
			std::cout << ToHex( (*(ptr_PktData + i)) );

			charData = (((int)(*(ptr_PktData + i)) >> 1*4) & 0xF) * 16;
			charData += (((int)(*(ptr_PktData + i)) >> 0*4) & 0xF);
			vctChars.push_back( charData );

			//every 16 blocks put a newline for organization
			if( (i+1) % 16 )
			{
				std::cout<<" ";
			}
			else
			{
				std::cout<<"  |  ";
				//print ascii equivalents
				for( iter_vctChars = vctChars.begin(); iter_vctChars != vctChars.end(); ++iter_vctChars )
				{
					if( ((*iter_vctChars) <= 126 && (*iter_vctChars) >= 32) || ((*iter_vctChars) <= 254 && (*iter_vctChars >= 128)) )
					{
						std::cout<<(*iter_vctChars);
					}
					else
					{
						std::cout<<" ";
					}
				}
				vctChars.clear();
				std::cout<<"\n";
			}
		}
	}

	/*** PrintTCPProtocol ***************************************************
	This function prints the TCP Protocol provided.
	*/
	void PrintTCPProtocol( const int& iProto )
	{
		switch( iProto )
		{
			case( 7 ):
				std::cout<<"Echo";
			break;
			case( 13 ):
				std::cout<<"Daytime";
			break;
			case( 17 ):
				std::cout<<"Quote";
			break;
			case( 20 ):
				std::cout<<"FTP Data";
			break;
			case( 21 ):
				std::cout<<"FTP Control";
			break;
			case( 23 ):
				std::cout<<"Telnet";
			break;
			case( 25 ):
				std::cout<<"SMTP";
			break;
			case( 37 ):
				std::cout<<"Time";
			break;
			case( 42 ):
				std::cout<<"Internet Name Server";
			break;
			case( 50 ):
				std::cout<<"RMCP";
			break;
			case( 53 ):
				std::cout<<"DNS";
			break;
			case( 67 ):
				std::cout<<"BOOTP Server";
			break;
			case( 68 ):
				std::cout<<"BOOTP Client";
			break;
			case( 69 ):
				std::cout<<"TFTP";
			break;
			case( 80 ):
				std::cout<<"HTTP";
			break;
			case( 109 ):
				std::cout<<"POP v2";
			break;
			case( 110 ):
				std::cout<<"POP v3";
			break;
			case( 161 ):
				std::cout<<"SNMP";
			break;
			case( 162 ):
				std::cout<<"SNMP Traps";
			break;
			case( 179 ):
				std::cout<<"BGP";
			break;
			default:
				std::cout<<"unknown";
			break;
		}
	}