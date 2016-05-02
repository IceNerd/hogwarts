/************************************************************************
* Class: cString
*
* Constructors:	
*	
*
* Mutators:
*	
*
* Methods:		
*	
*************************************************************************/

#ifndef CSTRING_H
#define CSTRING_H

#include<iostream>
using std::ostream;
using std::istream;

#include<iomanip>
using std::setw;

class cString
{
	friend ostream& operator<<(ostream&, const cString&);
	friend istream& operator>>(istream&, cString&);

   public:
		inline cString(const char* = "");
		inline cString(char);
		inline cString(const cString&);
		const cString& operator=(const cString&);
		bool operator==(const cString&) const;
		~cString() { delete [] ptr; }

   private:
		void SetS(const char*);
		char *ptr;
};

#endif