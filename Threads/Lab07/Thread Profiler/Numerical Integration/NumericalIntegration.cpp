///////////////////////////////////////////////////////////////////////////////
//
//  This is a threaded numerical integration code to compute the value of Pi. The
//  iterations are equally divided among the threads and the value of Pi that
//  is computed is also correct. However, this version introduces a serious
//  performance degradation due to the placement of the synch. primitives.
//
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
//
//  Constants are declared with capitalized first character.
//
///////////////////////////////////////////////////////////////////////////////
const int MaxIterations = 1000000;
const int MaxThreads    = 16 ; 

///////////////////////////////////////////////////////////////////////////////
//
//  Globals are declared with "global" keyword as the prefix.
//
//  globalDInterval:      Used by all the threads as a "Read-only" variable
//  globalDSum :          Used by all the threads in a "Read-Write" manner
//  globalNumThreadsUsed: Used by all the threads as a "Read-only" variable
//  globalCS:             Declared global so it is visible to all the threads
//
///////////////////////////////////////////////////////////////////////////////
double           globalDInterval, 
                 globalDSum = 0.0;
int              globalNumThreads = 0;
CRITICAL_SECTION globalCS;

///////////////////////////////////////////////////////////////////////////////
//
//  f(x) - Change this function to compute different integral.
//
//         Integrate f(x) = 4 / (1 + x^2) between 0 and 1 will yield approximation
//            of Pi.
//
///////////////////////////////////////////////////////////////////////////////
double f(double x)
{
	return 4.0/(1.0 + x*x);
}
///////////////////////////////////////////////////////////////////////////////
//
//  PiThreadFunc
//
//  Threaded version of Pi algorithm that successively refines the algorithm
//  to improve the performance of the threaded program.
//
///////////////////////////////////////////////////////////////////////////////
DWORD WINAPI PiThreadFunc(LPVOID pArg)
{
	int myThreadNum = *((int*)pArg);
	int start;
	double dx;


	start = myThreadNum+1 ;

	//
	//  Break the iterations required to compute PI equally among all 
	//  of the threads created by this application
	//
	for( int i = start; i < MaxIterations; i += globalNumThreads )
	{
	  dx         = (i - 0.5) * globalDInterval; 
	  //
	  //  Since globalDSum is being updated, the access to global
	  //  has to be protected.
	  //
	  EnterCriticalSection(&globalCS);
	   globalDSum = globalDSum + f(dx);
	  LeaveCriticalSection(&globalCS);
	}

	return myThreadNum ; // thread exit code

} // PiThreadFunc

///////////////////////////////////////////////////////////////////////////////
//
//  GetCommandLineNumThreads
//
//  Grabs the number of threads from the commandline
//
///////////////////////////////////////////////////////////////////////////////
int GetCommandLineNumThreads(int argc, char **argv)
{
	if( argc == 1 )
	{
		//
		//  No command line arguments specified.
		//  Use 2 threads for the run.
		//
		return 2;
	}
	else
		if( argc == 2 )
		{
			int nThreads = atoi(argv[1]);
			if( nThreads > MaxThreads )
				nThreads = MaxThreads;

			return nThreads;
		}
		else
		{
			printf("Only one command line argument expected!\n");
			printf("Usage:- %s <num_threads>\n", argv[0]);
			exit(-1);
		}
}

///////////////////////////////////////////////////////////////////////////////
//
//  main()
//
//  Application driver that invokes the threaded Pi function. Before the
//  threaded version can be invoked, the main function does the following:
//  
//  (1) Obtains the required number of threads from the command line,
//  (2) Creates the requested number of threads
//  (3) Waits for these threads to finish computation
//  (4) Prints the computed value of PI
//
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)  
{ 
	int    i;
	HANDLE hThread[MaxThreads] ;
	int	   tID[MaxThreads];
	DWORD  threadID;
	double dPi;

	//
	//  Obtain the requested number of threads for this run from
	//  the commandline
	//
	globalNumThreads = GetCommandLineNumThreads(argc, argv);
	//
	//  Provide information on the number of threads and iteration used
	//
	printf("Using %d threads and %d iterations\n", globalNumThreads, 
		                                           MaxIterations) ;
	//
	//  Compute the value for each interval
	//
	globalDInterval = 1.0/MaxIterations;
	//
	//  Initialize the CRITICAL SECTION object
	//
	InitializeCriticalSection(&globalCS);
	// 
	//  Create and start the threads
	//
	//  Here each thread is executing the PiThreadFunc() and ignoring
	//  the value of threadID as we aren't using them.
	//
	for(i = 0; i < globalNumThreads; ++i) 
	{
		tID[i] = i;
		hThread[i] = CreateThread( NULL,          // Security attributes
			                       0,             // Stack size
			                       PiThreadFunc,  // Thread function
								   (LPVOID)&tID[i],     // Data for thread func()
								   0,             // Thread start mode
								   &threadID);    // Returned thread ID
	}
   
	// 
	//  Main thread waits for all compution threads to complete
	//  execution and update the global variable globalDSum.
	//
	WaitForMultipleObjects(globalNumThreads, hThread,  TRUE, INFINITE); 
	//
	//  Delete the CRITICAL SECTION object
	//
	DeleteCriticalSection(&globalCS);

	//
	//  What is the computed value of PI ?
	//
	dPi  = globalDSum * globalDInterval; 

	printf("Computed PI :  %18.16f\n", dPi);
	printf("PI should be:  3.1415926535897932 \n") ;

	return 0 ;
}


