#include "Writer.h"

using namespace std;

PexWriter::PexWriter(string filename)
{
	fopen_s(&f, filename.c_str(), "w");
}

bool PexWriter::GetFile()
{
	return f != nullptr;
}

void PexWriter::WriteLine(string line)
{
	int r = fprintf(f, line.c_str());

	if (r < 0) throw papyrusBase::PexException("Failed to write line. Line: " + line);
}

void PexWriter::WriteLine(PexStringData line)
{
	WriteLine(line.operator std::string());
}

void PexWriter::WriteLine(unsigned char c)
{
	WriteLine(static_cast<char>(c));
}

void PexWriter::WriteLine(char line)
{
	int r = fprintf(f, "%c", line);

	if (r < 0) throw papyrusBase::PexException("Failed to write line. Line: " + line);
}
