#pragma once

#include <memory>
#include <chrono>

; namespace papyrusBase
{
	struct PexTime
	{
	private:
		time_t value = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	public:
		PexTime();
		operator time_t();
	};
}
