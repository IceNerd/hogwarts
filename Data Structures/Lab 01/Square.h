/************************************************************************
* Class: cSquare
*
* Constructors:	
*	cSquare();
*		-Square set as hidden, blank and unmarked
*	cSquare(const cSquare&);
*		-Copy Constructor
*
* Mutators:
*	void setIdentity(const int);
*		-Sets identity to whatever. Also sets visibility to false.
*	void show();
*		-Sets the square to be visible
*	void mark();
*		-Marks or unMarks the square
*	void operator++();
*		-Increments the identity if not a mine.
*	cSquare& operator=(const cSquare&);
*		-Copys all data.
*
* Methods:	
*	int getIdentity();
*		-Returns the identity.
*	bool visible();
*		-Returns the visibility
*	bool getMark();	
*		-Returns if square is marked.
*	
*************************************************************************/

#ifndef SQUARE_H
#define SQUARE_H

#include<iostream>
using std::ostream;

class cSquare
{
	friend ostream& operator<<(ostream& output, const cSquare& outme);

public:
	cSquare();
	~cSquare();
	cSquare(const cSquare&);

	//Mutators
	void setIdentity(const int);
	void show();
	void mark();
	void operator++();
	cSquare& operator=(const cSquare&);
	
	//Other Methods
	int getIdentity();
	bool visible();
	bool getMark();	

private:
	bool hidden;
	int identity;
	bool flag;

};


#endif