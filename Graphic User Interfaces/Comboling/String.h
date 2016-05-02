/************************************************************************
* Class: String
*
* Constructors:
*
* Mutators:
*
* Methods:		
*	
*************************************************************************/

#ifndef STRING_H
#define STRING_H

class String
{
   public:
		String(const char* = "");
		String(char);
		String(const String&);
		~String() { if(ptr){delete [] ptr;} }
		const String& operator=(const String&);

		bool operator==(const String&) const;
		bool operator==(const char*) const;
		void operator+=(char);
		const String& operator+=( const String& right);
		char operator[](const int) const;

		operator char*();
		operator const char*() const;

   private:
		void SetS(const char*);
		char* ptr;
};

#endif