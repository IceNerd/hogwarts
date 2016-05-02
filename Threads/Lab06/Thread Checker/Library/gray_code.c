#include "data.h"

static void binary_convert4(int n, char *s)
{
	s[0] = (n & 0x08) ? '1' : '0';
	s[1] = (n & 0x04) ? '1' : '0';
	s[2] = (n & 0x02) ? '1' : '0';
	s[3] = (n & 0x01) ? '1' : '0';
	s[4] = '\0';
}

_declspec (dllexport) int gray_code4(int n, char *gc)
{
	if (n >= 0 && n <= 15) {
		G = n ^ (n >> 1);
		binary_convert4(G,gc);
		return 0;
	}
	else return 1;
}
