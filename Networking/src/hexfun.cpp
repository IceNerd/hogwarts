#include "hexfun.h"

//ToHex
std::string ToHex( unsigned char ConvertMe )
{
	std::string strBuff;

	strBuff = HexAlphabet[(((int)ConvertMe >> 4) & 0xF)];
	strBuff += HexAlphabet[(((int)ConvertMe) & 0xF)];

	return strBuff;
}

int TwoByteToDecimal( unsigned char Byte1, unsigned char Byte2 )
{
	int iReturn( 0 );

	iReturn = (((int)Byte1 >> 4) & 0xF) * 4096;
	iReturn += (((int)Byte1) & 0xF) * 256;
	iReturn += (((int)Byte2 >> 4) & 0xF) * 16;
	iReturn += (((int)Byte2) & 0xF);

	return iReturn;
}

int ByteToDecimal( unsigned char ConvertMe )
{
	int iReturn( 0 );

	iReturn = (((int)ConvertMe >> 4) & 0xF) * 16;
	iReturn += (((int)ConvertMe) & 0xF);

	return iReturn;
}