/* compute the potential energy of a collection of */
/* particles interacting via pairwise potential    */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
 
#define NPARTS 1000
#define NITER 301
#define DIMS 3
#define NUM_THREADS 2
 
//int rand( void );
DWORD WINAPI tPoolComputePot(LPVOID);
void computePot(int);
void initPositions(void);
void updatePositions(void);
 
double r[DIMS][NPARTS];
int    bounds[2][NUM_THREADS];
double pot;
double gPot[NUM_THREADS];
int done = 0;
HANDLE bSignal[NUM_THREADS];  // signal to begin computation
HANDLE eSignal[NUM_THREADS];  // signal that computation is ended

int main() {
   int i, j;
   HANDLE tHandle[NUM_THREADS];
   int    tNum[NUM_THREADS];

   for (i=0; i<NUM_THREADS; i++) {
      bounds[0][i] =    i  * (NPARTS/NUM_THREADS);
      bounds[1][i] = (i+1) * (NPARTS/NUM_THREADS);
      bSignal[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto-reset
      eSignal[i] = CreateEvent(NULL, FALSE, FALSE, NULL); // auto-reset
   }
   bounds[1][NUM_THREADS-1] = NPARTS;

   for (j=0; j<NUM_THREADS; j++) {
      tNum[j] = j;
      tHandle[j] = CreateThread(NULL, 0, tPoolComputePot, &tNum[j], 0, NULL);
   }

   initPositions();
   updatePositions();
 
   for( i=0; i<NITER; i++ ) {
      WaitForMultipleObjects(NUM_THREADS, eSignal, TRUE, INFINITE);

      pot = 0.0;
      for (j=0; j<NUM_THREADS; j++) {
         pot += gPot[j];
      }
      if (i%10 == 0) printf("%5d: Potential: %10.3f\n", i, pot);
      updatePositions();
   }
   done = 1;
   for (j=0; j<NUM_THREADS; j++)
      SetEvent(bSignal[i]);
   
   WaitForMultipleObjects(NUM_THREADS, tHandle, TRUE, INFINITE);
}
 
 
void initPositions() {
   int i, j;
 
   for( i=0; i<DIMS; i++ )
      for( j=0; j<NPARTS; j++ ) 
         r[i][j] = 0.5 + ( (double) rand() / (double) RAND_MAX );
}
 
 
void updatePositions() {
   int i, j;
 
   for( i=0; i<DIMS; i++ )
      for( j=0; j<NPARTS; j++ )
         r[i][j] -= 0.5 + ( (double) rand() / (double) RAND_MAX );
   for (j=0; j<NUM_THREADS; j++)
      SetEvent(bSignal[j]);
}
 
DWORD WINAPI tPoolComputePot(LPVOID pArg) {
 
   int tid = *(int *)pArg;

   while (!done) {
      WaitForSingleObject(bSignal[tid], INFINITE);
      computePot(tid);
      SetEvent(eSignal[tid]);
   }
   return 0;
}
   

void computePot(int tid) {
   int i, j, start, end;
   double lPot = 0.0;
   double distx, disty, distz, dist;

   start = bounds[0][tid];
   end   = bounds[1][tid];
 
   for( i=start; i<end; i++ ) {
      for( j=0; j<i-1; j++ ) {
        distx = pow( (r[0][j] - r[0][i]), 2 );
        disty = pow( (r[1][j] - r[1][i]), 2 );
        distz = pow( (r[2][j] - r[2][i]), 2 );
        dist = sqrt( distx + disty + distz );
        lPot += 1.0 / dist;
      }
   }
   gPot[tid] = lPot;
}
