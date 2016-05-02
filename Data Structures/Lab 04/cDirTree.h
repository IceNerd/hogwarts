/************************************************************************
* Class: cDirTree
*
* Constructors:	
*	cDirTree(const String&);
*
* Mutators:
*	
*
* Methods:
*	void Display();
*
*************************************************************************/

#ifndef CDIRTREE_H
#define CDIRTREE_H

#include "cDTNode.h"
#include<windows.h>
#include<direct.h>
#include<io.h>

class cDirTree
{public:
	cDirTree(const String&);
	~cDirTree();

	void Display();

private:
	cDTNode* root;

};

#endif