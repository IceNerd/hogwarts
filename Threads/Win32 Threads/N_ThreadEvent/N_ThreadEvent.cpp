/*
	This simple code demonstrates CreateEvent, WaitForMultipleObjects 
	Win32 API functions and event objects.

	This code computes sum of Mercator's series.

	Mercator's series expression for ln( x + 1 ) function is:
 
		ln( x + 1 ) = x - x^2/2 + x^3/3 - x^4/4 + x^5/5 - ...

		for -1 < x <= 1.
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>


#define NUMTHREADS 4
#define SERIES_MEMBER_COUNT 10000

HANDLE *threadHandles, masterThreadHandle;
CRITICAL_SECTION countCS;
double *sums;
double x = 1.0, res = 0.0;
int threadCount = 0;

double getMember(int n, double x)
{
	double numerator = 1;
	for( int i=0; i<n; i++ )
		numerator = numerator*x;

	if ( n % 2 == 0 )
		return ( - numerator / n );
	else
		return numerator/n;
}

DWORD WINAPI threadProc(LPVOID par)
{
	int threadIndex = *((int *)par);
	sums[threadIndex] = 0;
	for(int i=threadIndex; i<SERIES_MEMBER_COUNT;i+=NUMTHREADS)
		sums[threadIndex] += getMember(i+1, x);

	//Signal Master thread that one more processing thread is done
	EnterCriticalSection(&countCS);
	  threadCount++;
    LeaveCriticalSection(&countCS);

	delete par;
	return 0;
}

DWORD WINAPI masterThreadProc(LPVOID par)
{
	for( int i=0; i<NUMTHREADS; i++ ) ResumeThread(threadHandles[i]);  // Start computing threads

	while (threadCount != NUMTHREADS) {}   // busy wait until all threads are done with computation of partial sums
	res = 0;
	for(int i=0; i<NUMTHREADS; i++)
		res += sums[i];
	return 0;
}

void main()
{
	threadHandles = new HANDLE[NUMTHREADS + 1];
	InitializeCriticalSection(&countCS);
	sums = new double[NUMTHREADS];

	for(int i=0; i<NUMTHREADS;i++)
	{
		int * threadIdPtr = new int;
		*threadIdPtr = i;
		threadHandles[i] = CreateThread(NULL, 0, threadProc, threadIdPtr, CREATE_SUSPENDED, NULL);
	}
	threadHandles[NUMTHREADS] = CreateThread(NULL, 0, masterThreadProc, NULL, 0, NULL);
	
	printf("Count of ln(1 + x) Mercator's series members is %d\n",SERIES_MEMBER_COUNT);
	printf("Argument value of x is %f\n", (double)x);

	WaitForMultipleObjects(NUMTHREADS+1,threadHandles,TRUE,INFINITE);

	for(int i=0; i<NUMTHREADS+1; i++ ) CloseHandle(threadHandles[i]);

	delete threadHandles;
	DeleteCriticalSection(&countCS);
	delete sums;

	printf("Result is %10.8f\n", res);
	printf("By function call ln(1 + %f) = %10.8f\n",x, log(1+x));
	printf("Press any key ... ");
	_getch();
}