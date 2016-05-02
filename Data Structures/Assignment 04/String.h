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
		const String& operator=(const String&);
		bool operator==(const String&) const;
		~String() { delete [] ptr; }

   private:
		void SetS(const char*);
		char *ptr;
};

#endif