/*************************************************************************
* Author:					Alberto Martinez
* Date Created:				05.28.2004
* Last Modification Date:	05.29.2004
* Lab Number:				CST 211 Lab 6
* Filename:					main.cpp
*
* Overview:
*	This program will make use of various sorts and time them for
*		efficiency.
*
* Input:
*	Simple keyboard user interface
*
* Output:
*	Time the sort took and every 500ths element of the array.
*	
*************************************************************************/

#include "String.h"
#include "tArray.h"
#include "Error.h"
#include "random.h"
#include "time.h"
#include<conio.h>

#include<iostream>
using std::cout;

int main()
{
	tArray<int> Array(10000);
	Random numgen;
	srand(time(0));
	double time;
	clock_t tv1 = 0, tv2 = 0;
	int choice(-1);
	bool done(false);
	numgen.init_Randomize();

	try
	{
		while(!done)
		{
			while( (choice < 0) || (choice > 9) )
			{
				system("cls");
				cout<<"0: Randomize Array\n"
					<<"1: Brute Force Bubble Sort\n"
					<<"2: Flagged Bubble Sort\n"
					<<"3: Selection Sort\n"
					<<"4: Insertion Sort\n"
					<<"5: Shell Sort\n"
					<<"6: Heap Sort\n"
					<<"7: Merge Sort\n"
					<<"8: Quick Sort\n"
					<<"9: Exit\n"
					<<"Please choose one\n";
				choice = getch();
				choice-=48;
			}

			switch(choice)
			{
				case 0:
					system("cls");
					for(int i = 0; i < 10000; i++)
					{
						Array[i] = numgen.Randomize(0, 10000);
					}
				break;
				
				case 1:
					system("cls");
					tv1 = clock();
					Array.Sort_Bubble();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 2:
					system("cls");
					tv1 = clock();
					Array.Sort_F_Bubble();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 3:
					system("cls");
					tv1 = clock();
					Array.Sort_Selection();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 4:
					system("cls");
					tv1 = clock();
					Array.Sort_Insertion();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 5:
					system("cls");
					tv1 = clock();
					Array.Sort_Shell();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 6:
					system("cls");
					tv1 = clock();
					Array.Sort_Heap();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 7:
					system("cls");
					tv1 = clock();
					Array.Sort_Merge();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 8:
					system("cls");
					tv1 = clock();
					Array.Sort_Quick();
					tv2 = clock();
					time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
					cout<<"Time elapsed: "<<time<<"ms\n";
					cout<<"Every 500th element\n";
					for(int i = 0; i < 10000; i+=500)
					{
						cout<<i<<": "<<Array[i]<<"\n";
					}
					cout<<"Press any key to continue\n";
					getch();
				break;

				case 9:
					done = true;
				break;
			}
			choice = -1;
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
}