#include "cSPNode.h"
#include <iostream>
using std::cout;

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
void cSPNode::InsertArc(const String& desc, const int& wgt, cSPNode* dest)
{
	if( dest != 0 )
	{
		m_arcs.Append( new cSPArc(desc, wgt, dest) );
	}
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
cSPArc* cSPNode::FindArc( const String& key)
{
	cSPArc* returnvalue(0);

	if( !(m_arcs.isEmpty()) )
	{
		int i(0);
		for(i = 0; (m_arcs[i] != m_arcs.Last()) && !(m_arcs[i]->m_dest->m_desc == key); i++);

		if(m_arcs[i]->m_dest->m_desc == key)
		{
			returnvalue = m_arcs[i];
		}
	}

	return returnvalue;
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
cSPNode::cSPNode(const String& desc)
	    :m_desc(desc), m_TDist(-1), visited(false), predecessor(-1)
{
}

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
cSPNode::~cSPNode()
{
}