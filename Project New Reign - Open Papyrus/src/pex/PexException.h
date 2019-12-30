#pragma once

#include <string>

namespace papyrusBase
{
	struct PexException : public std::exception
	{
	private:
		std::string msg;

	public:
		PexException(std::string errormsg);
		std::string what();
	};
}
