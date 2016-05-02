#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <vector>

int PrintAddresses();
bool ModAddress();
bool AddStationPrice();
bool AddTransaction();

bool RemoveUnusedAddresses();

int main()
{
	bool bEnd( false ), bValid( false );
	int iChoice( 0 );

	while( !bEnd )
	{
		bValid = false;
		system("cls");
		while( !bValid )
		{
			std::cout<<"What would you like to do?\n"
				<<"1: Insert a Station_Price entry\n"
				<<"2: Add a transaction\n"
				<<"3: Edit an existing address\n"
				<<"4: Cleanup unused addresses\n"
				<<"\nesc: Exit\n";
			iChoice = getch();
			if( ((iChoice > 48) && (iChoice < 53)) || (iChoice == 27) )
			{
				bValid = true;
			}
		}
		switch( iChoice )
		{
			case 49://1
				AddStationPrice();
			break;

			case 50://2 Add Transaction
				AddTransaction();
			break;

			case 51://3
				system("cls");
				PrintAddresses();
				ModAddress();
			break;

			case 52://4 Remove Unused Addresses
				RemoveUnusedAddresses();
			break;

			case 27: //esc key
				bEnd = true;
			break;

			default:
			break;
		}
	}

	return 0;
}

int PrintAddresses()
{

	SQLHANDLE h_Env;
	SQLHANDLE h_DBC;
	SQLHANDLE h_Statement;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);

	
	int iCount( 0 );
	SDWORD cbQual;
	std::string chQuery = "select * from address";
	char chID[11];
	char chStreet1[31];
	char chStreet2[31] = "";
	char chCity[31];
	char chState[3];
	char chZip[11];

	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SQLExecDirect(h_Statement, (unsigned char *)chQuery.c_str(), SQL_NTS);
	SQLBindCol(h_Statement, 1, SQL_CHAR, chID, 11, &cbQual);
	SQLBindCol(h_Statement, 2, SQL_CHAR, chStreet1, 31, &cbQual);
	SQLBindCol(h_Statement, 3, SQL_CHAR, chStreet2, 31, &cbQual);
	SQLBindCol(h_Statement, 4, SQL_CHAR, chCity, 31, &cbQual);
	SQLBindCol(h_Statement, 5, SQL_CHAR, chState, 3, &cbQual);
	SQLBindCol(h_Statement, 6, SQL_CHAR, chZip, 11, &cbQual);

	while( !SQLFetch(h_Statement) )
	{
		std::cout << chID << ":\t" << chStreet1 << "\n";
		if( strcmp( chStreet2, "" ) != 0 )
		{
			std::cout<< '\t' << chStreet2 << "\n";
		}
		std::cout<< '\t' << chCity << ", " << chState << ", " << chZip << "\n\n";
		strcpy( chStreet2, "" );
		iCount++;
	}

	//disconnect
	SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
	SQLDisconnect( h_DBC );
	SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
	SQLFreeHandle( SQL_NULL_HANDLE, h_Env );

	return iCount;
}

bool ModAddress()
{
	SQLHANDLE h_Env;
	SQLHANDLE h_DBC;
	SQLHANDLE h_Statement;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SDWORD cbQual;
	std::string chQuery = "select * from address where addressid = ";
//	std::string chIn;
	char chIn[100];
	std::cin.getline( chIn, 30 );

	chQuery += chIn;

	char chID[11];
	char chStreet1[31];
	char chStreet2[31] = "";
	char chCity[31];
	char chState[3];
	char chZip[11];

	SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);
	SQLBindCol(h_Statement, 1, SQL_CHAR, chID, 11, &cbQual);
	SQLBindCol(h_Statement, 2, SQL_CHAR, chStreet1, 31, &cbQual);
	SQLBindCol(h_Statement, 3, SQL_CHAR, chStreet2, 31, &cbQual);
	SQLBindCol(h_Statement, 4, SQL_CHAR, chCity, 31, &cbQual);
	SQLBindCol(h_Statement, 5, SQL_CHAR, chState, 3, &cbQual);
	SQLBindCol(h_Statement, 6, SQL_CHAR, chZip, 11, &cbQual);

	if( !SQLFetch(h_Statement) )
	{
		std::cout << chID << ":\t" << chStreet1 << "\n";
		if( strcmp( chStreet2, "" ) != 0 )
		{
			std::cout<< '\t' << chStreet2 << "\n";
		}
		else
		{
			strcpy( chStreet2, "" );
		}
		std::cout<< '\t' << chCity << ", " << chState << ", " << chZip << "\n\n";

		//disconnect
		SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
		SQLDisconnect( h_DBC );
		SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
		SQLFreeHandle( SQL_NULL_HANDLE, h_Env );
	
		//Collect Data for Modification
		chQuery = "update address set street1 = '";

		//Street1
		std::cout<<"Street Line 1: ";
		std::cin.getline( chIn, 101 );
		std::cout<<"\n";
		chQuery += chIn;
		chQuery += "', street2 = '";

		//Street2
		std::cout<<"Street Line 2: ";
		std::cin.getline( chIn, 101 );
		std::cout<<"\n";
		chQuery += chIn;
		chQuery += "', city = '";

		//City
		std::cout<<"City: ";
		std::cin.getline( chIn, 101 );
		std::cout<<"\n";
		chQuery += chIn;
		chQuery += "', state = '";

		//State
		std::cout<<"State: ";
		std::cin.getline( chIn, 101 );
		std::cout<<"\n";
		chQuery += chIn;
		chQuery += "', zip = '";

		//Zip
		std::cout<<"Zip: ";
		std::cin.getline( chIn, 101 );
		std::cout<<"\n";
		chQuery += chIn;
		chQuery += "' where addressid = ";
		chQuery += chID;
		chQuery += ";";
		
		//Execute Built Statement
		std::cout<<chQuery;
		getch();

		//reconnect
		SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
		SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
		SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
		SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
						(unsigned char *)"system", SQL_NTS,
						(unsigned char *)"darlin", SQL_NTS);
		SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

		SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);
		//SQLExecDirect(h_Statement, (unsigned char *) "commit;", SQL_NTS);

		//disconnect
		SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
		SQLDisconnect( h_DBC );
		SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
		SQLFreeHandle( SQL_NULL_HANDLE, h_Env );

	}
	else
	{
		std::cout<<"Address ID not found!\n";
		getch();
	}
	return true;
}

bool AddStationPrice( )
{
	SQLHANDLE h_Env;
	SQLHANDLE h_DBC;
	SQLHANDLE h_Statement;

	system("cls");

	//std::string chIn;
	char chIn[100];
	std::string chQuery;

	//Collect Data for Modification
	chQuery = "insert into station_price( stationid, gradeid, price, timestamp ) values( '";

	//StationID
	std::cout<<"Station ID: ";
	std::cin.getline( chIn, 101 );
	std::cout<<"\n";
	chQuery += chIn;
	chQuery += "', '";

	//GradeID
	std::cout<<"Grade ID: ";
	std::cin.getline( chIn, 101 );
	std::cout<<"\n";
	chQuery += chIn;
	chQuery += "', '";

	//Price
	std::cout<<"Price: ";
	std::cin.getline( chIn, 101 );
	std::cout<<"\n";
	chQuery += chIn;
	chQuery += "', '";

	//timestamp
	std::cout<<"Time Stamp: ";
	std::cin.getline( chIn, 101 );
	std::cout<<"\n";
	chQuery += chIn;
	chQuery += "' )";

	//Connect and execute built command
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);

	//disconnect
	SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
	SQLDisconnect( h_DBC );
	SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
	SQLFreeHandle( SQL_NULL_HANDLE, h_Env );

	return true;
}

bool AddTransaction()
{
	SQLHANDLE h_Env;
	SQLHANDLE h_DBC;
	SQLHANDLE h_Statement;
	SDWORD cbQual;

	char chIn[100];
	char chStationID[10];
	char chTransDate[10];
	char chTransID[10];
	std::string chQuery;

	system("cls");

	//Get ID of this Transaction
	chQuery = "select last_number from user_sequences where sequence_name = 'SEQ_TRANSID'";

	//Connect and execute built command
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);
	SQLBindCol(h_Statement, 1, SQL_CHAR, chTransID, 10, &cbQual);
	SQLFetch( h_Statement );

	//disconnect
	SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
	SQLDisconnect( h_DBC );
	SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
	SQLFreeHandle( SQL_NULL_HANDLE, h_Env );


	//Collect Data for Modification
	chQuery = "insert into trans( transid, stationid, pickerid, transnumber, transdate ) values( seq_transid.NEXTVAL, '";

	//StationID
	std::cout<<"Station ID: ";
	std::cin.getline( chStationID, 10 );
	std::cout<<"\n";
	chQuery += chStationID;
	chQuery += "', '";

	//PickerID
	std::cout<<"Picker ID: ";
	std::cin.getline( chIn, 101 );
	std::cout<<"\n";
	chQuery += chIn;
	chQuery += "', '";

	//Transaction Number
	std::cout<<"Transaction Number: ";
	std::cin.getline( chIn, 101 );
	std::cout<<"\n";
	chQuery += chIn;
	chQuery += "', '";

	//Transaction Date
	std::cout<<"Transaction Date: ";
	std::cin.getline( chTransDate, 10 );
	std::cout<<"\n";
	chQuery += chTransDate;
	chQuery += "' )";

	std::cout<<chQuery<<"\n";
	getch();

	//Connect and execute built command
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);

	//disconnect
	SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
	SQLDisconnect( h_DBC );
	SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
	SQLFreeHandle( SQL_NULL_HANDLE, h_Env );

	//-------------------Add Items to the transaction--------------
	bool bDoneAdding( false );
	char chChoice( 0 );
	char chGradeID[10];
	char chPrice[10];
	std::string chSecondQuery;
	while( bDoneAdding == false )
	{
		system("cls");
		std::cout<<"Add an item to this transaction? (y or n) ";
		chChoice = getch();
		if( chChoice == 89 || chChoice == 121 )
		{
			//---Get information for trans_item---
			//We have the transaction id and will get the price from the grade selection unless unavailable
			chQuery = "insert into trans_item( transid, gradeid, qty, price, bonus ) values( ";
			chQuery += chTransID;
			chQuery += ", ";

			//GradeID
			std::cout<<"Grade ID: ";
			std::cin.getline( chGradeID, 10 );
			std::cout<<"\n";
			chQuery += chGradeID;
			chQuery += ", ";

			//qty
			std::cout<<"Quantity: ";
			std::cin.getline( chIn, 10 );
			std::cout<<"\n";
			chQuery += chIn;
			chQuery += ", ";
			
			//price
			//See if the price is in station_price
			chSecondQuery = "select price from station_price where (stationid = ";
			chSecondQuery += chStationID;
			chSecondQuery += ") and (gradeid = ";
			chSecondQuery += chGradeID;
			chSecondQuery += ") and (timestamp = '";
			chSecondQuery += chTransDate;
			chSecondQuery += "')";

			std::cout<<chSecondQuery<<"\n";
			getch();

			//--------------------------
			//Connect and execute built command
			SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
			SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
			SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
			SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
					         (unsigned char *)"system", SQL_NTS,
							 (unsigned char *)"darlin", SQL_NTS);
			SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

			SQLExecDirect(h_Statement, (unsigned char *) chSecondQuery.c_str(), SQL_NTS);
			strcpy( chPrice, "" );
			SQLBindCol(h_Statement, 1, SQL_CHAR, chPrice, 10, &cbQual);
			SQLFetch( h_Statement );

			//disconnect
			SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
			SQLDisconnect( h_DBC );
			SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
			SQLFreeHandle( SQL_NULL_HANDLE, h_Env );
			//--------------------------

			if( strcmp( chPrice, "" ) == 0 )//no price found, so ask for one.
			{
				std::cout<<"No Price Found for this date\nPlease provide a price:";
				std::cin.getline( chPrice, 10 );
				std::cout<<"\n";
			}
			chQuery += chPrice;
			chQuery += ", ";

			//Bonus
			std::cout<<"Bonus: ";
			std::cin.getline( chIn, 10 );
			std::cout<<"\n";
			if( strcmp( chIn, "" ) == 0 )
			{
				chQuery += "0";
			}
			else
			{
				chQuery += chIn;
			}
			chQuery += ");";

			std::cout<<chQuery<<"\n";
			getch();

			//--------------------------
			//Connect and execute built command
			SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
			SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
			SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
			SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
					         (unsigned char *)"system", SQL_NTS,
							 (unsigned char *)"darlin", SQL_NTS);
			SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

			SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);

			//disconnect
			SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
			SQLDisconnect( h_DBC );
			SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
			SQLFreeHandle( SQL_NULL_HANDLE, h_Env );
			//--------------------------

		}
		else
		{
			bDoneAdding = true;
		}
	}

	return true;
}

bool RemoveUnusedAddresses()
{
	SQLHANDLE h_Env;
	SQLHANDLE h_DBC;
	SQLHANDLE h_Statement;
	SDWORD cbQual;
	char chID[100];
	std::vector< std::string > vect_IDUsed;
	std::vector< std::string > vect_IDAddresses;
	vect_IDUsed.clear();
	vect_IDAddresses.clear();
	std::string chQuery;
	std::string chINCon;
	system("cls");

	//Collect Data for Modification
	chQuery = "select addressid from picker";

	//Connect and execute built command
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);
	SQLBindCol(h_Statement, 1, SQL_CHAR, chID, 11, &cbQual);
	while( !SQLFetch( h_Statement ) )
	{
		chINCon = chID;
		vect_IDUsed.push_back( chINCon );
	}

	//disconnect
	SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
	SQLDisconnect( h_DBC );
	SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
	SQLFreeHandle( SQL_NULL_HANDLE, h_Env );

	//Collect Data for Modification
	chQuery = "select addressid from employee";

	//Connect and execute built command
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);
	SQLBindCol(h_Statement, 1, SQL_CHAR, chID, 11, &cbQual);
	while( !SQLFetch( h_Statement ) )
	{
		chINCon = chID;
		vect_IDUsed.push_back( chINCon );
	}

	//disconnect
	SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
	SQLDisconnect( h_DBC );
	SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
	SQLFreeHandle( SQL_NULL_HANDLE, h_Env );

	//Collect Data for Modification
	chQuery = "select addressid from address";

	//Connect and execute built command
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
	SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
	SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
		             (unsigned char *)"system", SQL_NTS,
					 (unsigned char *)"darlin", SQL_NTS);
	SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

	SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);
	SQLBindCol(h_Statement, 1, SQL_CHAR, chID, 11, &cbQual);
	while( !SQLFetch( h_Statement ) )
	{
		chINCon = chID;
		vect_IDAddresses.push_back( chINCon );
	}

	//disconnect
	SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
	SQLDisconnect( h_DBC );
	SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
	SQLFreeHandle( SQL_NULL_HANDLE, h_Env );


	//compare the two vectors
	bool bAddyUsed( false );
	for( std::vector< std::string >::iterator iter_addy = vect_IDAddresses.begin(); iter_addy != vect_IDAddresses.end(); ++iter_addy )
	{
		bAddyUsed = false;
		for( std::vector< std::string >::iterator iter_used = vect_IDUsed.begin(); iter_used != vect_IDUsed.end(); ++iter_used )
		{
			if( (*iter_addy) == (*iter_used) )
			{
				bAddyUsed = true;
			}
		}

		//remove it from the DB
		if( !bAddyUsed )
		{
			//Collect Data for Modification
			chQuery = "delete from address where addressid = ";
			chQuery += (*iter_addy);

			//Connect and execute built command
			SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_Env);
			SQLSetEnvAttr(h_Env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
			SQLAllocHandle(SQL_HANDLE_DBC, h_Env, &h_DBC);
			SQLConnect(h_DBC, (unsigned char *)"kazoo", SQL_NTS, 
							(unsigned char *)"system", SQL_NTS,
							(unsigned char *)"darlin", SQL_NTS);
			SQLAllocHandle(SQL_HANDLE_STMT, h_DBC, &h_Statement);

			SQLExecDirect(h_Statement, (unsigned char *) chQuery.c_str(), SQL_NTS);

			//disconnect
			SQLFreeHandle(SQL_HANDLE_STMT, h_Statement);
			SQLDisconnect( h_DBC );
			SQLFreeHandle( SQL_HANDLE_DBC, h_DBC );
			SQLFreeHandle( SQL_NULL_HANDLE, h_Env );
			
		}

	}
	return true;
}
