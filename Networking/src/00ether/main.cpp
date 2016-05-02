/*************************************************************************
Alberto Martinez
04/10/2005

main.cpp

Rdy Set Go
**************************************************************************/
#include <iostream>
#include <conio.h>//for getch()
#include <string>

#include <pcap.h>

#include "exception.h"
#include "netpacket.h"

#define LINE_LEN 16

void PrintRawPacket( struct pcap_pkthdr*, u_char* );
void PrintAddress( unsigned char* );

int main( int argc, char **argv )
{
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
							PCAP_OPENFLAG_PROMISCUOUS,	//flags
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
							PCAP_OPENFLAG_PROMISCUOUS,	//flags
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
		if( 1 )
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

			//--- Type handling ------------------------------------------
			switch( Traffic.LenType )
			{
				case( 2048 )://IP
				break;

				case( 2054 )://ARP
				break;

				default://UnhandledTypes
				break;
			}
			std::cout<<"\n\n";

			PrintRawPacket( header, pkt_data );
			std::cout<<"\n"<<std::endl;
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

//--- Prints the packet as raw hex data -----
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