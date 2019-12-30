#include "PexException.h"

papyrusBase::PexException::PexException(std::string errormsg)
{
	msg = errormsg;
}

std::string papyrusBase::PexException::what()
{
	return msg;
}
