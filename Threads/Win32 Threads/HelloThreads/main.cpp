#include <stdio.h>
#include <windows.h>
const int numThreads = 4;


DWORD WINAPI helloFunc(LPVOID pArg) 
{ 
	int param;

	param = (*(int*)(pArg));

	printf("Hello Thread #%d\n", param); 
	return 0; 
}

int main() 
{	
	HANDLE hThread[numThreads];
	int thrdCnt[numThreads];

	for (int i = 0; i < numThreads; i++)
	{
		thrdCnt[i] = i;

		hThread[i] = 
			CreateThread(NULL, 0, helloFunc, &thrdCnt[i], 0, NULL );
	}

	WaitForMultipleObjects(numThreads, hThread, TRUE, INFINITE);
	return 0; 
}

