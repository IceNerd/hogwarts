#ifndef ERROR_H
#define ERROR_H

#include "String.h"

#include <iostream>
using std::ostream;

class EXCEPTION
{
friend ostream& operator<<(ostream&, const EXCEPTION&);

public:
	EXCEPTION();
	EXCEPTION(const String&);
	~EXCEPTION();
	EXCEPTION(const EXCEPTION&);
	EXCEPTION& operator=(const EXCEPTION& toThis);

private:
	String Error_Message;

};

#endif