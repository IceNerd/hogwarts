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
#include "IterClass.h"

int main()
{
	cLList< int > Bob_LL;
	IterClass< int > George_It(Bob_LL);
	cout<<"Add Before Cursor\n";
	for(int i = 0; i < 10; i++)
	{
		George_It.addBefore(i);
	}
	George_It.Reset();
	
	while(!George_It)
	{
		cout<<*George_It<<"\n";
		if(George_It.IsDone())
		{
			cout << "End of List\n";
		}
		++George_It;
	}
	cout << "\n";
	George_It.Reset();
	cout<<"Add After Cursor\n";
	for(int i = 10; i < 21; i++)
	{
		George_It.addAfter(i);
	}

	while(!George_It)	
	{
		cout << *George_It << "\n";
		if(George_It.IsDone())
		{
			cout << "End of List\n";
		}
		++George_It;
	}

	return 0;
}