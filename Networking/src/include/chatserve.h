#ifndef CHATSERVE_H
#define CHATSERVE_H

#include "PracticalSocket.h"
#include "thread.h"
#include "property.h"
#include "chatclient.h"

class ChatServe : public Thread
{
	public:
		ChatServe();
		virtual ~ChatServe();

		Property<unsigned short> Port;

	protected:
		virtual unsigned long ThreadBody( void* );
		void Listen();

	private:
		unsigned short u_shortPort;
};

#endif