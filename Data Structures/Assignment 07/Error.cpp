#include "Error.h"

EXCEPTION& EXCEPTION::operator=(const EXCEPTION& toThis)
{
	this->Error_Message = toThis.Error_Message;
	return *this;
}

ostream& operator<<(ostream& output, const EXCEPTION& vato)
{
	output<<"***Exception: "<<vato.Error_Message;
	return output;
}

EXCEPTION::EXCEPTION()
		  :Error_Message("***An Exception has Occured!")
{
}

EXCEPTION::EXCEPTION(const String& err)
{
	Error_Message = err;
}

EXCEPTION::EXCEPTION(const EXCEPTION& err)
{
	*this = err;
}

EXCEPTION::~EXCEPTION()
{
}