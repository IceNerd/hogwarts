#include "cCard.h"

#include <iostream>
using std::cout;

const char suit_text[] = {3, 4, 5, 6};
//One suit does not hold value over another
const char rank_text[] = {'A', '2', '3', '4', '5',
'6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤cCard::<getters>
¤
¤   Gets the suit or rank.
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
int cCard::getSuit() const {return Suit;}
int cCard::getRank()const {return Rank;}

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤cCard::Equal
¤
¤   Compares invoking cCard with inputed cCard.
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
bool cCard::Equal(cCard amIU) const
{
	return (Suit == amIU.Suit)&&(Rank==amIU.Rank) ? true : false;
}

cCard& cCard::operator=(const cCard& copyme)
{
	Suit = copyme.Suit;
	Rank = copyme.Rank;
	return *this;
}

int cCard::getColor() const
{
	if( (Suit == 0) || (Suit == 1) )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤Operator<< overload function for ostream
¤
¤   I did this instead of a seperate display function.  I think this
¤way will be more useful and intuitive.
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
ostream& operator<<(ostream& output, const cCard& output_me)
{

	output<<rank_text[output_me.Rank]<<suit_text[output_me.Suit];
	return output;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
cCard::cCard(int init_Suit, int init_Rank)
	 :Suit(init_Suit), Rank(init_Rank)
{
}

cCard::~cCard()
{
}