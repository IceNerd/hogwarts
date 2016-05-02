/*************************************************************************
Alberto Martinez
05/28/2005

udpcon.h

<desc>
**************************************************************************/

#ifndef UDPCON_H
#define UDPCON_H

#include <list>
#include <string>
#include <vector>

#include "PracticalSocket.h"
#include "thread.h"
#include "property.h"

#define BROADCASTIP "224.0.0.1"
#define PING "#PING#"
#define PONG "@PONG@"
#define LOGOFF "!OUT!"
#define DEF_PORT 6

	class UDPCon : public Thread
	{
		public:
			//--- Constructor --------------------------------------------
			UDPCon( std::list<std::string>&, HWND = 0, const unsigned short& = DEF_PORT );

			//--- Deconstructor ------------------------------------------
			virtual ~UDPCon();

			//--- Public -------------------------------------------------
			bool SendTo( const void*, int, const std::string&, const unsigned short& = DEF_PORT );
			std::vector<std::string>* GetClientList();
			void SortPings();

		protected:
			virtual unsigned long ThreadBody( void* );
			void HandleIncomingUDP();
			void AddToOutput( const std::string& );

		private:
			UDPSocket Socket;
			std::list<std::string>& lstOutput;
			std::vector<std::string> vctClients;
			std::vector<std::string> vctClientsOld;
			HWND WinHandle;

	};

#endif