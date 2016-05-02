/*************************************************************************
Alberto Martinez
05/28/2005

thread.cpp

<desc>
**************************************************************************/

#include "thread.h"

//--- Constructor --------------------------------------------------------
	Thread::Thread( const unsigned long& u_lTimeoutInit )
	:ThreadHandle( &this->ptr_TH ), MainThreadHandle( &this->ptr_THMain ), ThreadID( &this->u_lTID ), MainThreadID( &this->u_lTIDMain ), Timeout( &this->u_lTimeout )
	{
		this->ptr_TH = 0;
		this->ptr_THMain = ::GetCurrentThread();
		this->u_lTID = 0;
		this->u_lTIDMain = ::GetCurrentThreadId();
		this->u_lTimeout = u_lTimeoutInit;//in ms
	}

//--- Deconstructor --------------------------------------------------------
	Thread::~Thread()
	{
		if( this->ptr_TH )
		{
			if( ::WaitForSingleObject( this->ptr_TH, this->u_lTimeout ) == WAIT_TIMEOUT )
			{
				::TerminateThread( this->ptr_TH, 1 );
			}

			::CloseHandle( this->ptr_TH );
		}
	}

//--- Public -------------------------------------------------------------
	bool Thread::CreateThread()
	{
		bool bReturn( false );

		if( !this->IsCreated() )
		{
			st_Param* ptr_Param = new st_Param;
			ptr_Param->ptr_Thread = this;
			this->ptr_TH = ::CreateThread( 0, 0, (unsigned long(__stdcall*)(void*))this->Execute, (void*)(ptr_Param), 0, &this->u_lTID );
			bReturn = (this->ptr_TH ? true : false);
		}

		return bReturn;
	}

	int Thread::IsCreated()
	{
		return (this->ptr_TH != 0);
	}

//--- Protected ----------------------------------------------------------
	unsigned long Thread::ThreadBody( void* ptr_Arg )
	{
		unsigned long u_lReturn( 0 );

		if( ::GetCurrentThreadId() != this->u_lTIDMain )
		{
			//--code here
		}

		return u_lReturn;
	}

//--- Private ------------------------------------------------------------
	int Thread::Execute( void* ptr_Param )
	{
		Thread*	ptr_Thread;
		ptr_Thread = (Thread*)((st_Param*)ptr_Param)->ptr_Thread;
		delete ((st_Param*)ptr_Param);

		return ptr_Thread->ThreadBody( 0 );
	}