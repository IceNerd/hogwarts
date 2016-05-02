#include "multiply_d.h"
#include <stdio.h>
// matrix multiply routine
void multiply_d(double a[][NUM], double  b[][NUM], double  c[][NUM])
{
	int i,j,k;
	double temp;

	temp = 0.0;
	for(i=0;i<NUM;i++) {
	  for(j=0;j<NUM;j++) {
		for(k=0;k<NUM;k++) {
			temp = temp + a[i][k] * b[k][j];
		  }
			c[i][j] = temp;
			temp = 0;
		}
	}

	
}


void multiply_b(double a[][NUM], double  b[][NUM], double  c[][NUM])
{
	int i,j,k;


	for(i=0;i<NUM;i++) {
	  for(j=0;j<NUM;j++) {
		for(k=0;k<NUM;k++) {
			c[i][k] = c[i][k] + a[i][j] * b[j][k];
		  }
		}
	}
}