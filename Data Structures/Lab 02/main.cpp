/*************************************************************************
* Author:					Alberto Martinez
* Date Created:				04.16.2004
* Last Modification Date:	04.19.2004
* Lab Number:				CST 211 Lab 2
* Filename:					main.cpp
*
* Overview:
*	This program is the game of Freecell.  It uses a standard deck of
*		52 cards.  The beginning of the game places all the cards on
*		the table.  The table is 8 stacks of cards.  The object of the
*		game is to get all the cards in the home cells, which are 4
*		stacks of cards on the top of the board, in order from ace to
*		king.  On can move cards around the table, however, the rule is
*		that the color must be opposite and the rank must be consecutive
*		from higher to smaller.
*
* Input:
*	Single keyboard strokes will be accepted.  This will allow the user
*		to make several different decisions about the next move.
*
* Output:
*	Simple ASCII menus and ASCII drawn field.
*	
*************************************************************************/

#include <iostream>
using std::cout;

#include "cError.h"
#include "cCard.h"
#include "cFCGame.h"

int main()
{
	try
	{
		cFCGame FreeCell;
		FreeCell.Game_Start();
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}


	return 0;
}