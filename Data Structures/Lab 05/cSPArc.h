/************************************************************************
* Class: cSPArc
*
* Constructors:	
*	cSPArc(const String&, const int&, cSPNode*);
*
* Mutators:
*	
*
* Methods:
*
*
*************************************************************************/

#ifndef CSPARC_H
#define CSPARC_H

#include "String.h"

class cSPArc
{	
friend class cSPNode;
friend class cSPath;

public:
	cSPArc(const String&, const int&, cSPNode*);
	~cSPArc();

private:
	cSPNode* m_dest;
	String m_desc;
	int m_weight;

};

#endif