#include<iomanip>
using std::setw;

#include "String.h"

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
inline String::String(const char* p)
{
  p = p ? p : "";
  ptr = new char[strlen(p) + 1];
  strcpy(ptr, p);
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
inline String::String(char ch)
{
  ptr = new char[2];
  ptr[0] = ch;
  ptr[1] = '\0';
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
inline String::String(const String& obj)
{
  ptr = new char[strlen(obj.ptr) + 1];
  strcpy(ptr, obj.ptr);
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
void String::SetS(const char* tewThis)
{
  ptr = new char[strlen(tewThis) + 1];
  strcpy(ptr, tewThis);
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
const String& String::operator=(const String& toThis)
{
	if(&toThis != this)
	{
		delete [] ptr;
		SetS(toThis.ptr);
	}
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
bool String::operator==(const String& amI) const
{
	return strcmp(ptr, amI.ptr) == 0;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
ostream& operator<<(ostream& output, const String& vato)
{
	output<<vato.ptr;
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
istream& operator>>(istream& input, String& vato)
{
	char temp[100];
	input>>setw(100)>>temp;
	vato = temp;
	return input;
}