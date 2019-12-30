#pragma once

#include <vector>

template<typename T>
struct PexList : public std::vector<T>
{
	inline PexList& operator=(std::vector<T> _new)
	{
		reserve(_new.size());
		insert(end(), _new.begin(), _new.end());
	}

	inline size_t size()
	{
		return static_cast<size_t>(std::vector<T>::size());
	}
};
