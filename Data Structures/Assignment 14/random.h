/************************************************************************
* Class: Random
*
* Constructors:	
*
*
* Mutators:
*	
*
* Methods:		
*	
*************************************************************************/

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤random.h
¤
¤   Definition of pseudo-random number generation class
¤ It uses the Mitchell-Moore algorithm for generating each number.
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
#ifndef RANDOM_H
#define RANDOM_H

#include <time.h>

class Random
{
 public:
	void init_Randomize();
	int Randomize(int from,int to);

private:
	int Number_MM();
	static int rgiState[]; // leave this alone
};

#endif