/************************************************************************
* Class: cSPNode
*
* Constructors:	
*	cSPNode(const String&);
*
* Mutators:
*	cSPArc* FindArc( const String& );
*
* Methods:
*	void InsertArc(const String&, const int&, cSPNode*);
*
*************************************************************************/

#ifndef CSPNODE_H
#define CSPNODE_H

#include "cSPArc.h"
#include "tLList.h"
#include "String.h"

class cSPNode
{	
friend class cSPath;

public:
	cSPNode(const String&);
	~cSPNode();

	void InsertArc(const String&, const int&, cSPNode*);
	cSPArc* FindArc( const String& );

private:
	tLList< cSPArc* > m_arcs;
	int m_TDist;
	bool visited;
	int predecessor;
	String m_desc;

};

#endif