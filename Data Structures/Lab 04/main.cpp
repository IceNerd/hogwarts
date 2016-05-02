/*************************************************************************
* Author:					Alberto Martinez
* Date Created:				05.10.2004
* Last Modification Date:	05.10.2004
* Lab Number:				CST 211 Lab 4
* Filename:					main.cpp
*
* Overview:
*	This program will load a directory tree with ALL the files and folders
*		contained within the given path.  The path will be brought in
*		through the main function call.
*
* Input:
*	Valid path on a valid drive.
*	example: "c:\"
*
* Output:
*	The names of all files and folders organized to show the relationships.
*
*	ex.
*	/windows         <---  this is a folder
*		boot.ini	<--- these are the files within the folder /windows
*		winbgi.h
*	
*************************************************************************/

#include<iostream>
using std::cout;
#include "cDirTree.h"
#include "Error.h"

int main(int argc, char* argv[])
{
	try
	{
		if(argc == 2)
		{
			cDirTree MyDirTree(argv[1]);
			MyDirTree.Display();
		}
		else
		{
			throw EXCEPTION("int main(int argc, char* argv)^invalid arguments^\n");
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}
}