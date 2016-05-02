/************************************************************************
* Class: cRandom
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

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤
¤   Definition of pseudo-random number generation class
¤ It uses the Mitchell-Moore algorithm for generating each number.
¤
¤	Based on code from:		www.planetsourecode.com
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
#ifndef CRANDOM_H
#define CRANDOM_H

#include <time.h>

class cRandom
{
 public:
	void init_Randomize();
	int Randomize(int from,int to);

private:
	int Number_MM();
	static int rgiState[]; // leave this alone
};

#endif