#pragma once

#include <string>

namespace papyrusBase
{
	struct dataType
	{
		enum Type
		{
			STRING = 2,
			INT = 3,
			FLOAT = 4,
			BOOL = 5
		};

		Type type;
		std::string varName = "\"empty\"";
		bool isTemp() { return varName == "\"empty\""; }

		dataType() {}
	};
}