#include "PexStatement.h"
#include "PexFunction.h"
#include "PexCondition.h"

using namespace std;

PexInstruction& PexStatement::back()
{
	return store.back();
}

void PexStatement::add()
{
	store.push_back(PexInstruction());
}

void PexStatement::setCode(PexInstruction::OpCode code)
{
	back().setCode(code);
}

void PexStatement::rtn()
{
	add();
	setCode(PexInstruction::OpCode::Return);
}

PexStatement::PexStatement(PexFunction * _func) : func(_func)
{
	// empty
}

void PexStatement::addInstrctions(PexInstructions _instrlist)
{
	store.insert(store.end(), _instrlist.begin(), _instrlist.end());
}

PexInstructions PexStatement::asInstructions()
{
	return store;
}

void PexStatement::ifStatement(shared_ptr<papyrusBase::Value> value1, shared_ptr<papyrusBase::Value> value2, bool cmp)
{
	//generalSetup();



}

void PexStatement::endIf()
{
	add();
	setCode(PexInstruction::OpCode::Jmp);
	//back().getArgs().push_back(make_shared<papyrusBase::Value>(totalCounter() - 1, instrCount));
}

void PexStatement::returnIf()
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>());
}

void PexStatement::returnIf(string _rtn)
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>(_rtn));
}

void PexStatement::returnIf(string _rtn, papyrusBase::Value::ValueType _type)
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>(_rtn, &func->getLocals(), _type));
}

void PexStatement::returnIf(PexStringRef _rtn)
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>(_rtn));
}

void PexStatement::returnIf(PexStringRef _rtn, papyrusBase::Value::ValueType _type)
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>(_rtn, &func->getLocals(), _type));
}

void PexStatement::returnIf(int _rtn)
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>(_rtn));
}

void PexStatement::returnIf(float _rtn)
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>(_rtn));
}

void PexStatement::returnIf(bool _rtn)
{
	rtn();
	back().getArgs().push_back(make_shared<papyrusBase::Value>(_rtn));
}
