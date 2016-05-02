#include<iomanip>
using std::setw;

#include "cString.h"

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
inline cString::cString(const char* p)
{
  p = p ? p : "";
  ptr = new char[strlen(p) + 1];
  strcpy(ptr, p);
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
inline cString::cString(char ch)
{
  ptr = new char[2];
  ptr[0] = ch;
  ptr[1] = '\0';
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
inline cString::cString(const cString& obj)
{
  ptr = new char[strlen(obj.ptr) + 1];
  strcpy(ptr, obj.ptr);
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
void cString::SetS(const char* tewThis)
{
  ptr = new char[strlen(tewThis) + 1];
  strcpy(ptr, tewThis);
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
const cString& cString::operator=(const cString& toThis)
{
	if(&toThis != this)
	{
		delete [] ptr;
		SetS(toThis.ptr);
	}
	return *this;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
bool cString::operator==(const cString& amI) const
{
	return strcmp(ptr, amI.ptr) == 0;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
ostream& operator<<(ostream& output, const cString& vato)
{
	output<<vato.ptr;
	return output;
}

/*************************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
*************************************************************************/
istream& operator>>(istream& input, cString& vato)
{
	char temp[100];
	input>>setw(100)>>temp;
	vato = temp;
	return input;
}