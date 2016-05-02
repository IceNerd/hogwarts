#include <windows.h>
#include <sqlext.h>
#include <stdio.h>
#include <mbstring.h>

#ifndef ODBC_H
#define ODBC_H

#define MAXDATA 100
#define CHECKSUCCESS( retCode ) ((retCode == SQL_SUCCESS) || (retCode == SQL_SUCCESS_WITH_INFO) )
#define ALIGNSIZE 4
#define ALIGNBUF(Length) Length % ALIGNSIZE ? Length + ALIGNSIZE - (Length % ALIGNSIZE) : Length

class ODBC
{
public:
	ODBC( const char* );
	~ODBC();
	int Connect();
	int Connect( const char*, const char* ); // Allocate env, stat, and conn
	int ExecSQL( const char* );	// Execute SQL statement
	void Disconnect();				// Free pointers to env, stat, conn, and disconnect
	void Error();

protected:
	ODBC();

	bool mbConnected;
	bool mbStmtActive;
	SQLSMALLINT miCol;

	RETCODE mretCode;// ODBC return code
	HENV	mhEnv;	// Environment   
	HDBC	mhDBC;	// Connection handle
	HSTMT	mhStmt;	// Statement handle
	
	unsigned char szData[MAXDATA];					// Returned data storage
	SDWORD cbData;									// Output length of data
	unsigned char mucDSN[SQL_MAX_DSN_LENGTH];	    // Data source name
	unsigned char mucUser[SQL_MAX_OPTION_STRING_LENGTH];
	unsigned char mucPW[SQL_MAX_OPTION_STRING_LENGTH];
};

#endif