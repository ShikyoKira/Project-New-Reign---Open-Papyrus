#pragma once

#include "PexDataType.h"

struct PexAssignIdenfier
{
	papyrusBase::dataType receiver;
	papyrusBase::dataType sender;

	PexAssignIdenfier(papyrusBase::dataType _receiver, papyrusBase::dataType _sender) : receiver(_receiver), sender(_sender) {}
};
