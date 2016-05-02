/************************************************************************
* Class: cMorse
*
* Constructors:
*	cMorse(const char*)
*
* Mutators:
*	<none>
*
* Methods:
*	char Decode(const String&)
*	String Encode(const char&)
*
*************************************************************************/

#ifndef CMORSE_H
#define CMORSE_H

#include <fstream>
using std::ifstream;

#include "tLList.h"
#include "tThrTree.h"
#include "tTreeNode.h"
#include "String.h"

class cMorse
{public:
	cMorse(const char*);
	~cMorse();

	char Decode(const String&);
	String Encode(const char&);

private:
	tThrTree< char > CodeTree;
	tLList< tTreeNode< char >* > AlphaList;
};

#endif