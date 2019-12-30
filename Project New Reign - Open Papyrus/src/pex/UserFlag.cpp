#include "UserFlag.h"

using namespace std;

void UserFlag::setName(string _name)
{
	name = ADD_PEXSTRING(_name);
}

void UserFlag::setFlagIndex(unsigned char _flag)
{
	flagIndex = _flag;
}

PexStringRef& UserFlag::getName()
{
	return name;
}

unsigned char& UserFlag::getFlagIndex()
{
	return flagIndex;
}
