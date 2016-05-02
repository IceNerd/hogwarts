/* compute the potential energy of a collection of */
/* particles interacting via pairwise potential    */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
 
// Set number of particles and iterations low for Thread Checker

#define NPARTS 10
#define NITER 11
#define DIMS 3
#define NUM_THREADS 2
 
int rand( void );
DWORD WINAPI computePot(LPVOID);
void initPositions(void);
void updatePositions(void);
 
double r[DIMS][NPARTS];
int    bounds[2][NUM_THREADS];
double pot;
double distx, disty, distz, dist;

int main() {
   int i, j;
   HANDLE tHandle[NUM_THREADS];
   int    tNum[NUM_THREADS];

   for (i=0; i<NUM_THREADS; i++) {
      bounds[0][i] =    i  * (NPARTS/NUM_THREADS);
      bounds[1][i] = (i+1) * (NPARTS/NUM_THREADS);
   }
   bounds[1][NUM_THREADS-1] = NPARTS;

   initPositions();
   updatePositions();
 
   for( i=0; i<NITER; i++ ) {
      pot = 0.0;
      for (j=0; j<NUM_THREADS; j++) {
         tNum[j] = j;
         tHandle[j] = CreateThread(NULL, 0, computePot, &tNum[j], 0, NULL);
      }
      WaitForMultipleObjects(NUM_THREADS, tHandle, TRUE, INFINITE);

      if (i%10 == 0) printf("%5d: Potential: %10.3f\n", i, pot);
      updatePositions();
   }
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
}
 
 
DWORD WINAPI computePot(LPVOID pArg) {
   int i, j, start, end, tid;

   tid = *(int *)pArg;
   start = bounds[0][tid];
   end   = bounds[1][tid];
 
   for( i=start; i<end; i++ ) {
      for( j=0; j<i-1; j++ ) {
        distx = pow( (r[0][j] - r[0][i]), 2 );
        disty = pow( (r[1][j] - r[1][i]), 2 );
        distz = pow( (r[2][j] - r[2][i]), 2 );
        dist = sqrt( distx + disty + distz );
        pot += 1.0 / dist;
      }
   }
   return 0;
}
