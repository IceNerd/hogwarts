#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "PracticalSocket.h"
#include "thread.h"
#include "property.h"

class ChatClient : public Thread
{
	public:
		ChatClient( TCPSocket* );
		virtual ~ChatClient();

	protected:
		virtual unsigned long ThreadBody( void* );
		void HandleTCPClient();

	private:
		TCPSocket* ptr_Socket;

};

#endif