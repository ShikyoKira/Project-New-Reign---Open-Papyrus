#pragma once

#include <stdio.h>
#include <string>
#include "..\PexException.h"
#include "..\PexStringData.h"

struct PexWriter
{
	FILE* f;

	PexWriter(std::string filename);

	bool GetFile();

	void WriteLine(std::string line);
	void WriteLine(PexStringData line);
	void WriteLine(unsigned char c);
	void WriteLine(char line);

	template<typename T>
	void WriteLine(T num)
	{
		unsigned char c[sizeof(num)];
		memcpy(c, &num, sizeof(num));

		for (unsigned int i = sizeof(num) - 1; i >= 0; --i)
		{
			WriteLine(c[i]);
		}
	}

	template<typename ... other>
	void WriteLine(std::string line, other... rest)
	{
		WriteLine(line);
		WriteLine(rest...);
	}

	template<typename ... other>
	void WriteLine(PexStringData line, other... rest)
	{
		WriteLine(line);
		WriteLine(rest...);
	}

	template<typename T, typename ... other>
	void WriteLine(T num, other... rest)
	{
		WriteLine(num);
		WriteLine(rest...);
	}

	~PexWriter()
	{
		fclose(f);
	}
};
