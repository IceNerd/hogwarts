#include "multiply_d.h"

/*
void
dgemm ( 
              const double *A, const double *B, double *C)
{
  unsigned i, j, k;

  for (i = 0; i < NUM; ++i) {
	   const double *Ai_ = A + i;
       for (j = 0; j < NUM; ++j) {
            
            const double *B_j = B + j*NUM;

            double cij = *(C + j*NUM + i);

            for (k = 0; k < NUM; ++k) {
                 cij += *(Ai_ + k*NUM) * *(B_j + k);
            }

            *(C + j*NUM + i) = cij;
       }
  }
}

*/



void
dgemm ( 
              const double *A, const double *B, double *C)
{
     
     unsigned bi, bj, bk;
	 unsigned l, m, n;

     for (bi = 0; bi < (NUM / BLOCK_SIZE); ++bi) {
          const unsigned i = bi * BLOCK_SIZE;
          
          for (bj = 0; bj < (NUM / BLOCK_SIZE); ++bj) {
               const unsigned j = bj * BLOCK_SIZE;

               for (bk = 0; bk < (NUM / BLOCK_SIZE); ++bk) {
                    const unsigned k = bk * BLOCK_SIZE;
                    
//					basic_dgemm (A + i + k*NUM, B + k + j*NUM, C + i + j*NUM);
					for (l = 0; l < BLOCK_SIZE; ++l) 
					{
						for (m = 0; m < BLOCK_SIZE; ++m) 
						{
							double cij = *(C + m*NUM + l+ i + j*NUM);
							for (n = 0; n < BLOCK_SIZE; ++n) 
							{
									cij += A[l + n * NUM+i + k*NUM] * B[ n + m * NUM + k + j*NUM];
							}
				            *(C + m*NUM + l+ i + j*NUM) = cij;
						}
					}
               }
          }
     }
}

