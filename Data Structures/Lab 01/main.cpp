/***********************************************************
* Author:					Alberto Martinez
* Date Created:				04.07.2004
* Last Modification Date:	04.09.2004
* Lab Number:				CST 211 Lab 1
* Filename:					main.cpp
*
* Overview:
*	This is the game of Minesweeper.  The rules of the game
* are simple.  The user will select a difficulty level and a
* playing field will be displayed respectively.  There are 5
* different types of squares:
*		'X' symbolizes an unknown or "covered" square.
*		' ' symbolizes a blank, "uncovered" square.
*		<number> symbolizes how many mines are around this
*			uncovered blank square.
*		'@' symbolizes a mine.  If you see this then it's
*			probably because you lost  =)
*		'*' symbolizes a marked square.  Mark all of the
*			mines to win the game.
*
* Input:
*	Keyboard.  Menu options will be done with getch() and
*	square selection will be done with cin.
*
* Output:
*	Simple ASCII menus and ASCII drawn field.
*	
************************************************************/


#include <iostream>
using std::cout;
using std::cin;
#include <conio.h>

#include "Field.h"
#include "Error.h"

int main()
{
	cField Mine_Field;
	int choice(0), X(0), Y(0);
	bool Done(false);

	while(!Done)
	{
		choice = 100;
		cout<<"***  Minesweeper  *****\nBy: Alberto Martinez\n\n";
		cout<<"1: Start Beginner Game\n"
			<<"2: Start Intermediate Game\n"
			<<"3: Start EXPERT game\n"
			<<"4: Exit\n"
			<<"What will it be:  ";
		choice = getch();
		while(choice - 48 > 0 && choice - 48 < 5)
		{
			switch(choice - 48)
			{
			case 1:
				Mine_Field.Populate(10, 10, 10);
				break;
			case 2:
				Mine_Field.Populate(16, 16, 40);
				break;
			case 3:
				Mine_Field.Populate(16, 30, 100);
				break;
			case 4:
				Done = true;
				break;
			}
			while(!Mine_Field.GameOver() && !Mine_Field.Did_I_Win())
			{
				choice = 100;
				while(!(choice - 48 > 0 && choice - 48 < 3))
				{
					Mine_Field.PrintField();
					cout<<"1: Uncover Space\n"
						<<"2: Mark Mine\n"
						<<"What will it be cap'n?  ";
					choice = getch();
					cout<<"\n";
				}
				cout<<"X: ";
				cin>>X;
				cout<<"Y: ";
				cin>>Y;
				if(choice - 48 == 1)
				{
					Mine_Field.Uncover(X-1, Y-1);
				}
				else
				{
					Mine_Field.Mark(X-1, Y-1);
				}
				cout<<"done wit choice";

				if(Mine_Field.GameOver())
				{
					Mine_Field.ShowAll();
					Mine_Field.PrintField();
					cout<<"Too bad, try again\n";
					getch();
				}
				if(Mine_Field.Did_I_Win())
				{
					Mine_Field.ShowAll();
					Mine_Field.PrintField();
					cout<<"GREAT JOB!!!  YOU WON!!!\n";
					getch();
				}
				choice = 100;
			}
			system("cls");
		}
	}

	return 0;
}