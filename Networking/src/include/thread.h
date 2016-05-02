/*************************************************************************
Alberto Martinez
05/28/2005

thread.h

<desc>
**************************************************************************/

#ifndef THREAD_H
#define THREAD_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include "property.h"

	class Thread
	{
		public:
			//--- Constructor --------------------------------------------
			Thread( const unsigned long& = 20 );
			//--- Deconstructor --------------------------------------------
			virtual ~Thread();

			//--- Public -------------------------------------------------
			bool CreateThread();
			int IsCreated();

			Property<void*> ThreadHandle;
			Property<void*> MainThreadHandle;
			Property<unsigned long> ThreadID;
			Property<unsigned long> MainThreadID;
			Property<unsigned long> Timeout;

		protected:
			virtual unsigned long ThreadBody( void* );

			void* ptr_TH;				//Thread Handle
			void* ptr_THMain;			//Main Thread Handle
			unsigned long u_lTID;		//Thread ID
			unsigned long u_lTIDMain;	//Main Thread ID
			
		private:
			static int Execute( void* );

			unsigned long u_lTimeout;	//Timeout

	};

	//Workaround Struct for C->C++ Casing Problems
	struct st_Param
	{
		Thread*	ptr_Thread;
	};

#endif