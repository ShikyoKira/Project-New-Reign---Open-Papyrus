#pragma once

#include <string>
#include "PexList.h"

struct PexStringData
{
private:
	PexList<unsigned char> rawData;		// string represented in ASCII

public:
	PexStringData(std::string& line);
	PexStringData(const char line[]);

	inline operator std::string()
	{
		std::string line;
		line.insert(line.end(), rawData.begin(), rawData.end());
		return line;
	}

	inline bool operator==(std::string _str)
	{
		return this->operator std::string() == _str;
	}

	inline bool operator!=(std::string _str)
	{
		return this->operator std::string() != _str;
	}

	void set(std::string& line);
	void operator=(std::string& line);
	short length();
	short size();
};

