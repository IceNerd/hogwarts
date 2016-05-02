/************************************************************************
* Class: cSPath
*
* Constructors:	
*	cSPath(const String&);
*
* Mutators:
*	cSPNode* KeySearch(const String&);
*
* Methods:
*	void Short_Path(const int&, const int&);
*	void Reset_Distance();
*	void Insert(const String&);
*	void PrintPlaces();
*	int FindIndex(cSPNode*);
*
*************************************************************************/

#ifndef CSPATH_H
#define CSPATH_H

#include "cSPNode.h"
#include "tLList.h"

class cSPath
{public:
	cSPath(const String&);
	~cSPath();

	void Short_Path(const int&, const int&);
	void Reset_Distance();

	void Insert(const String&);
	void PrintPlaces();
	cSPNode* KeySearch(const String&);

private:
	int FindIndex(cSPNode*);
	tLList< cSPNode* > m_verts;

};

#endif