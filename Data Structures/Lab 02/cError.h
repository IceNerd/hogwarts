/************************************************************************
* Class: cError
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

#ifndef ERROR_H
#define ERROR_H

#include "cString.h"

#include <iostream>
using std::ostream;

class EXCEPTION
{
friend ostream& operator<<(ostream&, const EXCEPTION&);

public:
	EXCEPTION();
	EXCEPTION(const cString&);
	~EXCEPTION();
	EXCEPTION(const EXCEPTION&);
	EXCEPTION& operator=(const EXCEPTION& toThis);

private:
	cString Error_Message;

};

#endif