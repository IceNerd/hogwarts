#include <stdio.h>
#include "../Library/Library.h"

void main()
{
int i; 
char gc[5];

    printf("Four-bit Gray Code\n\n");
	for (i = -2; i < 19; i++) {
		if (!gray_code4(i,gc)) printf("%2d  %s\n",i, gc);
	}

	printf("\n\nInteger exponents\n\n");
	printf("5 ^ 4   = %12d\n\n", iexp(5,4));
	printf("27 ^ 4  = %12d\n\n", iexp(27,4));
	printf("3 ^ 18  = %12d\n\n", iexp(3,18));
	printf("7 ^ 2   = %12d\n\n", iexp(7,2));
	printf("4 ^ 12  = %12d\n\n", iexp(4,12));

	printf("\nInteger base10 logarithms\n\n");
	printf("log10(      625) = %2d\n\n", ilog10(625));
	printf("log10(   531441) = %2d\n\n", ilog10(531441));
	printf("log10(387420489) = %2d\n\n", ilog10(387420489));
	printf("log10(       49) = %2d\n\n", ilog10(49));
	printf("log10( 16777216) = %2d\n\n", ilog10(16777216));
	
}