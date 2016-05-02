/************************************************************************
* Class: String
*
* Constructors:
*	inline String(const char* = "");
*		-Defualt Constructor.  Also handles char*s
*	inline String(char);
*		-Constructor for single char data types
*	inline String(const String&);
*		-Copy Constructor
*
* Mutators:
*	const String& operator=(const String&);
*		-Assignment operator.  This sets the string to the same values of
*			another string object.
*
* Methods:		
*	bool operator==(const String&) const;
*		-Compares two strings
*************************************************************************/

#ifndef STRING_H
#define STRING_H

#include<iostream>
using std::ostream;
using std::istream;

#include<iomanip>
using std::setw;

class String
{
	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);

   public:
		inline String(const char* = "");
		inline String(char);
		inline String(const String&);

		//Mutators
		const String& operator=(const String&);

		//Other Methods
		bool operator==(const String&) const;
		~String() { delete [] ptr; }

   private:
		void SetS(const char*);
		char *ptr;
};

#endif