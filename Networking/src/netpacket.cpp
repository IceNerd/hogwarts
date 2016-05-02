/*************************************************************************
Alberto Martinez
04/10/2005

netpacket.cpp

**************************************************************************/
#include "netpacket.h"


//--- Constructor --------------------------------------------------------
	NetPacket::NetPacket( const std::string& strTypeFile )
	:Size( &iSize ), LenType( &iLenType ), Packet( &ptr_Packet )
	{
		PropogateTypes( strTypeFile );
	}

//--- Deconstructor ------------------------------------------------------
	NetPacket::~NetPacket()
	{
		//delete the strings we made from the type definition file
		while( !lstTypeDesc.empty() )
		{
			delete lstTypeDesc.front();
			lstTypeDesc.pop_front();
		}
	}

//--- Input --------------------------------------------------------------
	/*** NewPacket *******************************************************
	This function is where the class is notified that there is a new
	packet.  EFrame is then layed on top of the packet to handle parsing
	the ethernet header.
	*/
	void NetPacket::NewPacket( struct pcap_pkthdr* pkt_Header, unsigned char* pkt_Data )
	{
		ptr_Packet = pkt_Data;
		iSize = pkt_Header->caplen;

		/*****************************************************************
		** Do not delete EFrame because it references data contained by **
		**   parent class. ***********************************************
		*****************************************************************/

		//--- Ethernet Frame
		EFrame = (frame_EtherNet*)pkt_Data;

		//--- Len/Type
		iLenType = (((int)EFrame->LenType[0] >> 4) & 0xF) * 4096;
		iLenType += (((int)EFrame->LenType[0]) & 0xF) * 256;
		iLenType += (((int)EFrame->LenType[1] >> 4) & 0xF) * 16;
		iLenType += (((int)EFrame->LenType[1]) & 0xF);
	}

//--- Output -------------------------------------------------------------

	/*** GetPacket *******************************************************
	Simple Getter just in case we need to get the packet ptr back.
	*/
	unsigned char* NetPacket::GetPacket()
	{
		return ptr_Packet;
	}

	/*** DestAddr ********************************************************
	Get the Destination Address from the ethernet header.
	*/
	std::string NetPacket::DestAddr()
	{
		std::string strBuff;

		for( int i = 0; i < 6; ++i )
		{
			strBuff += ToHex( EFrame->DestAddr[i] );
			if( i != 5 )
			{
				strBuff += '-';
			}
		}
		return strBuff;
	}

	/*** SrcAddr *********************************************************
	Get the source address from the ethernet header.
	*/
	std::string NetPacket::SrcAddr()
	{
		std::string strBuff;

		for( int i = 0; i < 6; ++i )
		{
			strBuff += ToHex( EFrame->SrcAddr[i] );
			if( i != 5 )
			{
				strBuff += '-';
			}
		}
		return strBuff;
	}

	/*** FindTypeDesc ****************************************************
	Gets the Type from the ethernet header
	*/
	std::string* NetPacket::FindTypeDesc( const int& iType )
	{
		std::string* ptr_Return(0);
		std::map< int, std::string* >::const_iterator iter_i;

		iter_i = mapTypes.find( iType );
		if( iter_i != mapTypes.end() )
		{
			ptr_Return = iter_i->second;
		}

		return ptr_Return;
	}

	/*** LenTypeHex ******************************************************
	Gets the Length/Type from the ethernet header
	*/
	std::string NetPacket::LenTypeHex()
	{
		std::string strBuff;

		for( int i = 0; i < 2; ++i )
		{
			strBuff += ToHex( EFrame->LenType[i] );
		}

		return strBuff;
	}

//--- Private ------------------------------------------------------------

//--- Protected ----------------------------------------------------------
	/*** PropogateTypes **************************************************
	This function retreves a list of Types and their associated decimal
	designation.   hrm, did not know how big I made this function
	*/
	void NetPacket::PropogateTypes( const std::string& inFile )
	{
		std::ifstream inTypeFile( inFile.c_str() );
		char chFromFile;
		unsigned short u_sWhere(0);
		std::string strNum1;
		int iNum1;
		std::string strNum2;
		int iNum2;
		std::string strBuffDesc;
		std::string* strTypeDesc;

		if( inTypeFile.is_open() )
		{
			while( !inTypeFile.eof() )
			{
				chFromFile = inTypeFile.get();
				switch( chFromFile )
				{
					case( '\n' ):
						//Convert number/numbers to dec |  64 - 32 - 16 - 1
						for( int i = 0; i < 4; ++i )
						{
							if( strNum1[i] >= 48 && strNum1[i] <= 57 )
							{
								//0-9
								strNum1[i] -= 48;

							}
							else
							{
								//A-F
								strNum1[i] -= 55;
							}
						}
						iNum1 = ((int)strNum1[0]) * 4069;
						iNum1 += ((int)strNum1[1]) * 256;
						iNum1 += ((int)strNum1[2]) * 16;
						iNum1 += ((int)strNum1[3]);

						if( !strNum2.empty() )
						{
							for( int i = 0; i < 4; ++i )
							{
								if( strNum2[i] >= 48 && strNum2[i] <= 57 )
								{
									//0-9
									strNum2[i] -= 48;

								}
								else
								{
									//A-F
									strNum2[i] -= 55;
								}
							}
							iNum2 = ((int)strNum2[0]) * 4096;
							iNum2 += ((int)strNum2[1]) * 256;
							iNum2 += ((int)strNum2[2]) * 16;
							iNum2 += ((int)strNum2[3]);
						}

						//Add string to list
						strTypeDesc = new std::string( strBuffDesc );
						lstTypeDesc.push_back( strTypeDesc );
						if( iNum2 && iNum2 > iNum1 )
						{
							//if two numbers, then do range
							for( int i = iNum1; i <= iNum2; ++i )
							{
								mapTypes.insert( std::pair< int, std::string* >( i, strTypeDesc ) );
							}
						}
						else
						{
							mapTypes.insert( std::pair< int, std::string* >( iNum1, strTypeDesc ) );
						}

						strNum1.clear();
						strNum2.clear();
						strBuffDesc.clear();
						strTypeDesc = 0;
						u_sWhere = 0;
						iNum1 = 0;
						iNum2 = 0;
					break;

					case( '|' ):
						u_sWhere++;
					break;

					default:
						switch( u_sWhere )
						{
							case( 0 ):
								strNum1 += chFromFile;
							break;

							case( 1 ):
								if( (chFromFile >= 48 && chFromFile <= 57) || (chFromFile >= 65 && chFromFile <= 70) )
								{
									strNum2 += chFromFile;
								}
								else
								{
									strNum2 += chFromFile;
									strBuffDesc = strNum2;
									strNum2.clear();
									u_sWhere++;
								}
							break;

							case( 2 ):
								strBuffDesc += chFromFile;
							break;

							default:
								throw Exception< std::string >( "Error reading type file" );
							break;
						}
					break;
				}
			}
		}
		else
		{
			throw Exception< std::string >( "Error opening file for types" );
		}
		inTypeFile.close();
	}