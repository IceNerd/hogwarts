#include "chatclient.h"


ChatClient::ChatClient( TCPSocket* init_TCPSock )
:ptr_Socket( init_TCPSock )
{
}

ChatClient::~ChatClient()
{
	if( this->ptr_Socket )
	{
		delete (TCPSocket*) this->ptr_Socket;
		ptr_Socket = 0;
	}
}

unsigned long ChatClient::ThreadBody( void* ptr_Arg )
{
	unsigned long u_lReturn( 0 );

	if( ::GetCurrentThreadId() != this->u_lTIDMain )
	{
		this->HandleTCPClient();
	}

	return u_lReturn;
}

void ChatClient::HandleTCPClient()
{
	std::string strProgress;
	char strBuff[50];

	//AddToChat( "Incoming Connection" );
	try
	{
		strProgress = this->ptr_Socket->getForeignAddress();
		strProgress += ":";
	}
	catch( SocketException& errSock )
	{
		//AddToChat( "ERROR: Unable to get foreign address" );
	}

	try
	{
		strProgress += itoa( this->ptr_Socket->getForeignPort(), strBuff, 10 );
	}
	catch( SocketException& errSock )
	{
		//AddToChat( "Unable to get foreign port" );
	}

	strProgress += " with thread ";
	strProgress += itoa( this->ThreadID, strBuff, 10 );

	//AddToChat( strProgress );

	//Send received string and receive again until the end of transmission
	char echoBuffer[32];
	int recvMsgSize;

	while( (recvMsgSize = this->ptr_Socket->recv( echoBuffer, 32 )) > 0 )
	{
		//Recieve Message
	}

	//Destructor closes socket
}