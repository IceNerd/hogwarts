/***********************************************************
* Author:				Alberto Martinez
* Date Created:			04/01/2004
* Last Modification Date:	...
* Lab Number:			CST 211 Assignment 4
* Filename:				main.cpp
*
* Overview:
*	
*
* Input:
*	
*
* Output:
*	
************************************************************/


#include <iostream>
using std::cout;
#include "Error.h"
#include "cLList.h"
#include "String.h"

int main()
{
	cLList<int> Bob;

	try
	{
		cout<<"Insert after...\n";
		for(int i = 0; i < 10; i++)
		{
			Bob.InsertAfter(i, 0);
		}
		cout<<"\nInsert Before...\n";
		for(int i = 0; i < 10; i++)
		{
			Bob.InsertBefore(i, 0);
		}
		Bob.Extract(3);

		cLList< int >George(Bob);

		George.PrintBackwards();
		Bob.PrintBackwards();

		cout<<"\nDONE\n";
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
	return 0;
}