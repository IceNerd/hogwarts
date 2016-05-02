/************************************************************************
* Class: cCard
*
* Constructors:	
*	cCard(int = -1, int = -1)
*		-Constructs a card.  -1 indicates a blank card.
*
*	~cCard()
*		-Destructs the card.
*
* Mutators:
*	cCard& operator=(const cCard&)
*		-Copys a card
*
* Methods:	
*	bool Equal(cCard) const
*		-Comparison for two cards
*
*	int getSuit() const
*		-Returns the suit of a card
*
*	int getRank() const
*		-Returns the rank of a card
*
*	int getColor() const
*		-Returns the color of a card
*	
*************************************************************************/

#ifndef CCARD_H
#define CCARD_H

#include <iostream>
using std::ostream;

class cCard
{
friend ostream& operator<<(ostream&, const cCard&);

public:
	cCard(int = -1, int = -1);
	~cCard();

	bool Equal(cCard) const;
	int getSuit() const;
	int getRank() const;
	int getColor() const;
	cCard& operator=(const cCard&);

private:
	int Suit;
	int Rank;
};


#endif