#include "cSPArc.h"

/**************************************************************
*   Entry: 
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
cSPArc::cSPArc(const String& desc, const int& wgt, cSPNode* dest)
	   :m_dest(dest), m_desc(desc), m_weight(wgt)
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
cSPArc::~cSPArc()
{
}