#pragma once

#include <memory>
#include "PexList.h"

namespace papyrusBase
{
	struct Value;
}

struct PexInstruction
{
	enum class OpCode : unsigned char
	{
		Nop,
		Iadd,		// add (ref int/ref float, ref local/float/int, ref local/float/int)
		Fadd,
		Isub,		// minus (ref int/ref float, ref local/float/int, ref local/float/int)
		Fsub,
		Imul,		// multiply (ref int/ref float, ref local/float/int, ref local/float/int)
		Fmul,
		Idiv,
		Fdiv,
		Imod,
		Not,					// "!" not (ref temp, ref temp)
		Ineg,
		Fneg,
		Assign,					// "=" (ref local, ref temp/int/float/string/bool)				for temp to local
		Cast,					// cast, change data type (ref temp, ref local/ref temp)		for temp/local to temp
		Cmp_Eq,					// "==" compare equal (ref bool, string/int/float/bool/ref local, string/int/float/bool/ref local)
		Cmp_Lt,					// ">" compare lesser (ref bool, string/int/float/bool/ref local, string/int/float/bool/ref local)
		Cmpt_Lte,				// ">=" compare lesser or equal (ref bool, string/int/float/bool/ref local, string/int/float/bool/ref local)
		Cmp_Gt,					// "<" compare greater (ref bool, string/int/float/bool/ref local, string/int/float/bool/ref local)
		Cmp_Gte,				// "<=" compare greater or equal (ref bool, string/int/float/bool/ref local, string/int/float/bool/ref local)
		Jmp,					// jump (int)
		Jmpt,					// jump if true (ref bool, int)
		Jmpf,					// jump if false (ref bool, int)
		CallMethod,
		CallParent,
		CallStatic,				// function Args(ref source, ref functionName, ref returnValue/::NoneVar), VarArgs(...) variables
		Return,					// return
		Strcat,					// <temp1 = local + temp3> (ref temp1, string/ref local, string/ref temp)
		PropGet,
		PropSet,
		Array_Create,			// new [] (ref temp, int size)
		Array_Length,
		Array_GetElement,		// array[] (ref temp, ref array, int/ref local)
		Array_SetElement,		// array[] (ref array, int/ref int, ref temp)
		Array_FindElement,
		Array_RfindElement
	};

private:
	OpCode code;
	PexList<std::shared_ptr<papyrusBase::Value>> args;

public:
	void setCode(unsigned char _code);
	void setCode(OpCode _code);

	OpCode& getCode();
	PexList<std::shared_ptr<papyrusBase::Value>>& getArgs();
};

typedef PexList<PexInstruction> PexInstructions;
