#include "odbc.h"

// Public Constructor
ODBC::ODBC( const char* DSN )
:mbConnected( false ), mbStmtActive( false )
{
	_mbscpy_s( mucDSN, SQL_MAX_DSN_LENGTH, (const unsigned char*)DSN );
}

// Private Constructor
ODBC::ODBC()
:mbConnected( false ), mbStmtActive( false )
{
}

// Deconstructor
ODBC::~ODBC()
{
	if( mbConnected )
	{
		Disconnect();
	}
}

// Allocate environment handle and connection handle, connect to data source, and allocate statement handle.
int ODBC::Connect()
{
	int iReturn( 0 );

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mhEnv);
	SQLSetEnvAttr(mhEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, mhEnv, &mhDBC);
	mretCode = SQLConnect(mhDBC, mucDSN, SQL_NTS, 
							     mucUser, SQL_NTS,
							     mucPW, SQL_NTS);

	if( CHECKSUCCESS( mretCode ) )
	{
		SQLAllocHandle(SQL_HANDLE_STMT, mhDBC, &mhStmt);
		mbConnected = true;
	}
	else
	{
		iReturn = -1;
	}

	return iReturn;
}

int ODBC::Connect( const char* UserName, const char* Password )
{
	_mbscpy_s( mucUser, SQL_MAX_OPTION_STRING_LENGTH, (const unsigned char*)UserName );
	_mbscpy_s( mucPW, SQL_MAX_OPTION_STRING_LENGTH, (const unsigned char*)Password );

	return this->Connect();
}

// Execute SQL command with SQLExecDirect() ODBC API.
int ODBC::ExecSQL( const char* SQLStatement )
{
	int iReturn( -1 );
	if( mbConnected )
	{
		mretCode = SQLExecDirect( mhStmt, (unsigned char*)SQLStatement, SQL_NTS );
		if( CHECKSUCCESS( mretCode ) )
		{//Success
			mbStmtActive = true;
			SQLNumResultCols( mhStmt, &miCol );
			iReturn = miCol;
		}
		else
		{
			Error();
		}
	}
	return iReturn;
}

// Free the statement handle, disconnect, free the connection handle, and free the environment handle.
void ODBC::Disconnect()
{
	SQLFreeHandle(SQL_HANDLE_STMT, mhStmt);
	SQLDisconnect(mhDBC);
	SQLFreeHandle(SQL_HANDLE_DBC, mhDBC);
	SQLFreeHandle(SQL_NULL_HANDLE, mhEnv);
	mbConnected = false;
}

void ODBC::Error()
{
   unsigned char szSQLSTATE[10];
   SDWORD nErr;
   unsigned char msg[SQL_MAX_MESSAGE_LENGTH + 1];
   SWORD cbmsg;

   while( SQLError(0, 0, mhStmt, szSQLSTATE, &nErr, msg, sizeof(msg), &cbmsg) == SQL_SUCCESS )
   {
      printf("Error:\nSQLSTATE=%s, Native error=%ld, msg='%s'", szSQLSTATE, nErr, msg);
   }
}