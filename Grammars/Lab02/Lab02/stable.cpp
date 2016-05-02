#include "stable.h"

STable::STable( const std::string& fileFSM )
:CheckCLegal( fileFSM )
{
}

STable::~STable()
{
}

void STable::Add( const std::string& strSymbol, const int& iType )
{
	std::pair<std::string, int> toAdd( strSymbol, iType );
	this->mapSymbol.insert( toAdd );
}

int STable::Find( const std::string& strSymbol )
{
	int iReturn(-1);
	std::map< std::string, int>::const_iterator iter_i;

	iter_i = this->mapSymbol.find( strSymbol );
	if( iter_i != this->mapSymbol.end() )
	{
		iReturn = iter_i->second;
	}
	else
	{
		if( this->CheckCLegal.CheckInput( strSymbol ) )
		{
			iReturn = 0;
		}
	}

	return iReturn;
}