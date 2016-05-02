#include <windows.h>
#include <stdio.h>

static long num_steps=100000; 
const int	numThreads = 2;
CRITICAL_SECTION calcCS;
struct stCalcVals* calcs;
double step, pi;

struct stCalcVals
{
	long    strtVal;
	long    stpVal;
	double	sum;
};

DWORD WINAPI calcSteps(LPVOID pArg) 
{
	long i;

	double x = 0.0;

	calcs = (struct stCalcVals*) pArg;

	for (i=calcs->strtVal; i < calcs->stpVal; i++)
	{
		x = (i+0.5)*step;
		calcs->sum = calcs->sum + 4.0/(1.0 + x*x);
	}
	EnterCriticalSection(&calcCS);
    pi += step * calcs->sum;
	LeaveCriticalSection(&calcCS);
	return 0;
}


void main()
{  
	InitializeCriticalSection(&calcCS);
	int i;	
	double sum = 0.0;

	long stepInc = num_steps/numThreads;

	long stepCtr = 0;

	struct stCalcVals calcVals[numThreads];

	HANDLE hThread[numThreads];


	step = 1.0/(double) num_steps;

	for (i=0; i<numThreads; i++)
	{
		calcVals[i].strtVal		= stepCtr;
		stepCtr					+= stepInc;
		calcVals[i].stpVal		= stepCtr;
		calcVals[i].sum			= 0.0;
	}
			
	for (i=0; i<numThreads; i++)
	{
		// Create threads
		hThread[i] = CreateThread(NULL, 0, calcSteps, &calcVals[i], 0, NULL );
	}

	WaitForMultipleObjects(numThreads, hThread, TRUE, INFINITE);

	//pi = 0.0;
	//for (i=0; i<numThreads; i++)
	//{
	//	pi += step * calcVals[i].sum;
	//}
	printf("Pi = %12.9f\n",pi);
	DeleteCriticalSection(&calcCS);
}
