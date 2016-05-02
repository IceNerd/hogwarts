#ifndef SHROOMDB_H
#define SHROOMDB_H

#include <vector>

#include "odbc.h"

class ShroomDB : public ODBC
{
public:
	ShroomDB( const char* );
	~ShroomDB();

	std::vector<int> DisplayShrooms();
	int DeleteShroom( const int& );
	int UpdateShroomName( const int&, const char* );
	int UpdateShroomDescription(const int&, const char* );
	int UpdateShroomSeason(const int&, const char* );

	std::vector<int> GetTransIDs();
	std::vector<int> DisplayTrans();

	int DisplayTransaction( const int& );

	std::vector<int> DisplayStations();
	std::vector<int> DisplayBuyers();
	std::vector<int> DisplayPickers();
	std::vector<int> DisplayShroomGrades();
	std::vector<int> DisplayAddresses();
};

#endif