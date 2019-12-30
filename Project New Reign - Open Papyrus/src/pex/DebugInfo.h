#pragma once

#include <chrono>
#include "PexStringRef.h"
#include "PexTime.h"
#include "PexList.h"

struct DebugFunction
{
	PexStringRef objectName;
	PexStringRef stateName;
	PexStringRef functionName;
	unsigned char functionType;
	PexList<unsigned short> lineNumbers;
};

typedef std::shared_ptr<DebugFunction> DebugFunctionRef;

struct DebugInfo
{
private:
	unsigned char hasDebugInfo;			// Tell if there is debug information. If 0, the following fields are null
	papyrusBase::PexTime modifTime;		// time of creation
	PexList<DebugFunctionRef> functions;

public:
	DebugInfo() {}
	DebugInfo(unsigned char hasDebug);

	unsigned char getHasDebug();
	papyrusBase::PexTime getModifTime();
	PexList<DebugFunctionRef>& getFunctions();
};
