#include "data.h"

_declspec (dllexport) int iexp (int x, unsigned n)
{
	y = 1;
	p = x;
	while(1) {
		if (n & 1) y = p*y;
		n = n >> 1;
		if (n == 0) return y;
		p = p*p;
	}
}