#pragma once

#include "PexList.h"
#include "DebugInfo.h"
#include "UserFlag.h"
#include "PexObject.h"

struct PexFile
{
	unsigned int magic = 0xFA57C0DE;
	unsigned short version = 0x0302;
	unsigned short gameId = 0x0001;
	papyrusBase::PexTime time;
	std::string sourceFileName;
	std::string userName;
	std::string machineName;
	PexList<PexStringData>* stringTable;
	DebugInfo debugInfo;
	PexList<UserFlag> userFlags;
	PexObjects pexObjects;

	PexFile(std::string _source, std::string _user, std::string _machine);
};

