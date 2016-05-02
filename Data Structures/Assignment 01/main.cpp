/* *******************************************************************
*   Program Identification:
*
*   Author:			Alberto Martinez
*   Date Created:	March 30, 2004
*   Date Modified:	March 30, 2004
*
*		Assignment:		Assignment 01
*		Compiler:		MS Visual Studio .Net 2003
*		Operating Sys:	Windows XP Pro V2002 SP1
*
*********************************************************************/

#include <iostream>
using std::cout;

#include <conio.h>

#include "Error.h"
#include "String.h"
#include "Array.h"

int main()
{
	//Instantiate our arrays
		Array<int> intArray(10, -5);
		Array<String> strArray(5, 0);
		Array<double> dubArray(20, 5);
	
	cout<<"--- Filling integer array with values ---\nIndex  |  Data\n";
	for(int i = intArray.getBase() - 2; i < intArray.getBase() + intArray.getLength() + 2; i++)
	{
		try
		{
			intArray[i] = i;
			cout<<i<<":\t"<<intArray[i]<<"\n";
		}
		catch(EXCEPTION& uhoh)
		{
			cout<<uhoh;
		}
	}
	cout<<"Press Any Key to Continue";
	getch();
	system("cls");

	cout<<"--- Filling String array with values ---\nIndex  |  Data\n";
	for(int i = strArray.getBase() - 2; i < strArray.getBase() + strArray.getLength() + 2; i++)
	{
		try
		{
			strArray[i] = "Array";
			cout<<i<<":\t"<<strArray[i]<<"\n";
		}
		catch(EXCEPTION& uhoh)
		{
			cout<<uhoh;
		}
	}
	cout<<"Press Any Key to Continue";
	getch();
	system("cls");

	cout<<"--- Filling double array with values ---\nIndex  |  Data\n";
	for(int i = dubArray.getBase() - 2; i < dubArray.getBase() + dubArray.getLength() + 2; i++)
	{
		try
		{
			dubArray[i] = i + 0.33;
			cout<<i<<":\t"<<dubArray[i]<<"\n";
		}
		catch(EXCEPTION& uhoh)
		{
			cout<<uhoh;
		}
	}
	cout<<"Press Any Key to Continue";
	getch();
	system("cls");

	cout<<"--- Changing the length of the double array to: "<<10<<" ---\n"
		<<"--- Changing the base of the double array to: "<<-34<<" ---\nIndex  |  Data\n";
	dubArray.setLength(10);
	dubArray.setBase(-34);
	for(int i = dubArray.getBase() - 2; i < dubArray.getBase() + dubArray.getLength() + 2; i++)
	{
		try
		{
			cout<<i<<":\t"<<dubArray[i]<<"\n";
		}
		catch(EXCEPTION& uhoh)
		{
			cout<<uhoh;
		}
	}
	cout<<"Press Any Key to Continue";
	getch();
	system("cls");

	cout<<"Done\n";
	return 0;
}