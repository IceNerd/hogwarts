#include <windows.h>
#include <stdio.h>

FILE *fd; 
int TotalEvenWords = 0, TotalOddWords = 0, TotalWords = 0;

int GetNextLine(FILE *f, char *Line)
{ 
	 
	 if (fgets(Line, 132, f)==NULL) if (feof(f))return EOF; else return 1;
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
	return (Word_Count);     // encode two return values
}

DWORD WINAPI CountWords() 
{ 
   BOOL bDone = FALSE ;
   char inLine[132];

	while (!bDone)
	{
      bDone = (GetNextLine(fd, inLine) == EOF);
	  if (!bDone){
           TotalWords += GetWordAndLetterCount(inLine) ;
         }
   }
	return 0;
}

void main()
{
   fopen_s(&fd, "InFile1.txt", "r"); // Open file for read

   CountWords();

   fclose(fd);

    printf("Total Words = %8d\n\n", TotalWords);
    printf("Total Even Words = %7d\nTotal Odd Words  = %7d\n", TotalEvenWords, TotalOddWords);

}