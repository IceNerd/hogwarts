#include "Error.h"

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
EXCEPTION& EXCEPTION::operator=(const EXCEPTION& toThis)
{
	this->Error_Message = toThis.Error_Message;
	return *this;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
ostream& operator<<(ostream& output, const EXCEPTION& vato)
{
	output<<"***Exception: "<<vato.Error_Message;
	return output;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
EXCEPTION::EXCEPTION()
		  :Error_Message("***An Exception has Occured!")
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
EXCEPTION::EXCEPTION(const String& err)
{
	Error_Message = err;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
EXCEPTION::EXCEPTION(const EXCEPTION& err)
{
	*this = err;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
EXCEPTION::~EXCEPTION()
{
}