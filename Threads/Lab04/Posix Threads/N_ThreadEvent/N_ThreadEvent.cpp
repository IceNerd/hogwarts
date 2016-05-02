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
#include <pthread.h>

#define NUMTHREADS 4
#define SERIES_MEMBER_COUNT 10000

pthread_t masterThreadHandle;
pthread_t threadHandles[NUMTHREADS + 1];
pthread_mutex_t Mutex;
pthread_mutex_t NumMutex;
pthread_cond_t eventHandle;

int ThreadsComplete = 0;

double* sums;
double x = 1.0;
double res = 0.0;

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

void* threadProc(void* par)
{
	int threadIndex = *((int *)par);
	
	printf("Thread id = %d\n",threadIndex);

	sums[threadIndex] = 0;

	for(int i=threadIndex; i<SERIES_MEMBER_COUNT;i+=NUMTHREADS)
		sums[threadIndex] += getMember(i+1, x);

	pthread_mutex_lock(&NumMutex);
	ThreadsComplete++;
	pthread_mutex_unlock(&NumMutex);
	if( ThreadsComplete >= NUMTHREADS )
	{
		pthread_cond_signal(&eventHandle);
	}
	delete par;
	return 0;
}

void* masterThreadProc(void* par)
{	
	//for( int i=0; i < NUMTHREADS; i++ )
	//{
	//	pthread_join(threadHandles[i], NULL);
	//}

	pthread_mutex_lock(&Mutex);
	pthread_cond_wait(&eventHandle, &Mutex);
	pthread_mutex_unlock(&Mutex);
//	WaitForMultipleObjects(NUMTHREADS, eventHandles, TRUE,INFINITE);

	res = 0;
	for( int i = 0; i < NUMTHREADS; i++ )
		res += sums[i];

	return 0;
}

void main()
{
	sums = new double[NUMTHREADS];
	int iErr(0);
	pthread_mutex_init(&Mutex, NULL);
	pthread_mutex_init(&NumMutex, NULL);
	eventHandle = PTHREAD_COND_INITIALIZER;

	for( int i = 0; i < NUMTHREADS; i++ )
	{
		int * threadIdPtr = new int;
		*threadIdPtr = i;
		iErr = pthread_create(&threadHandles[i], NULL, threadProc, threadIdPtr);
		if( iErr )
		{
			printf("ERROR: Return code from pthread_create() is %d\n", iErr);
		}
		//eventHandles[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	iErr = pthread_create(&threadHandles[NUMTHREADS], NULL, masterThreadProc, NULL);

	printf("Count of ln(1 + x) Mercator's series members is %d\n",SERIES_MEMBER_COUNT);
	printf("Argument value is %f\n", (double)x);

	pthread_join(threadHandles[NUMTHREADS], NULL);

	delete sums;

	printf("Result is %f\n", (double)res);
	printf("Press any key ... ");
	_getch();
}