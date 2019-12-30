#pragma once

#include "ObjectData.h"

struct PexObject
{
	PexStringRef nameIndex;
	unsigned int size;
	papyrusBase::ObjectData data;
};

typedef PexList<PexObject> PexObjects;