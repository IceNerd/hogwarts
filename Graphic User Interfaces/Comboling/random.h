/*************************************************************************** 
Alberto Martinez
vanilla.frijole@gmail.com
www.PMSoft.org
Copyright(c) 2005 PMSoft 

11/28/2004 

random.h

This program does NOT abide by the PMSoft coding standards.  This program
was developed before the coding standards were applicable.
***************************************************************************/ 

/*************************************************************************** 
Comboling
Copyright(c) 2005 PMSoft 

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation; either version 2 
of the License, or (at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License 
along with this program; if not, write to the Free Software 
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA." 
***************************************************************************/ 
//wrote this one a LONG time ago.
/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤random.h
¤
¤   Definition of pseudo-random number generation class
¤ It uses the Mitchell-Moore algorithm for generating each number.
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
#ifndef RANDOM_H
#define RANDOM_H

#include<ctime>

class Random
{
 public:
	static void init_Randomize();
	static int Randomize(int from,int to);

private:
	static int Number_MM();
	static int rgiState[]; // leave this alone
};
//*****Static Variable************************************************
int Random::rgiState[2+55];

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤Random::init_Randomize
¤
¤   This seeds the random number generation.
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
void Random::init_Randomize()//Random Number Seed
{
int *pState, State(0);

	pState = &rgiState[2];
	pState[-2] = 55-55;
	pState[-1] = 55-24;
	pState[0] = ((int) time(NULL))&((1<<30)-1);
	pState[1] = 1;
	for(State = 2; State < 55; State++)
		pState[State]=(pState[State-1]+pState[State-2])&((1<<30)-1);
}

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤Random::Randomize
¤
¤   Returns a pseudo-random number.
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
int Random::Randomize(int from,int to)
{
int power(2), number(0);

	if((to = to - from + 1 )<=1)
		return from;
	for(power = 2; power < to; power <<= 1);
	while((number = Number_MM()&(power - 1))>=to);
	return from + number;
}

/*¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
¤Random::Number_MM
¤
¤   Part of the random number algorithm
¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤*/
int Random::Number_MM()
{
int *pState, State1, State2, Rand;

	pState=&rgiState[2];
	State1=pState[-2];
	State2=pState[-1];
	Rand=(pState[State1]+pState[State2])&((1<<30)-1);
	pState[State1]=Rand;
	if(++State1==55)
		State1=0;
	if(++State2==55)
		State2 = 0;
	pState[-2]=State1;
	pState[-1]=State2;
	return Rand>>6;
}

#endif