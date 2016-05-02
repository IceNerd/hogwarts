#ifndef STABLE_H
#define STABLE_H

#include <map>
#include <string>
#include "statetree.h"

class STable
{
	public:
		STable( const std::string& );
		~STable();
		void Add( const std::string&, const int& );
		int Find( const std::string& );

	private:
		std::map<std::string, int> mapSymbol;
		StateTree CheckCLegal;
};

#endif