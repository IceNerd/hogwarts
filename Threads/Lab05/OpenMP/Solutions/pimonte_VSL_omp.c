#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//VSL Variables
#include "mkl_vsl.h"
#define BRNG    VSL_BRNG_MCG31
#define METHOD  0
#define BLOCK_SIZE 500


int main(){
  unsigned int iter=200000000; 
  int i,j;
  double x, y;
  double dUnderCurve=0.0;
  double pi=0.0;


  VSLStreamStatePtr stream;  //You need one stream for each thread

  double end_time,start_time;

  start_time=clock();
#pragma omp parallel private(stream,x,y,i) reduction(+:dUnderCurve)
  {
   double r[BLOCK_SIZE*2];  //Careful!!! 
  	//you need a private copy of whole array for each thread  

    vslNewStream( &stream, BRNG,  (int)clock() );   
#pragma omp for 
    for(j=0;j<iter/BLOCK_SIZE;j++) {
                              
        vdRngUniform( METHOD, stream, BLOCK_SIZE*2, r, 0.0, 1.0 );   
		//Create random numbers into array r
        
        for (i=0;i<BLOCK_SIZE;i++) {
            x=r[i];                     //X Coordinate
            y=r[i+BLOCK_SIZE];          //Y Coordinate
            if (x*x + y*y <= 1.0) {	//is distance from Origin under Curve 
                dUnderCurve++;
            }
        } 
    }
    
    vslDeleteStream( &stream );
  }
  pi = dUnderCurve / (double) iter * 4 ;

  end_time=clock();

  printf ("pi = %10.9f\n", pi);
  printf ("Seconds = %10.9f\n",(double)((end_time-start_time)/1000.0));
  
  return 0;
}
