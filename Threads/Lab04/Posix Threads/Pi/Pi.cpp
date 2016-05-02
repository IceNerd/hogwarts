#include <pthread.h>
#include <stdio.h>

//thread stuff
#define NUM_THREADS 2
pthread_mutex_t Mutex;

//calculation stuff
static long num_steps=100000; 
struct stCalcVals* calcs;
double step, pi;

struct stCalcVals
{
	long    strtVal;
	long    stpVal;
	double	sum;
};

void* CalcPartOf(void* pArg) 
{
	double x = 0.0;

	calcs = (struct stCalcVals*) pArg;

	for( long i = calcs->strtVal; i < calcs->stpVal; ++i )
	{
		x = (i+0.5)*step;
		calcs->sum = calcs->sum + 4.0/(1.0 + x*x);
	}
	pthread_mutex_lock(&Mutex);
    pi += step * calcs->sum;
	pthread_mutex_unlock(&Mutex);
	return 0;
}


void main()
{
	// initialize thread stuff
	int iErr(0);
	pthread_t hThreads[NUM_THREADS];
	pthread_mutex_init(&Mutex, NULL);

	// initialize calculation stuff
	double sum = 0.0;
	long stepInc = num_steps/NUM_THREADS;
	long stepCtr = 0;
	struct stCalcVals calcVals[NUM_THREADS];

	step = 1.0/(double) num_steps;

	for( int i = 0; i < NUM_THREADS; ++i )
	{
		calcVals[i].strtVal		= stepCtr;
		stepCtr					+= stepInc;
		calcVals[i].stpVal		= stepCtr;
		calcVals[i].sum			= 0.0;
	}
			
	for( int i = 0; i < NUM_THREADS; ++i )
	{
		// Create threads
		iErr = pthread_create(&hThreads[i], NULL, CalcPartOf, &calcVals[i]);
		if( iErr )
		{
			printf("ERROR: Return code from pthread_create() is %d\n", iErr);
		}
	}

	for( int i = 0; i < NUM_THREADS; ++i )
	{
		pthread_join(hThreads[i], NULL);
	}

	printf("Pi = %12.9f\n",pi);

}
