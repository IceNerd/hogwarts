#include "shroomdb.h"

ShroomDB::ShroomDB( const char* DSN )
:ODBC( DSN )
{
}

ShroomDB::~ShroomDB()
{
}

std::vector<int> ShroomDB::DisplayShrooms()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		SDWORD qGeneral;
		int iShroomID;
		char cShroomName[100];
		char cShroomDescription[100];
		SDWORD qDesc;
		DATE_STRUCT dsShroomSeason;
		SDWORD qSeason;

		if( ExecSQL( "select * from mushroom" ) )
		{
			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iShroomID, 100, &qGeneral);
			SQLBindCol(mhStmt, 2, SQL_C_CHAR, cShroomName, 100, &qGeneral);
			SQLBindCol(mhStmt, 3, SQL_C_CHAR, cShroomDescription, 100, &qDesc);
			SQLBindCol(mhStmt, 4, SQL_C_DATE, &dsShroomSeason, 100, &qSeason);

			int i( 1 );
			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iShroomID );
				printf( "%i ------ ShroomID: %d\nName: %s\nDescription: ", i, iShroomID, cShroomName );
				if( qDesc == SQL_NULL_DATA )
				{
					printf("NULL\n");
				}
				else
				{
					printf( "%s\n", cShroomDescription );
				}

				printf( "Season: " );
				if( qSeason == SQL_NULL_DATA )
				{
					printf("NULL\n\n");
				}
				else
				{
					printf("%i-%i-%i\n\n", dsShroomSeason.month, dsShroomSeason.day, dsShroomSeason.year );
				}
				++i;
			}
		}
	}

	return vReturn;
}

int ShroomDB::DeleteShroom( const int& iShroomID )
{
	int iReturn( 0 );
	char cQuery[75];

	sprintf_s( cQuery, "delete from mushroom where shroomid = %i", iShroomID );
	if( ExecSQL( cQuery ) == 0 )
	{
		iReturn = -1;
	}

	return iReturn;
}

int ShroomDB::UpdateShroomName( const int& iShroomID, const char* cName )
{
	int iReturn( 0 );
	char cQuery[150];

	sprintf_s( cQuery, "update mushroom set shroomname = '%s' where shroomid = %i", cName, iShroomID );

	return ExecSQL( cQuery );
}

int ShroomDB::UpdateShroomDescription( const int& iShroomID, const char*cDesc  )
{
	int iReturn( 0 );
	char cQuery[150];

	sprintf_s( cQuery, "update mushroom set shroomdescription = %s where shroomid = %i", cDesc, iShroomID );

	return ExecSQL( cQuery );
}

int ShroomDB::UpdateShroomSeason( const int& iShroomID, const char* cDate )
{
	int iReturn( 0 );
	char cQuery[150];

	sprintf_s( cQuery, "update mushroom set season = %s where shroomid = %i", cDate, iShroomID );

	return ExecSQL( cQuery );
}

std::vector<int> ShroomDB::GetTransIDs()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		if( ExecSQL( "select transid from trans" ) )
		{
			SDWORD qGeneral;
			int iTransID;
			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iTransID, 100, &qGeneral);

			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iTransID );
			}
		}
	}

	return vReturn;
}

std::vector<int> ShroomDB::DisplayTrans()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		if( ExecSQL( "select * from trans" ) )
		{
			SDWORD qGeneral;
			int iTransID;
			int iTransNumber;
			DATE_STRUCT dsTransDate;

			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iTransID, 100, &qGeneral);
			SQLBindCol(mhStmt, 5, SQL_C_LONG, &iTransNumber, 100, &qGeneral);
			SQLBindCol(mhStmt, 6, SQL_C_DATE, &dsTransDate, 100, &qGeneral);

			int i( 1 );
			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iTransID );
				printf( "%i ------ TransID: %i\nNumber: %i\nDate: %i-%i-%i\n\n", i, iTransID, iTransNumber, dsTransDate.month, dsTransDate.day, dsTransDate.year );

				++i;
			}
		}
	}

	return vReturn;
}

int ShroomDB::DisplayTransaction( const int& iTransNumber )
{
	int iReturn( 0 );

	if( mbConnected )
	{
		char cQuery[500];

		sprintf_s( cQuery, "select transid, stationid, buyerid, pickerid, transdate from trans where transnumber = %i", iTransNumber );
		if( ExecSQL( cQuery ) )
		{iReturn++;
			SDWORD qGeneral;
			int iTransID(0);
			int iStationID(0);
			int iBuyerID(0);
			int iPickerID(0);
			DATE_STRUCT dsTransDate;

			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iTransID, 100, &qGeneral);
			SQLBindCol(mhStmt, 2, SQL_C_LONG, &iStationID, 100, &qGeneral);
			SQLBindCol(mhStmt, 3, SQL_C_LONG, &iBuyerID, 100, &qGeneral);
			SQLBindCol(mhStmt, 4, SQL_C_LONG, &iPickerID, 100, &qGeneral);
			SQLBindCol(mhStmt, 5, SQL_C_DATE, &dsTransDate, 100, &qGeneral);

			while( !SQLFetch( mhStmt ) );

			printf( "Transaction: %i, %i-%i-%i\n", iTransNumber, dsTransDate.day, dsTransDate.month, dsTransDate.year );

			//station
			char cStation[100];
			sprintf_s( cQuery, "select town from station where stationid = %i", iStationID );
			if( ExecSQL( cQuery ) )
			{
				SQLBindCol( mhStmt, 1, SQL_C_CHAR, cStation, 100, &qGeneral );
				while( !SQLFetch( mhStmt ) );
				printf( "Station: %s\n", cStation );
			}

			//buyer
			char cBuyerFName[100];
			char cBuyerLName[100];
			sprintf_s( cQuery, "select firstname, lastname from buyer where buyerid = %i", iBuyerID );
			if( ExecSQL( cQuery ) )
			{
				SQLBindCol( mhStmt, 1, SQL_C_CHAR, cBuyerFName, 100, &qGeneral );
				SQLBindCol( mhStmt, 2, SQL_C_CHAR, cBuyerLName, 100, &qGeneral );

				while( !SQLFetch( mhStmt ) );

				printf( "Employee: %s %s\n", cBuyerFName, cBuyerLName );
			}

			//picker
			char cPickerFName[100];
			char cPickerLName[100];
			char cPickerLicense[100];
			sprintf_s( cQuery, "select firstname, lastname, licensenumber from picker where pickerid = %i", iPickerID );
			if( ExecSQL( cQuery ) )
			{
				SQLBindCol( mhStmt, 1, SQL_C_CHAR, cPickerFName, 100, &qGeneral );
				SQLBindCol( mhStmt, 2, SQL_C_CHAR, cPickerLName, 100, &qGeneral );
				SQLBindCol( mhStmt, 3, SQL_C_CHAR, cPickerLicense, 100, &qGeneral );

				while( !SQLFetch( mhStmt ) );

				printf( "Picker: %s %s\n--- License: %s\n", cPickerFName, cPickerLName, cPickerLicense );
			}
			
			//mushrooms
			sprintf_s( cQuery, "select shroomname, gradename, qty, price, bonus from mushroom, grade, trans_item where trans_item.transid = %i and grade.gradeid = trans_item.gradeid and mushroom.shroomid = grade.shroomid", iTransID );
			if( ExecSQL( cQuery ) )
			{
				char cShroomName[100];
				char cGradeName[100];
				float fQty;
				float fPrice;
				float fBonus;
				float fTotal(0.0);

				SQLBindCol( mhStmt, 1, SQL_C_CHAR, cShroomName, 100, &qGeneral );
				SQLBindCol( mhStmt, 2, SQL_C_CHAR, cGradeName, 100, &qGeneral );
				SQLBindCol( mhStmt, 3, SQL_C_FLOAT, &fQty, 100, &qGeneral );
				SQLBindCol( mhStmt, 4, SQL_C_FLOAT, &fPrice, 100, &qGeneral );
				SQLBindCol( mhStmt, 5, SQL_C_FLOAT, &fBonus, 100, &qGeneral );

				printf("____Transaction Items__________________________\n");
				while( !SQLFetch( mhStmt ) )
				{
					printf( "%s - %s - %4.2flbs @ %4.2f", cShroomName, cGradeName, fQty, fPrice );
					if( fBonus > 0.00 )
					{
						printf( "(%4.2f Bonus) -- Total: %8.2f\n", fBonus, (fQty * fPrice) );
						fTotal += (fQty * fPrice);
					}
					else
					{
						printf( " -- Total: %8.2f\n", (fQty * fPrice) );
						fTotal += (fQty * fPrice);
					}
				}
				printf("------  Total: %8.2f\n", fTotal);
			}
			printf("\n");

		}
	}

	return iReturn;
}

std::vector<int> ShroomDB::DisplayStations()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		SDWORD qGeneral;
		int iStationID;
		char cTown[100];
		char cLocationDesc[100];
		SDWORD qLocationDesc;
		char cActive[100];
		char cPhone[100];
		SDWORD qPhone;

		if( ExecSQL( "select * from station" ) )
		{
			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iStationID, 100, &qGeneral);
			SQLBindCol(mhStmt, 2, SQL_C_CHAR, cTown, 100, &qGeneral);
			SQLBindCol(mhStmt, 3, SQL_C_CHAR, cLocationDesc, 100, &qLocationDesc);
			SQLBindCol(mhStmt, 4, SQL_C_CHAR, cActive, 100, &qGeneral);
			SQLBindCol(mhStmt, 5, SQL_C_CHAR, cPhone, 100, &qPhone);

			int i( 1 );
			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iStationID );
				printf( "%i ------ StationID: %d\nTown: %s\nDescription: ", i, iStationID, cTown );
				if( qLocationDesc == SQL_NULL_DATA )
				{
					printf("NULL\n");
				}
				else
				{
					printf( "%s\n", cLocationDesc );
				}

				printf( "Active: %s\nPhone: ", cActive );
				if( qPhone == SQL_NULL_DATA )
				{
					printf("NULL\n\n");
				}
				else
				{
					printf("%s\n\n", cPhone );
				}
				++i;
			}
		}
	}

	return vReturn;
}

std::vector<int> ShroomDB::DisplayBuyers()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		SDWORD qGeneral;
		int iBuyerID;
		int iAddressID;
		SDWORD qAddress;
		char cFirstName[100];
		char cLastName[100];
		char cPhone[100];
		SDWORD qPhone;

		if( ExecSQL( "select * from buyer" ) )
		{
			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iBuyerID, 100, &qGeneral);
			SQLBindCol(mhStmt, 2, SQL_C_LONG, &iAddressID, 100, &qAddress);
			SQLBindCol(mhStmt, 3, SQL_C_CHAR, cFirstName, 100, &qGeneral);
			SQLBindCol(mhStmt, 4, SQL_C_CHAR, cLastName, 100, &qGeneral);
			SQLBindCol(mhStmt, 5, SQL_C_CHAR, cPhone, 100, &qPhone);

			int i( 1 );
			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iBuyerID );
				printf( "%i ------ BuyerID: %d\nFirst Name: %s\nLast Name: %s\nPhone: ", i, iBuyerID, cFirstName, cLastName );
				if( qPhone == SQL_NULL_DATA )
				{
					printf( "NULL\n" );
				}
				else
				{
					printf( "%s\n", cPhone );
				}
				printf("Address: ");
				if( qAddress == SQL_NULL_DATA )
				{
					printf( "NULL\n\n" );
				}
				else
				{
					printf( "%i\n\n", iAddressID );
				}
				++i;

			}
		}
	}

	return vReturn;
}

std::vector<int> ShroomDB::DisplayPickers()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		SDWORD qGeneral;
		int iPickerID;
		int iAddressID;
		SDWORD qAddress;
		char cFirstName[100];
		char cLastName[100];
		char cLicense[100];
		char cPhone[100];
		SDWORD qPhone;

		if( ExecSQL( "select * from picker" ) )
		{
			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iPickerID, 100, &qGeneral);
			SQLBindCol(mhStmt, 2, SQL_C_LONG, &iAddressID, 100, &qAddress);
			SQLBindCol(mhStmt, 3, SQL_C_CHAR, cFirstName, 100, &qGeneral);
			SQLBindCol(mhStmt, 4, SQL_C_CHAR, cLastName, 100, &qGeneral);
			SQLBindCol(mhStmt, 5, SQL_C_CHAR, cLicense, 100, &qGeneral);
			SQLBindCol(mhStmt, 6, SQL_C_CHAR, cPhone, 100, &qPhone);

			int i( 1 );
			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iPickerID );
				printf( "%i ------ PickerID: %d\nFirst Name: %s\nLast Name: %s\nLicense: %s\nPhone: ", i, iPickerID, cFirstName, cLastName, cLicense );
				if( qPhone == SQL_NULL_DATA )
				{
					printf( "NULL\n" );
				}
				else
				{
					printf( "%s\n", cPhone );
				}
				printf("Address: ");
				if( qAddress == SQL_NULL_DATA )
				{
					printf( "NULL\n\n" );
				}
				else
				{
					printf( "%i\n\n", iAddressID );
				}
				++i;

			}
		}
	}

	return vReturn;
}

std::vector<int> ShroomDB::DisplayShroomGrades()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		if( ExecSQL( "select grade.gradeid, mushroom.shroomname, grade.gradename from grade, mushroom where grade.shroomid = mushroom.shroomid" ) )
		{
			SDWORD qGeneral;
			int iGradeID;
			char cShroomName[100];
			char cGradeName[100];

			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iGradeID, 100, &qGeneral);
			SQLBindCol(mhStmt, 2, SQL_C_CHAR, cShroomName, 100, &qGeneral);
			SQLBindCol(mhStmt, 3, SQL_C_CHAR, cGradeName, 100, &qGeneral);

			int i( 1 );
			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iGradeID );
				printf( "%i ------ GradeID: %i\nShroom: %s\nGrade: %s\n\n", i, iGradeID, cShroomName, cGradeName );

				++i;
			}
		}
	}

	return vReturn;
}

std::vector<int> ShroomDB::DisplayAddresses()
{
	std::vector<int> vReturn;

	if( mbConnected )
	{
		if( ExecSQL( "select addressid, address1, address2, city, state, zip from address" ) )
		{
			SDWORD qGeneral;
			SDWORD qAddress2;
			int iAddressID;
			char cAddress1[100];
			char cAddress2[100];
			char cCity[100];
			char cState[100];
			char cZip[100];

			SQLBindCol(mhStmt, 1, SQL_C_LONG, &iAddressID, 100, &qGeneral);
			SQLBindCol(mhStmt, 2, SQL_C_CHAR, cAddress1, 100, &qGeneral);
			SQLBindCol(mhStmt, 3, SQL_C_CHAR, cAddress2, 100, &qAddress2);
			SQLBindCol(mhStmt, 4, SQL_C_CHAR, cCity, 100, &qGeneral);
			SQLBindCol(mhStmt, 5, SQL_C_CHAR, cState, 100, &qGeneral);
			SQLBindCol(mhStmt, 6, SQL_C_CHAR, cZip, 100, &qGeneral);

			int i( 1 );
			while( !SQLFetch( mhStmt ) )
			{
				vReturn.push_back( iAddressID );
				printf( "%i ------ AddressID: %i\n%s\n%s\n%s, %s, %s\n\n", i, iAddressID, cAddress1, cAddress2, cCity, cState, cZip );

				++i;
			}
		}
	}

	return vReturn;
}