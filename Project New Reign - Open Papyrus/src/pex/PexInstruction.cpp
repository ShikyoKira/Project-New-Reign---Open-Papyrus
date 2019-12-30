#include "PexInstruction.h"
#include "PexValue.h"

void PexInstruction::setCode(unsigned char _code)
{
	code = static_cast<OpCode>(_code);
}

void PexInstruction::setCode(OpCode _code)
{
	code = _code;
}

PexInstruction::OpCode& PexInstruction::getCode()
{
	return code;
}

PexList<std::shared_ptr<papyrusBase::Value>>& PexInstruction::getArgs()
{
	return args;
}
