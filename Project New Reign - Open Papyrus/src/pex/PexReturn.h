#pragma once

#include "PexDataType.h"

namespace papyrusBase
{
	struct dataType;

	struct Return
	{
	private:
		dataType& data;

	public:
		Return(dataType& _data) : data(_data) {}
		operator dataType&() { return data; }
	};
}
