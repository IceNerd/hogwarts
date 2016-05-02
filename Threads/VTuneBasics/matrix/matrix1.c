#include <stdio.h>
#include <time.h>
#include "multiply_d.h"



static double  a[NUM][NUM];

static double  b[NUM][NUM];

static double  c[NUM][NUM];

//routine to initialize an array with data
void init_arr(double row, double col, double off, double a[][NUM])
{
	int i,j;

	for (i=0; i< NUM;i++) {
		for (j=0; j<NUM;j++) {
			a[i][j] = row*i+col*j+off;
	
		}
	}
}


// routine to print out contents of small arrays
void print_arr(char * name, double array[][NUM])
{
	int i,j;
	
	printf("\n%s\n", name);
	for (i=0;i<NUM;i++){
		for (j=0;j<NUM;j++) {
			printf("%g\t",array[i][j]);
		}
		printf("\n");
	}
}


main()
{
	clock_t start, stop;

	printf("Address a = %d\n", &a );
	printf("Address b = %d\n", &b );
	printf("Address c = %d\n", &c );

// initialize the arrays with data
	init_arr(3,-2,1,a);
	init_arr(-2,1,3,b);

	//start timing the matrix multiply code
	printf("NUM:%d\n",NUM);
	start = clock();
//	multiply_d(b,a,c);
//	square_dgemm( a, b, c );
	dgemm( a, b, c );
//	square_dgemm_blocked_sse2( a, b, c);
	stop = clock();

// print simple test case of data to be sure multiplication is correct
	if (NUM < 5) {
		print_arr("a", a);
		print_arr("b", b);
		print_arr("c", c);
	}

// print elapsed time
	printf("Elapsed time = %lf seconds\n",
    		((double)(stop - start)) / CLOCKS_PER_SEC);


}

