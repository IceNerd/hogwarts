#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include <stdio.h>
#include <time.h>
#include <malloc.h>

#define NUM_PROCS 2 
#define NUM 512
#define BLOCK_SIZE ((unsigned) 16)

double **a;


double **b;

double  **c;

double  **d;

#ifdef WIN32
HANDLE hThread[NUM_PROCS];
#else
pthread_t hThread[NUM_PROCS];
pthread_attr_t  thread_attribute;
#endif

void multiply_orig()
{
	unsigned int i,j,k;
	

	for(i=0;i<NUM;i++) {
	  for(j=0;j<NUM;j++) {
		d[i][j] = 0.0;
		for(k=0;k<NUM;k++) {
			d[i][j] += a[i][k]*b[k][j];
		  }
			
		}
	}

	
}

#ifdef WIN32
DWORD WINAPI multiply_mt_core(void* s)
#else
void multiply_mt_core(void* s)
#endif
{
	unsigned int i, j, k;
	unsigned int slice ;
	unsigned int from ;
	unsigned int to ;
	double	tmp;

	slice = (unsigned int) s;
	from = (slice*NUM)/NUM_PROCS;
	to = ((slice+1)*NUM)/NUM_PROCS;
	for(i=from; i<to; i++)
	{
		for(j=0; j<NUM; j++) {
			tmp = 0.0;
			for(k=0; k<NUM; k++)
				tmp += a[i][k]*b[k][j];
		}
		c[i][j] = tmp;
	}

#ifdef WIN32
	return 0;
#else
	printf("exit core\n");
	pthread_exit( (void *)0 );
#endif
}

void multiply_mt()
{
	int status, rc;
	unsigned int i;
#ifndef WIN32
	pthread_attr_init( &thread_attribute );
	pthread_attr_setdetachstate(&thread_attribute, PTHREAD_CREATE_JOINABLE);
#endif
	
	for( i=0; i < NUM_PROCS; i++ )
	{
#ifdef WIN32
		hThread[i] = CreateThread( NULL, 0, multiply_mt_core, (void *)i, 0, 0 );
#else
		pthread_create( &hThread[i], &thread_attribute, (void *)multiply_mt_core , (void *)i );
#endif
	}
#ifdef WIN32
	WaitForMultipleObjects( NUM_PROCS, hThread, TRUE, INFINITE );
#else
	for( i = 0; i < NUM_PROCS; i++ )
	{
		printf("Enter join\n");
		rc = pthread_join(hThread[i], (void **)&status);
		printf("Exit join\n");

	}
	pthread_attr_destroy( &thread_attribute );
	printf("Done\n");
#endif
}

//routine to initialize an array with data
void init_arr(double row, double col, double off, double ** output)
{
	int i,j;

	for (i=0; i< NUM;i++) {
		for (j=0; j<NUM;j++) {
			output[i][j] = row*i+col*j+off;
	
		}
	}
}

double ** allocate_matrix( unsigned int size )
{
	double ** tmp;
	unsigned int i;
	tmp = ( double ** ) malloc ( sizeof (double**) * size );
	tmp[0] = malloc ( sizeof (double) * size * (size ) );  //tom remove the +1 and you will see
															  //a lot of L2 cache misses and probably
															  //64k aliasing conflicts too
	for ( i = 1; i < size; i++ )
	{
		tmp[i] = tmp[0] +  (size) * i;
	}

	return tmp;
}

int check( )
{
	unsigned i, j;
	for ( i= 0; i < NUM; i++ )
		for ( j= 0; j < NUM; j++ )	
		{
			if ( c[i][j] != d[i][j] )
			{
				return 1;
			}
		}
	return 0;
}

void free_matrix( double ** in )
{
	free( in[0]);
	free( in );

}

main()
{
	clock_t start, stop;
	a = allocate_matrix( NUM );
	b = allocate_matrix( NUM );
	c = allocate_matrix( NUM );
	d = allocate_matrix( NUM );
	printf("Address a = %x\n", a );
	printf("Address b = %x\n", b );
	printf("Address c = %x\n", c );

// initialize the arrays with data
	init_arr(3,-2,1,a);
	init_arr(-2,1,3,b);

	//start timing the matrix multiply code
	start = clock();
	multiply_mt();
	stop = clock();

// print elapsed time
	printf("Elapsed time = %lf seconds\n",
    		((double)(stop - start)) / CLOCKS_PER_SEC);
	free_matrix( a );
	free_matrix( b );
	free_matrix( c );
	free_matrix( d );


}


