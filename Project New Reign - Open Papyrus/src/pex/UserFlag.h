#pragma once

#include"PexStringRef.h"

struct UserFlag
{
private:
	PexStringRef name;
	unsigned char flagIndex = 0;

public:
	void setName(std::string _name);
	void setFlagIndex(unsigned char _flag);

	PexStringRef& getName();
	unsigned char& getFlagIndex();
};
