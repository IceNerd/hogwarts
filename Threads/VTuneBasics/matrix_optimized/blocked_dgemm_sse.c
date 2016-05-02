#include "multiply_d.h"


/*
  In case you're wondering, dgemm stands for Double-precision, GEneral
  Matrix-Matrix multiplication.
*/

/*
  A is M-by-K
  B is K-by-N
  C is M-by-N

  lda is the leading dimension of the matrix (the M of square_dgemm).
*/


void
basic_dgemm_sse2 (
             const double *restrict A, const double *restrict B, double *restrict C)
{
  unsigned i, j, k;


  for (i = 0; i < BLOCK_SIZE; ++i) {
       
       for (j = 0; j < BLOCK_SIZE; ++j) {
           

            double cij = *(C + j*NUM + i);
#pragma vector always
            for (k = 0; k < BLOCK_SIZE; ++k) {
					cij += A[i + k * NUM] * B[ k + j * NUM ];
            }

            *(C + j*NUM + i) = cij;
       }
  }
}


void
do_block_sse2 (
          const double *A, const double *B, double *C,
          const unsigned i, const unsigned j, const unsigned k)
{
 
     basic_dgemm (A + i + k*NUM, B + k + j*NUM, C + i + j*NUM);
}

void
square_dgemm_blocked_sse2 ( 
              const double *A, const double *B, double *C)
{
     
     unsigned bi, bj, bk;

     for (bi = 0; bi < (NUM / BLOCK_SIZE); ++bi) {
          const unsigned i = bi * BLOCK_SIZE;
          
          for (bj = 0; bj < (NUM / BLOCK_SIZE); ++bj) {
               const unsigned j = bj * BLOCK_SIZE;

               for (bk = 0; bk < (NUM / BLOCK_SIZE); ++bk) {
                    const unsigned k = bk * BLOCK_SIZE;
                    
                    do_block (A, B, C, i, j, k);
               }
          }
     }
}

