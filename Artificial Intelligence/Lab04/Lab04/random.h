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
	 Random();
	 ~Random();
	 int Randomize( int, int );

private:
	void init_Randomize();
	int Number_MM();
	int rgiState[2+55]; //leave this alone

};

#endif