#include <windows.h>
#include <stdio.h>

#define MAX_SEM_COUNT 1

HANDLE hSemaphore;
FILE *fd; 
int TotalEvenWords = 0, TotalOddWords = 0, TotalWords = 0;

const int NUMTHREADS = 4;

int GetNextLine(FILE *f, char *Line)
{ 	 
	 if (fgets(Line, 132, f)==NULL) 
		if (feof(f))
			return EOF; 

	 return 1;
}

int GetWordAndLetterCount(char *Line)
{
	int Word_Count = 0, Letter_Count = 0;
	for (int i=0;i<132;i++)
	{
		if ((Line[i]!=' ')&&(Line[i]!=0)&&(Line[i]!='\n')) Letter_Count++; 
		else {
			if (Letter_Count % 2) {
				TotalOddWords++; 
                Word_Count++;
				Letter_Count = 0;
			}
			else {
				TotalEvenWords++;
				Word_Count++;
				Letter_Count = 0;
			}
			if (Line[i]==0) break;
		}
	}
	return (Word_Count);     
}


DWORD WINAPI CountWords(LPVOID arg) 
{
	DWORD dwWait;
	BOOL bDone = FALSE;
	char inLine[132];

	while( !bDone )
	{
        switch( WaitForSingleObject( hSemaphore, 0L ) ) 
        { 
            case WAIT_OBJECT_0:
				bDone = (GetNextLine(fd, inLine) == EOF);
				if( !bDone )
				{
					TotalWords += GetWordAndLetterCount(inLine);
				}
                ReleaseSemaphore( hSemaphore, 1, NULL);
			break; 
        }
	}
	return TRUE;
}

void main()
{
	HANDLE hThread[NUMTHREADS];
	hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, NULL);
	
	fopen_s(&fd, "InFile1.txt", "r"); // Open file for read

	for (int i = 0; i < NUMTHREADS; i++)
	{
		hThread[i] = CreateThread(NULL,0,CountWords,NULL,0,NULL);
	}
	WaitForMultipleObjects(NUMTHREADS, hThread, TRUE, INFINITE);

	//clean up
	fclose(fd);
	for (int i = 0; i < NUMTHREADS; i++)
	{
		CloseHandle(hThread[i]);
	}
	CloseHandle(hSemaphore);

	//report
	printf("Total Words = %8d\n\n", TotalWords);
    printf("Total Even Words = %7d\nTotal Odd Words  = %7d\n", TotalEvenWords, TotalOddWords);
}
