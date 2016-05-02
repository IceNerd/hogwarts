#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <conio.h>

#include "shroomdb.h"

int CleanCharArray( char*, int );
int CreateTransItem( ShroomDB&, const int& );
int MainMenu();
int UpdateShroomMenu();
int NewStation( ShroomDB&, std::vector<int>& );
int NewBuyer( ShroomDB&, std::vector<int>& );
int NewPicker( ShroomDB&, std::vector<int>& );
int CreateTrans( ShroomDB& );

int main()
{
	// Start up our connection
	ShroomDB Bernie( "CST324" );

	if( Bernie.Connect("bernie", "bernie") == 0 )
	{//Connected!
		int iOption( 0 );

		printf("Connected to Database\n\n");
		while( iOption != 27 )
		{
			std::vector<int> vReturn;
			char cBuffer[100];

			iOption = MainMenu();
			system("cls");
			switch( iOption )
			{
				case( 49 )://'1'
					Bernie.DisplayShrooms();
				break;

				case( 50 )://'2'
					vReturn = Bernie.DisplayShrooms();
					if( !vReturn.empty() )
					{
						printf( "Which Mushroom do you wish to delete?\n" );
						fgets( cBuffer, sizeof(cBuffer), stdin );
						iOption = atoi( cBuffer ) - 1;

						if( (iOption > -1) && (iOption < (int)vReturn.capacity()) )
						{
							if( Bernie.DeleteShroom( vReturn[iOption] ) == -1 )
							{
								printf( "Mushroom Deleted\n\n" );
							}
							else
							{
								printf( "Error: Entry not deleted\n\n" );
							}
						}
						else
						{
							printf("Option out of bounds\n\n");
						}
					}
				break;

				case( 51 )://'3'
					vReturn = Bernie.DisplayShrooms();
					if( !vReturn.empty() )
					{
						printf( "Which Mushroom do you wish to update?\n" );
						fgets( cBuffer, sizeof(cBuffer), stdin );
						iOption = atoi( cBuffer ) - 1;

						switch( UpdateShroomMenu() )
						{
							case( 49 )://'1'
								printf("Update Name to: ");
								for( int i = 0; i < 100; ++i )
								{
									cBuffer[i] = '\0';
								}
								fgets( cBuffer, sizeof(cBuffer), stdin );
								Bernie.UpdateShroomName( vReturn[iOption], cBuffer );
							break;
							case( 50 )://'2'
							break;
							case( 51 )://'3'
							break;
							default:
							break;
						}
					}
				break;

				case( 52 )://'4'
					CreateTransItem( Bernie, CreateTrans( Bernie ) );
				break;

				case( 53 )://'5'
					printf( "View Transaction Number: " );
					fgets( cBuffer, sizeof(cBuffer), stdin );
					iOption = atoi( cBuffer );
					Bernie.DisplayTransaction( iOption );
					iOption = 0;
				break;
				case( 27 )://'esc'
				break;

				default:
					printf( "Invalid Input: %i\n\n", iOption );
				break;
			}
		}
	}

	return 0;
}

int CleanCharArray( char* CleanThis, int iSize )
{
	int iReturn( 0 );
	for( int i = 0; i < iSize && iReturn == 0; ++i )
	{
		if( CleanThis[i] == '\n' )
		{
			CleanThis[i] = '\0';
			iReturn = 1;
		}
	}

	return 0;
}

int MainMenu()
{
	printf("------ Shroom DB Interface ------\n");
	printf("1: Display Mushroom Data\n");
	printf("2: Delete Mushroom\n");
	printf("3: Update Mushroom Data\n");
	printf("4: Create a Transaction\n");
	printf("5: Display Transaction\n\n");

	printf("ESC to exit\n");
	
	return _getch();
}


int UpdateShroomMenu()
{
	printf("------ Which Mushroom field to update?\n");
	printf("1: ShroomName\n");
	printf("2: ShroomDescription\n");
	printf("3: Season\n");

	return _getch();
}

int NewStation( ShroomDB& DB, std::vector<int>& vctIDs )
{
	int iReturn(0);
	system("cls");

	char cTown[100];
	char cLocationDesc[100];
	char cActive;
	char cPhone[100];

	char cQuery[500];

	printf("Name: ");
	fgets( cTown, 100, stdin );
	CleanCharArray( cTown, 100 );

	printf("Description: ");
	fgets( cLocationDesc, 100, stdin );
	CleanCharArray( cLocationDesc, 100 );

	printf("Active: ");
	cActive = _getch();
	printf("%c", cActive);
	printf("\n");

	printf("Phone: ");
	fgets( cPhone, 100, stdin );
	CleanCharArray( cPhone, 100 );

	for( std::vector<int>::iterator i = vctIDs.begin(); i != vctIDs.end(); i++ )
	{
		if( (*i) == iReturn )
		{
			iReturn++;
			i = vctIDs.begin();
			if( (*i) == iReturn )
			{
				iReturn++;
			}
		}
	}

	sprintf_s( cQuery, "insert into station( stationid, town, locationdesc, active, phone ) values( %i, '%s', '%s', '%c', '%s' )", iReturn, cTown, cLocationDesc, cActive, cPhone );
	DB.ExecSQL( cQuery );

	return iReturn;
}

int NewBuyer( ShroomDB& DB, std::vector<int>& vctIDs )
{
	int iReturn(0);
	system("cls");

	char cBuffer[100];

	char cFName[100];
	char cLName[100];
	char cPhone[100];
	int iAddressID(0);

	char cQuery[500];

	printf("First Name: ");
	fgets( cFName, 100, stdin );
	CleanCharArray( cFName, 100 );

	printf("Last Name: ");
	fgets( cLName, 100, stdin );
	CleanCharArray( cLName, 100 );

	printf("Phone: ");
	fgets( cPhone, 100, stdin );
	CleanCharArray( cPhone, 100 );

	system("cls");
	std::vector<int> vReturn = DB.DisplayAddresses();
	printf("Choose Address for Picker: ");
	fgets( cBuffer, sizeof(cBuffer), stdin );
	iAddressID = atoi(cBuffer) - 1;
	system("cls");

	if( iAddressID > -1 && iAddressID < (int)vReturn.capacity() )
	{
		iAddressID = vReturn[iAddressID];
	}

	for( std::vector<int>::iterator i = vctIDs.begin(); i != vctIDs.end(); i++ )
	{
		if( (*i) == iReturn )
		{
			iReturn++;
			i = vctIDs.begin();
			if( (*i) == iReturn )
			{
				iReturn++;
			}
		}
	}

	sprintf_s( cQuery, "insert into buyer( buyerid, firstname, lastname, phone, addressid ) values( %i, '%s', '%s', '%s', %i )", iReturn, cFName, cLName, cPhone, iAddressID );
	DB.ExecSQL( cQuery );

	return iReturn;
}

int NewPicker( ShroomDB& DB, std::vector<int>& vctIDs )
{
	int iReturn(0);
	system("cls");

	char cBuffer[100];

	char cFName[100];
	char cLName[100];
	char cLicense[100];
	char cPhone[100];
	int iAddressID(0);

	char cQuery[500];

	printf("First Name: ");
	fgets( cFName, 100, stdin );
	CleanCharArray( cFName, 100 );

	printf("Last Name: ");
	fgets( cLName, 100, stdin );
	CleanCharArray( cLName, 100 );

	printf("License: ");
	fgets( cLicense, 100, stdin );
	CleanCharArray( cLicense, 100 );

	printf("Phone: ");
	fgets( cPhone, 100, stdin );
	CleanCharArray( cPhone, 100 );

	system("cls");
	std::vector<int> vReturn = DB.DisplayAddresses();
	printf("Choose Address for Picker: ");
	fgets( cBuffer, sizeof(cBuffer), stdin );
	iAddressID = atoi(cBuffer) - 1;
	system("cls");

	if( iAddressID > -1 && iAddressID < (int)vReturn.capacity() )
	{
		iAddressID = vReturn[iAddressID];
	}
	

	for( std::vector<int>::iterator i = vctIDs.begin(); i != vctIDs.end(); i++ )
	{
		if( (*i) == iReturn )
		{
			iReturn++;
			i = vctIDs.begin();
			if( (*i) == iReturn )
			{
				iReturn++;
			}
		}
	}

	sprintf_s( cQuery, "insert into picker( pickerid, firstname, lastname, license, phone, addressid ) values( %i, '%s', '%s', '%s', '%s', %i )", iReturn, cFName, cLName, cLicense, cPhone, iAddressID );
	DB.ExecSQL( cQuery );

	return iReturn;
}

int CreateTrans( ShroomDB& DB )
{
	int iReturn( -1 );
	std::vector<int> vReturn;
	char cBuffer[100];
	int iTransID( 0 );
	int iStationID;
	int iBuyerID;
	int iPickerID;
	char cTransNumber[100];
	char cTransDate[100];

	char cQuery[500];

	vReturn = DB.DisplayStations();
	while( iReturn == -1 )
	{
		printf("Which Station? ('new' to add one) ");
		fgets( cBuffer, sizeof(cBuffer), stdin );
		CleanCharArray( cBuffer, 100 );
		if( _stricmp( cBuffer, "new" ) == 0 )
		{
			iStationID = NewStation( DB, vReturn );
			iReturn = iStationID;
		}
		else
		{
			iStationID = atoi( cBuffer ) - 1;
			if( iStationID > -1 && iStationID < (int)vReturn.capacity() )
			{
				iStationID = vReturn[iStationID];
				iReturn = iStationID;
			}
		}
	}
	iReturn = -1;
	system("cls");

		vReturn = DB.DisplayBuyers();
		while( iReturn == -1 )
		{
			printf("Who is the Buyer? ('new' to add one) ");
			fgets( cBuffer, sizeof(cBuffer), stdin );
			if( _stricmp( cBuffer, "new" ) == 0 )
			{
				iBuyerID = NewBuyer( DB, vReturn );
				iReturn = iBuyerID;
			}
			else
			{
				iBuyerID = atoi( cBuffer ) - 1;
				if( iBuyerID > -1 && iBuyerID < (int)vReturn.capacity() )
				{
					iBuyerID = vReturn[iBuyerID];
					iReturn = iBuyerID;
				}
			}
		}
		iReturn = -1;
		system("cls");

			vReturn = DB.DisplayPickers();
			while( iReturn == -1 )
			{
				printf("Who is the Picker? ('new' to add one) ");
				fgets( cBuffer, sizeof(cBuffer), stdin );
				if( _stricmp( cBuffer, "new" ) == 0 )
				{
					iPickerID = NewPicker( DB, vReturn );
					iReturn = iPickerID;
				}
				else
				{
					iPickerID = atoi( cBuffer ) - 1;
					if( iPickerID > -1 && iPickerID < (int)vReturn.capacity() )
					{
						iPickerID = vReturn[iPickerID];
						iReturn = iPickerID;
					}
				}
			}
			iReturn = -1;
			system("cls");

				printf("What is the Transaction Number? ");
				fgets( cTransNumber, sizeof(cTransNumber), stdin );
				CleanCharArray( cTransNumber, 100 );

				printf("What is the Transaction Date? (DD-MON-YEAR)ex:(11-NOV-1983) ");
				fgets( cTransDate, sizeof(cTransDate), stdin );
				CleanCharArray( cTransDate, 100 );

				vReturn = DB.GetTransIDs();
				for( std::vector<int>::iterator i = vReturn.begin(); i != vReturn.end(); i++ )
				{
					if( (*i) == iTransID )
					{
						i = vReturn.begin();
						iTransID++;
						if( (*i) == iTransID )
						{
							iTransID++;
						}
					}
				}

				iReturn = iTransID;
				sprintf_s( cQuery, "insert into trans( transid, stationid, buyerid, pickerid, transnumber, transdate ) values( %i, %i, %i, %i, %s, '%s' )", iTransID, iStationID, iBuyerID, iPickerID, cTransNumber, cTransDate );
				DB.ExecSQL( cQuery );

	return iReturn;
}

int CreateTransItem( ShroomDB& DB, const int& iTransID )
{
	int iReturn( 0 );
	if( iReturn != -1 )
	{
		char cBuffer[100];
		int iGradeID;
		char cQty[25];
		char cPrice[25];
		char cBonus[25];
		char cQuery[500];
		std::vector<int> vReturn;

		while( iReturn == 0 )
		{
			vReturn = DB.DisplayShroomGrades();
			printf("Mushroom to add: ");
			fgets( cBuffer, sizeof(cBuffer), stdin );
			iGradeID = atoi(cBuffer) - 1;
			system("cls");

			if( iGradeID > -1 && iGradeID < (int)vReturn.capacity() )
			{
				iGradeID = vReturn[iGradeID];

				printf("Quantity: ");
				fgets( cQty, sizeof(cQty), stdin );
				CleanCharArray( cQty, 25 );
				printf("Price: ");
				fgets( cPrice, sizeof(cPrice), stdin );
				CleanCharArray( cPrice, 25 );
				printf("Bonus: ");
				fgets( cBonus, sizeof(cBonus), stdin );
				CleanCharArray( cBonus, 25 );

				sprintf_s( cQuery, "insert into trans_item( transid, gradeid, qty, price, bonus ) values( %i, %i, %s, %s, %s )", iTransID, iGradeID, cQty, cPrice, cBonus );
				DB.ExecSQL( cQuery );
			}
			system("cls");
			printf( "'esc' to end adding or any key to add another" );
			if( _getch() == 27 )
			{
				iReturn = 1;
			}
			system("cls");
		}
	}

	return iReturn;
}