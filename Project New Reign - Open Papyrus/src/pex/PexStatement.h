#pragma once

#include <string>
#include "PexValue.h"
#include "PexInstruction.h"

struct PexFunction;

struct PexStatement
{
private:
	PexInstructions store;
	PexFunction* func;

	PexInstruction& back();
	void add();
	void setCode(PexInstruction::OpCode code);
	void rtn();

public:
	// initialization
	PexStatement(PexFunction* _func);

	// import
	void addInstrctions(PexInstructions _instrlist);

	// export
	PexInstructions asInstructions();

	// if statement
	void ifStatement(std::shared_ptr<papyrusBase::Value> value1, std::shared_ptr<papyrusBase::Value> value2, bool cmp);
	void endIf();

	// handle return
	void returnIf();
	void returnIf(std::string _rtn);
	void returnIf(std::string _rtn, papyrusBase::Value::ValueType _type);				
	void returnIf(PexStringRef _rtn);
	void returnIf(PexStringRef _rtn, papyrusBase::Value::ValueType _type);
	void returnIf(int _rtn);
	void returnIf(float _rtn);
	void returnIf(bool _rtn);
};
