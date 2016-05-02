#include <stdio.h>

int main() 
{
	#pragma omp parallel
	{
		int i;
		printf("Hello World\n");
		#pragma omp parallel for
		for( i = 0; i < 600; i++)
			printf("Iter:%d\n",i);
	}

		printf("GoodBye World\n");
}