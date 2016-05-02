#include "data.h"

static int nlz(unsigned x)
{
	int t;
	
	t = 0;
	p = x;
L:  if (x < 0) return t;
	if (p == 0) return 32-t;
	t = t + 1;
	x = x << 1;
	p = p >> 1;
	goto L;
}

_declspec (dllexport) int ilog10(unsigned x) 
{
	y = table1[nlz(x)];
	y = y - ((x - table2[y]) >> 31);
	return y;
}
