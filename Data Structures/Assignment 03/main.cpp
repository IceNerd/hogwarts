/* *******************************************************************
*   Program Identification:
*
*   Author:			Alberto Martinez
*   Date Created:	March 31, 2004
*   Date Modified:	March 31, 2004
*
*		Assignment:		Assignment 02
*		Compiler:		MS Visual Studio .Net 2003
*		Operating Sys:	Windows XP Pro V2002 SP1
*
*********************************************************************/

#include <iostream>
using std::cout;

#include <conio.h>

#include "Error.h"
#include "String.h"
#include "Array2D.h"

int main()
{

	//Integer array
	cout<<"2 Dimensional Integer Array\n";
	Array2D< int > MyArray(5, 5);

	for(int i = 0; i < MyArray.getRows(); i++)
	{
		for(int j = 0; j < MyArray.getColumns(); j++)
		{
			MyArray[i][j] = i + j;
		}
	}

	cout<<"Copying the array (copy constructor)\n";
	Array2D< int > cpyMyAry(MyArray);
	try
	{
		for(int i = 0; i < cpyMyAry.getRows(); i++)
		{
			cout<<"Row "<<i<<":  ";
			for(int j = 0; j < cpyMyAry.getColumns(); j++)
			{
				cout<<cpyMyAry[i][j]<<"  ";
			}
			cout<<"\n";
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
	cout<<"Press any key to continue";
	getch();
	system("cls");


	//String Array
	cout<<"2 Dimensional String Array\n";
	Array2D< String > MyStrArray(5, 5);

	for(int i = 0; i < MyStrArray.getRows(); i++)
	{
		for(int j = 0; j < MyStrArray.getColumns(); j++)
		{
			MyStrArray[i][j] = "Test";
		}
	}

	cout<<"Copying the array (copy constructor)\n";
	Array2D< String > cpyMyStrAry(MyStrArray);
	try
	{
		for(int i = 0; i < cpyMyStrAry.getRows(); i++)
		{
			cout<<"Row "<<i<<":  ";
			for(int j = 0; j < cpyMyStrAry.getColumns(); j++)
			{
				cout<<cpyMyStrAry[i][j]<<"  ";
			}
			cout<<"\n";
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
	cout<<"Press any key to continue";
	getch();
	system("cls");


	cout<<"Resizing integer array columns to 3\n";
	MyArray.SetColumns(3);
	cout<<"Resizing integer array rows to 3\n";
	MyArray.SetRows(3);
	try
	{
		for(int i = 0; i < MyArray.getRows(); i++)
		{
			cout<<"Row "<<i<<":  ";
			for(int j = 0; j < MyArray.getColumns(); j++)
			{
				cout<<MyArray[i][j]<<"  ";
			}
			cout<<"\n";
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
	cout<<"Press any key to continue";
	getch();
	system("cls");

	cout<<"Resizing integer array columns back to 5\n";
	MyArray.SetColumns(5);
	cout<<"Resizing integer array rows back to 5\n";
	MyArray.SetRows(5);
	try
	{
		for(int i = 0; i < MyArray.getRows(); i++)
		{
			cout<<"Row "<<i<<":  ";
			for(int j = 0; j < MyArray.getColumns(); j++)
			{
				cout<<MyArray[i][j]<<"  ";
			}
			cout<<"\n";
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
	cout<<"Press any key to continue";
	getch();
	system("cls");


	cout<<"Forcing exception to occur with the string class(MyStrArray[100][100])\n";
	try
	{
		cout<<MyStrArray[100][100]<<"\n";
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
	
	cout<<"Forcing exception to occur with the string class(MyStrArray[0][-1])\n";
	try
	{
		cout<<MyStrArray[0][-1]<<"\n";
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
	cout<<"Done\nPress any key to continue";
	getch();
	system("cls");

	return 0;
}