/************************************************************************
* Class:	cDTNode
*
* Constructors:	
*	cDTNode(const String&, const String&, const bool&);
*
* Mutators:
*	
*
* Methods:
*	void Display(const int&);
*************************************************************************/

#ifndef CDTNODE_H
#define CDTNODE_H

#include "tLList.h"
#include "String.h"
class cDirTree;

class cDTNode
{
friend class cDirTree;

public:
	~cDTNode();
	void Display(const int&);

private:
	cDTNode(const String&, const String&, const bool&);

	tLList< cDTNode* > m_children;
	String m_name;
	bool m_isdir;

};

#endif