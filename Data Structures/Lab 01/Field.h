/************************************************************************
* Class: cField
*
* Constructors:	
*	cField();
*		-Array set to the largest value it will ever be. Game_Over set to
*			false, game is just beginning!
*	cField(const cField&);
*		-Copy constructor for copying field.
*
* Mutators:
*	void Populate(int, int, const int&);
*		-"Populates" the field and places mines.  Increments surrounding
*			squares.
*	void ShowAll();
*		-Makes all squares visible.
*	void Uncover(const int, const int);
*		-Uncovers square.  If blank, uncovers all possible blank and
*			numbered squares.  If a mine, Game is over, you lose.
*	bool GameOver();
*		-Getter for game_over bool.
*	void Mark(int, int);
*		-Toggles whether a square is marked or not.
*
* Methods:		
*	void PrintField();
*		-Displays the entire field.  Hidden squares are hidden.
*	bool Did_I_Win();
*		-Determines if all the mines are marked and returns true for a win
*	cField& operator=(const cField&);
*		-Copys one field to target field.
*************************************************************************/


#ifndef FIELD_H
#define FIELD_H

#include "random.h"
#include "Array2D.h"
#include "Square.h"

class cField
{public:
	cField();
	~cField();
	cField(const cField&);
	cField& operator=(const cField&);

	//Mutators
	void Populate(int, int, const int&);
	void ShowAll();
	void Uncover(const int, const int);
	bool GameOver();
	void Mark(int, int);

	//Other Methods
	void PrintField();
	bool Did_I_Win();

private:
	Random Generator;

	Array2D< cSquare > m_Squares;
	Array2D< int > mine_loc;
	int m_mines;
	bool Game_Over;
};

#endif