#include "Square.h"
#include <iostream>
using std::ostream;

/**************************************************************
*   Entry:  Square is one of 5 different squares
*
*    Exit:  Square will output to the screen.
*
* Purpose:  To output square / status of square to the screen.
*
***************************************************************/
ostream& operator<<(ostream& output, const cSquare& outme)
{
	if(outme.flag == true)
	{
		output<<"*";
	}
	else if(outme.hidden == true)
	{
		output<<"X";
	}
	else
	{
		if(outme.identity == 0)
		{
			output<<" ";
		}
		else if(outme.identity == -1)
		{
			output<<"@";
		}
		else
		{
			output<<outme.identity;
		}
	}
	return output;
}


/**************************************************************
*   Entry:  n/a
*
*    Exit:  Identity of the square will be set to given value.
*
* Purpose:  Used in population.  Determining the playing field
*		before the game starts.
*
***************************************************************/
void cSquare::setIdentity(const int new_ident)
{
	identity = new_ident;
	hidden = true;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  returns the identity of the square.
*
***************************************************************/
int cSquare::getIdentity()
{
	return identity;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  Set the hidden status to false.
*
***************************************************************/
void cSquare::show()
{
	hidden = false;
}

/**************************************************************
*   Entry:  Identity is not a mine.
*
*    Exit:  Identity is either incremented or left alone.
*
* Purpose:  determine how many mines are adjacent to a square.
*
***************************************************************/
void cSquare::operator++()
{
	if(identity != -1)
	{
		identity++;
	}
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  Return the visibility status of the square.
*
***************************************************************/
bool cSquare::visible()
{
	return hidden;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  flag will be set to opposite value.  marked/unmarked
*
* Purpose:  To mark/unmark squares to win the game.
*
***************************************************************/
void cSquare::mark()
{
	flag = !flag;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  return the marked status of the square.
*
***************************************************************/
bool cSquare::getMark()
{
	return flag;
}



/**************************************************************
*   Entry:  Data is at least initialized
*
*    Exit:  Data will be copied
*
* Purpose:  to copy one square to target square.
*
***************************************************************/
cSquare& cSquare::operator=(const cSquare& copyme)
{
	hidden = copyme.hidden;
	identity = copyme.identity;
	return *this;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  cSquare object is initialized
*
* Purpose:  Initialize the cSquare object
*
***************************************************************/
cSquare::cSquare()
		:hidden(true), identity(0), flag(false)
{
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  cSquare object will be initialized
*
* Purpose:  To initialize the cSquare object
*
***************************************************************/
cSquare::cSquare(const cSquare& copyme)
{
	*this = copyme;
}

/**************************************************************
*   Entry:  n/a
*
*    Exit:  n/a
*
* Purpose:  Destructs the cSquare object
*
***************************************************************/
cSquare::~cSquare()
{
}