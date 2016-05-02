/*
  This program illustrates the potential for deadlock in a bad
  locking hierarchy. It is possible for one thread to lock both
  critical sections and avoid deadlock. However, concurrent
  programs that rely on a particular order-of-execution without
  enforcing that order will eventually fail.

  This program also contains a data race that illustrates 
  another flaw in this locking hierarchy - the critical sections 
  are not linked to any particular data.

  Copyright 2002 Intel Corporation, All rights reserved.
*/



#include <stdio.h>
#include <windows.h>

CRITICAL_SECTION cs0, cs1;

int globalX = 0;
int globalY = 0;


DWORD WINAPI work0 (void *arg)
{
	Sleep(5000);
	EnterCriticalSection( &cs0 );
		globalX++;
		EnterCriticalSection( &cs1 );
			globalY++;
		LeaveCriticalSection( &cs1 ); 
	LeaveCriticalSection( &cs0 ); 

	return 0;
}


DWORD WINAPI work1 (void *arg)
{
	EnterCriticalSection (&cs1);
		globalX++;
		EnterCriticalSection (&cs0);
			globalY++;
		LeaveCriticalSection (&cs0); 
	LeaveCriticalSection (&cs1); 

	return 0;
}


int main (int argc, char *argv[])
{
	HANDLE h[2];
	DWORD  rc;

	InitializeCriticalSection (&cs0);
	InitializeCriticalSection (&cs1);

	printf ("START\n");

	h[0] = CreateThread (0, 0, work0, NULL, 0, NULL);
	h[1] = CreateThread (0, 0, work1, NULL, 0, NULL);


	printf ("TOTAL = (%d,%d)\n", globalX, globalY);
	rc = WaitForMultipleObjects (2, h, TRUE, INFINITE);

	printf ("STOP\n");

	DeleteCriticalSection (&cs0);
	DeleteCriticalSection (&cs1);

}
