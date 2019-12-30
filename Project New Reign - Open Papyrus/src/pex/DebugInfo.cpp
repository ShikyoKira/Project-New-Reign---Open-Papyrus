#include "DebugInfo.h"

DebugInfo::DebugInfo(unsigned char hasDebug)
{
	hasDebugInfo = hasDebug;
}

unsigned char DebugInfo::getHasDebug()
{
	return hasDebugInfo;
}

papyrusBase::PexTime DebugInfo::getModifTime()
{
	return modifTime;
}

PexList<DebugFunctionRef>& DebugInfo::getFunctions()
{
	return functions;
}
