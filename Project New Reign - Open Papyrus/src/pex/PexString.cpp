#include "PexStringData.h"

using namespace std;

PexStringData::PexStringData(string& line)
{
	set(line);
}

PexStringData::PexStringData(const char line[])
{
	set(string(line));
}

void PexStringData::set(string& line)
{
	rawData.insert(rawData.end(), line.begin(), line.end());
}

void PexStringData::operator=(string& line)
{
	set(line);
}

short PexStringData::length()
{
	return rawData.size();
}

short PexStringData::size()
{
	return rawData.size();
}
