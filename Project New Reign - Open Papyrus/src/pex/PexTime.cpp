#include "PexTime.h"

papyrusBase::PexTime::PexTime()
{
}

papyrusBase::PexTime::operator time_t()
{
	return value;
}
