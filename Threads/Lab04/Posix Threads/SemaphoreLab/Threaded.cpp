#include <windows.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
pthread_mutex_t FileMutex;
pthread_mutex_t WordMutex;

FILE *fd; 
int TotalEvenWords = 0;
int TotalOddWords = 0;
int TotalWords = 0;

int GetNextLine(FILE *f, char *Line)
{
	int iReturn(1);
	 if( fgets(Line, 132, f) == NULL )
	 {
		if (feof(f))
		{
			iReturn = EOF;
		}
	 }

	 return iReturn;
}

int GetWordAndLetterCount( char* Line )
{
	int Word_Count = 0, Letter_Count = 0;
	for( int i = 0; i < 132; ++i )
	{
		if ((Line[i]!=' ')&&(Line[i]!=0)&&(Line[i]!='\n'))
		{
			Letter_Count++;
		}
		else
		{
			if (Letter_Count % 2)
			{
				TotalOddWords++; 
                Word_Count++;
				Letter_Count = 0;
			}
			else
			{
				TotalEvenWords++;
				Word_Count++;
				Letter_Count = 0;
			}
			if (Line[i]==0)
			{
				break;
			}
		}
	}
	return (Word_Count);     
}


void* CountWords(void* pArg) 
{
	bool bDone(false);
	char inLine[132];

	while( !bDone )
	{
		pthread_mutex_lock(&FileMutex);
		bDone = (GetNextLine(fd, inLine) == EOF);
		pthread_mutex_unlock(&FileMutex);
		if( !bDone )
		{
			pthread_mutex_lock(&WordMutex);
			TotalWords += GetWordAndLetterCount(inLine);
			pthread_mutex_unlock(&WordMutex);
		}
	}
	return 0;
}

void main()
{
	int iErr(0);
	pthread_t hThreads[NUM_THREADS];
	pthread_mutex_init(&FileMutex, NULL);
	pthread_mutex_init(&WordMutex, NULL);
	
	fopen_s( &fd, "InFile1.txt", "r" ); // Open file for read

	// create threads
	for (int i = 0; i < NUM_THREADS; i++)
	{
		iErr = pthread_create(&hThreads[i], NULL, CountWords, NULL);
		if( iErr )
		{
			printf("ERROR: Return code from pthread_create() is %d\n", iErr);
		}
	}

	// join threads
	for( int i = 0; i < NUM_THREADS; ++i )
	{
		pthread_join(hThreads[i], NULL);
	}

	//clean up
	fclose(fd);

	//report
	printf("Total Words = %8d\n\n", TotalWords);
    printf("Total Even Words = %7d\nTotal Odd Words  = %7d\n", TotalEvenWords, TotalOddWords);
}
