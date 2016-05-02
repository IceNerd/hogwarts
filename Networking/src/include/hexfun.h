#ifndef HEXFUN_H
#define HEXFUN_H

	#include <string>

	const std::string HexAlphabet( "0123456789ABCDEF" );

	std::string ToHex( unsigned char );
	int ByteToDecimal( unsigned char );
	int TwoByteToDecimal( unsigned char, unsigned char );

#endif