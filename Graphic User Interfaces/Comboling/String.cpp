#include "String.h"

#include<iomanip>
using std::setw;

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

/*------------------------  Op Overloads  -------------------*/

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
const String& String::operator+=( const String& right)
{
	char* tempPtr = new char[ strlen(*this) + strlen(right) + 1];
	strcpy(tempPtr, ptr);
	strcpy(tempPtr + strlen(*this), right.ptr);
	delete [] ptr;
	ptr = tempPtr;
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
String::operator char*()
{
	return ptr;
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
String::operator const char*() const
{
	return ptr;
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
	return !(strcmp(ptr, amI.operator const char *()));
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
bool String::operator==(const char* amI) const
{
	return !(strcmp(ptr, amI));
}

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
char String::operator[](const int index) const
{
	if(ptr[index])
	{
		return ptr[index];
	}
	else
	{
		return '0';
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
void String::operator+=(char addme)
{
	char* temp;
	temp = new char[strlen(ptr) + 1];
	strcpy(temp, ptr);
	delete [] ptr;
	ptr = new char[strlen(temp) + 2];

	for(int i = 0; i < int(strlen(temp) + 1); i++)
	{
		ptr[i] = temp[i];
	}
	ptr[strlen(temp)] = addme;
	ptr[strlen(temp) + 1] = '\0';
	delete [] temp;
}

/*------------------------  CTors  ---------------------------*/

/**************************************************************
*   Entry:  
*
*    Exit:  
*
* Purpose:  
*
***************************************************************/
String::String(const char* p)
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
String::String(char ch)
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
String::String(const String& obj)
{
  ptr = new char[strlen(obj.ptr) + 1];
  strcpy(ptr, obj.ptr);
}