/************************************************************************
* Class: -
*
* Constructors:
*	cFCGame()
*		-Handles instatiation of the class.  This will set the size of
*			the arrays.
*
*	~cFCGame()
*		-Handles destruction of the class.  No dynamic memory to destroy
*			manually.
*
* Mutators:
*	void Shuffle_Deck()
*		-Shuffles the cards using a pseudo random algorithm.
*
*	void Restart()
*		-Resets the state of the game.
*
*	bool Move_Card(int, int)
*		-Moves a card from one place to another.  Interfaces to the user
*			for the specifics of the move.
*
* Methods:	
*	void Game_Start()
*		-Starts the game.  This handles the basis of interface to the
*			user.  Calls Restart, Move_Card and Shuffle.
*
*	void Display_All();
*		-Displays the contents of our arrays in table layout.
*	
*************************************************************************/

#ifndef CFCGAME_H
#define CFCGAME_H

#include "cRandom.h"
#include "cCard.h"
#include "tStack.h"
#include "tArray.h"
#include <conio.h>

class cFCGame
{public:
	cFCGame();
	~cFCGame();

	void Game_Start();

private:
	cRandom Dealer;

	tStack< cCard* > deck;
	void Shuffle_Deck();

	tArray< cCard* > freecells;
	tArray< tStack< cCard* > > homecells;
	tArray< tStack< cCard* > > table;

	void Restart();
	void Display_All();
	bool Move_Card(int, int);

};

#endif