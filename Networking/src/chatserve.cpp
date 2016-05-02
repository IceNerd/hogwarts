#include "chatserve.h"


ChatServe::ChatServe()
:Port( &this->u_shortPort ), u_shortPort( 6 )
{
}

ChatServe::~ChatServe()
{
}

unsigned long ChatServe::ThreadBody( void* ptr_Arg )
{
	unsigned long u_lReturn( 0 );

	if( ::GetCurrentThreadId() != this->u_lTIDMain )
	{
		this->Listen();
	}

	return u_lReturn;
}

void ChatServe::Listen()
{
	bool bEnd( false );

	try
	{
		TCPServerSocket TCPServe( *((unsigned short*)this->u_shortPort) );

		while( !bEnd )
		{
			//Create client thread
			ChatClient newClient( TCPServe.accept() );
			if( !newClient.CreateThread() )
			{
				//AddToChat( "ERROR: Unable to create thread" );
				bEnd = true;
			}
		}
	}
	catch( SocketException& errSock )
	{
		//AddToChat( errSock.what() );
	}
}

///**/void* ChatServe::ClientThread( void* TCPClient )
//	{
//		//Guarantees that thread resources are deallocated upon return
//		//pthread_detach( pthread_self() ); 
//
//		//Extract socket file descriptor from argument
//		HandleTCPClient( (TCPSocket*)TCPClient );
//		delete (TCPSocket*)TCPClient;
//
//		return 0;
//	}
//
///**/void ChatServe::HandleTCPClient( TCPSocket* sock )
//	{
//		std::string strProgress;
//		char strBuff[50];
//
//		AddToChat( "Incoming Connection" );
//		try
//		{
//			strProgress = sock->getForeignAddress();
//			strProgress += ":";
//		}
//		catch( SocketException& errSock )
//		{
//			AddToChat( "ERROR: Unable to get foreign address" );
//		}
//
//		try
//		{
//			strProgress += itoa( sock->getForeignPort(), strBuff, 10 );
//		}
//		catch( SocketException& errSock )
//		{
//			AddToChat( "Unable to get foreign port" );
//		}
//
//		strProgress += " with thread ";
//		strProgress += itoa( (int)pthread_self(), strBuff, 10 );
//
//		AddToChat( strProgress );
//
//		//Send received string and receive again until the end of transmission
//		char echoBuffer[32];
//		int recvMsgSize;
//		while( (recvMsgSize = sock->recv( echoBuffer, 32 )) > 0 )
//		{
//			sock->send( echoBuffer, recvMsgSize );
//		}
//		//Destructor closes socket
//	}