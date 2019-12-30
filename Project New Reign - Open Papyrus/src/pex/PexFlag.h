#pragma once

template<typename T>
struct PexFlag
{
	int value;

	inline operator int() { return value; }

	inline PexFlag& operator|=(T& _flag)
	{
		value |= static_case<int>(_flag);
		return *this;
	}

	inline PexFlag& operator|=(PexFlag& _flag)
	{
		value = value |= _flag.value;
		return *this;
	}

	inline PexFlag& operator|=(int _flag)
	{
		value |= _flag;
		return *this;
	}

	inline PexFlag& operator|(T& _flag)
	{
		return value | static_case<int>(_flag);
	}

	inline PexFlag& operator|(PexFlag& _flag)
	{
		return value | _flag.value;
	}

	inline PexFlag& operator|(int& _flag)
	{
		return value | _flag;
	}
};
