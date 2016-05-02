#include<iomanip>
using std::setw;

#include<iostream>
using std::cout;

#include "String.h"

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

const String& String::operator+=( const String& right)
{
	char* tempPtr = new char[ strlen(*this) + strlen(right) + 1];
	strcpy(tempPtr, ptr);
	strcpy(tempPtr + strlen(*this), right.ptr);
	delete [] ptr;
	ptr = tempPtr;
	return *this;
}

String::operator char*()
{
	return ptr;
}

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