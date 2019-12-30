#include "PexFile.h"

PexFile::PexFile(std::string _source, std::string _user, std::string _machine) : stringTable(&tableRef)
{
	sourceFileName = _source;
	userName = _user;
	machineName = _machine;
}
