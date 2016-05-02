#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "STable.h"

std::string CreateStringFromFile( const std::string& );
std::vector<std::string> Tokenize( const std::string&, const std::string& = " " );
void Analyze( std::vector<std::string>& );

int main()
{
	std::vector<std::string> vctTokens;
    std::string strAnalyze( CreateStringFromFile( "tester.txt" ) );

	vctTokens = Tokenize( strAnalyze, ":'\"<>+%&=.-*/~(){}[];, " );

	Analyze( vctTokens );

	_getch();
}

std::string CreateStringFromFile( const std::string& strFile )
{
	std::ifstream inFile( strFile.c_str() );
	char strLine;
	std::string strReturn;

	if( inFile.is_open() )
	{
		while( !inFile.eof() )
		{
			inFile.get( strLine );
			//ignore tabs and linebreaks
			if( (strLine != '\n') && (strLine != '\t') && (!inFile.eof()) )
			{
				strReturn += strLine;
			}
		}
	}

	inFile.close();
	return strReturn;
}

std::vector<std::string> Tokenize( const std::string& strTok, const std::string& strDelim )
{
	std::vector<std::string> vctReturn;
    std::string::size_type lastPos = strTok.find_first_not_of( strDelim, 0 );
    std::string::size_type Pos = strTok.find_first_of( strDelim, lastPos );

	vctReturn.clear();

	while( strTok[lastPos + 1] ) 
    {
		if( lastPos == 0 )
		{
			vctReturn.push_back( strTok.substr( lastPos, Pos - lastPos ) );
		}
		else
		{
			if( strTok.substr( lastPos, 1 ) != " " )
			{
				vctReturn.push_back( strTok.substr( lastPos, 1 ) );
			}
			if( Pos - lastPos != 1 )
			{
				vctReturn.push_back( strTok.substr( lastPos + 1, (Pos - lastPos) - 1 ) );
			}
		}

        lastPos = strTok.find_first_of( strDelim, Pos );
        Pos = strTok.find_first_of( strDelim, lastPos + 1 );
    }
	vctReturn.push_back( strTok.substr( lastPos, 1 ) );

	return vctReturn;
}

void Analyze( std::vector<std::string>& vctTokens )
{
	if( !vctTokens.empty() )
	{

		STable SymbolTable( "clegal.txt" );
		char chBuffer[100];

		//--- propogate our Keywords( 1 )
		std::ifstream inKeyFile( "keywords.txt" );
		if( inKeyFile.is_open() )
		{
			while( !inKeyFile.eof() )
			{
				inKeyFile.getline( chBuffer, 100 );
				SymbolTable.Add( chBuffer, 1 );
			}
		}
		inKeyFile.close();
		//---

		//--- propogate our Operators( 2 )
		std::ifstream inOpFile( "operators.txt" );
		if( inOpFile.is_open() )
		{
			while( !inOpFile.eof() )
			{
				inOpFile.getline( chBuffer, 100 );
				SymbolTable.Add( chBuffer, 2 );
			}
		}
		inOpFile.close();
		//---

		//--- propogate our Symbols( 3 )
		std::ifstream inSymFile( "symbols.txt" );
		if( inSymFile.is_open() )
		{
			while( !inSymFile.eof() )
			{
				inSymFile.getline( chBuffer, 100 );
				SymbolTable.Add( chBuffer, 3 );
			}
		}
		inSymFile.close();
		//---


		for( std::vector<std::string>::iterator iter_i = vctTokens.begin(); iter_i != vctTokens.end(); ++iter_i )
		{
			std::cout.width(13);
			switch( SymbolTable.Find( (*iter_i) ) )
			{
				case 0:
					std::cout<<"IDENTIFIER: ";
				break;

				case 1:
					std::cout<<"KEYWORD: ";
				break;

				case 2:
					std::cout<<"OPERATOR: ";
				break;

				case 3:
					std::cout<<"SYMBOL: ";
				break;

				default:
					std::cout<<"UNKNOWN: ";
				break;
			}
			std::cout<<(*iter_i)<<"\n";
		}
	}
}