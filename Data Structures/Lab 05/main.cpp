/*************************************************************************
* Author:					Alberto Martinez
* Date Created:				05.19.2004
* Last Modification Date:	05.21.2004
* Lab Number:				CST 211 Lab 5
* Filename:					main.cpp
*
* Overview:
*	This program will determine the shortest path on a graph from any
*		given starting and ending point.
*
* Input:
*	Simple keyboard user interface
*
* Output:
*	The path from one point to the other
*	
*************************************************************************/

#include<conio.h>
#include<iostream>
using std::cout;
using std::cin;
#include<fstream>
using std::ifstream;

#include "cSPath.h"

int main()
{
	bool done(false);
	int choice1(0);
	int choice2(0);
	cSPath Shortest_Path("lab05.txt");

	while(!done)
	{
		system("cls");
		Shortest_Path.PrintPlaces();
		cout<<"Start at:  ";
		cin>>choice1;
		cout<<"End at:  ";
		cin>>choice2;
		system("cls");
		Shortest_Path.Short_Path(choice1, choice2);
		cout<<"Again? Y or N\n";
		choice1 = getch();
		if(choice1 == 110 || choice1 == 78)
		{
			done = true;
		}
	}

}