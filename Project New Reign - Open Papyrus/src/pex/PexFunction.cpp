#include "PexFunction.h"
#include "PexException.h"
#include "VarType.h"
#include <memory>
#include <boost\algorithm\string.hpp>

using namespace std;

papyrusBase::Value::ValueType dataTypeToValueType(papyrusBase::dataType::Type _type)
{
	return static_cast<papyrusBase::Value::ValueType>(_type);
}

shared_ptr<papyrusBase::Value> trueTempValue(papyrusBase::dataType& _data)
{
	if (_data.type == papyrusBase::dataType::BOOL) return make_shared<papyrusBase::Value>(static_cast<papyrusBase::Bool&>(_data));
	else if (_data.type == papyrusBase::dataType::INT) return make_shared<papyrusBase::Value>(static_cast<papyrusBase::Int&>(_data));
	else if (_data.type == papyrusBase::dataType::FLOAT) return make_shared<papyrusBase::Value>(static_cast<papyrusBase::Float&>(_data));
	else return make_shared<papyrusBase::Value>(static_cast<papyrusBase::String&>(_data));
}

PexList<shared_ptr<papyrusBase::Value>>& PexFunction::addAssign()
{
	instructions.push_back(PexInstruction());
	instructions.back().setCode(PexInstruction::OpCode::Assign);
	return instructions.back().getArgs();
}

void PexFunction::toAssign(papyrusBase::dataType& _data, papyrusBase::Value::ValueType _type, papyrusBase::dataType& _data2)
{
	auto& args = addAssign();
	args.push_back(make_shared<papyrusBase::Value>(_data.varName, &locals, _type));
	args.push_back(make_shared<papyrusBase::Value>(_data2.varName, &locals, _type));
}

void PexFunction::toAssign(papyrusBase::Bool& _data, papyrusBase::Bool& _data2)
{
	auto& args = addAssign();

	if (_data.isTemp()) args.push_back(make_shared<papyrusBase::Value>(&locals, papyrusBase::Value::Bool));
	else args.push_back(make_shared<papyrusBase::Value>(_data.varName, &locals, papyrusBase::Value::Bool));

	if (_data2.isTemp()) args.push_back(make_shared<papyrusBase::Value>(_data));
	else args.push_back(make_shared<papyrusBase::Value>(_data2.varName, &locals, papyrusBase::Value::Bool));
}

void PexFunction::toAssign(papyrusBase::Int& _data, papyrusBase::Int& _data2)
{
	auto& args = addAssign();

	if (_data.isTemp()) args.push_back(make_shared<papyrusBase::Value>(&locals, papyrusBase::Value::Integer));
	else args.push_back(make_shared<papyrusBase::Value>(_data.varName, &locals, papyrusBase::Value::Integer));

	if (_data2.isTemp()) args.push_back(make_shared<papyrusBase::Value>(_data));
	else args.push_back(make_shared<papyrusBase::Value>(_data2.varName, &locals, papyrusBase::Value::Integer));
}

void PexFunction::toAssign(papyrusBase::Float& _data, papyrusBase::Float& _data2)
{
	auto& args = addAssign();

	if (_data.isTemp()) args.push_back(make_shared<papyrusBase::Value>(&locals, papyrusBase::Value::Float));
	else args.push_back(make_shared<papyrusBase::Value>(_data.varName, &locals, papyrusBase::Value::Float));

	if (_data2.isTemp()) args.push_back(make_shared<papyrusBase::Value>(_data));
	else args.push_back(make_shared<papyrusBase::Value>(_data2.varName, &locals, papyrusBase::Value::Float));
}

void PexFunction::toAssign(papyrusBase::String& _data, papyrusBase::String& _data2)
{
	auto& args = addAssign();

	if (_data.isTemp()) args.push_back(make_shared<papyrusBase::Value>(&locals, papyrusBase::Value::String));
	else args.push_back(make_shared<papyrusBase::Value>(_data.varName, &locals, papyrusBase::Value::String));

	if (_data2.isTemp()) args.push_back(make_shared<papyrusBase::Value>(_data));
	else args.push_back(make_shared<papyrusBase::Value>(_data2.varName, &locals, papyrusBase::Value::String));
}

void PexFunction::setTypeName(papyrusBase::Value::ValueType type)
{
	TypeToString(returnTypeName, type);
}

void PexFunction::setTypeName(string _name)
{
	returnTypeName = ADD_PEXSTRING(_name);
}

void PexFunction::setDocString(string _doc)
{
	docString = ADD_PEXSTRING(_doc);
}

void PexFunction::setUserFlags(unsigned int _flags)
{
	userFlags = _flags;
}

void PexFunction::setFlags(unsigned char _flags)
{
	flags |= _flags;
}

void PexFunction::setGlobal()
{
	flags |= FLAG::global;
}

void PexFunction::setNative()
{
	flags |= native;
}

PexStringRef& PexFunction::getReturnType()
{
	return returnTypeName;
}

PexStringRef& PexFunction::getDoc()
{
	return docString;
}

unsigned int& PexFunction::getUserFlags()
{
	return userFlags;
}

unsigned char PexFunction::getFlags()
{
	return static_cast<unsigned char>(flags);
}

PexList<VarType>& PexFunction::getParameters()
{
	return parameters;
}

PexLocals& PexFunction::getLocals()
{
	return locals;
}

PexInstructions& PexFunction::asInstructions()
{
	return instructions;
}

void PexFunction::p_Function(papyrusBase::Int num)
{
	toAssign(num);
}

void PexFunction::p_Function(papyrusBase::Float num)
{
	toAssign(num);
}

void PexFunction::p_Function(papyrusBase::Bool num)
{
	toAssign(num);
}

void PexFunction::p_Function(papyrusBase::String num)
{
	toAssign(num);
}

void PexFunction::p_Function(papyrusBase::Cast cast)
{
	instructions.push_back(PexInstruction());
	auto& args = instructions.back().getArgs();
	instructions.back().setCode(PexInstruction::OpCode::Cast);
	args.push_back(make_shared<papyrusBase::Value>(cast.toData.varName, &locals, dataTypeToValueType(cast.toData.type)));
	args.push_back(make_shared<papyrusBase::Value>(cast.fromData.varName, &locals, dataTypeToValueType(cast.fromData.type)));
}

void PexFunction::p_Function(papyrusBase::Return rtn)
{
	instructions.push_back(PexInstruction());
	auto& args = instructions.back().getArgs();
	instructions.back().setCode(PexInstruction::OpCode::Return);
	papyrusBase::dataType& _data = rtn.operator papyrusBase::dataType&();

	if (_data.isTemp()) args.push_back(trueTempValue(_data));
	else args.push_back(make_shared<papyrusBase::Value>(_data.varName, &locals, dataTypeToValueType(_data.type)));
}

void PexFunction::p_Function(PexInstructions instr)
{
	instructions.insert(instructions.end(), instr.begin(), instr.end());

}

void PexFunction::p_Function(PexAssignIdenfier assign)
{
	toAssign(assign.receiver, dataTypeToValueType(assign.receiver.type), assign.sender);
}

void PexFunction::p_Function(If condition)
{
	string num = "";
}

void PexFunction::p_Function(ElseIf condition)
{
	string num = "";
}

void PexFunction::p_Function(Else condition)
{
	string num = "";
}

void PexFunction::p_Function(EndIf condition)
{
	string num = "";
}

PexNamedFunction::PexNamedFunction(string _name)
{
	setName(_name);
}

void PexNamedFunction::setName(string _name)
{
	name = ADD_PEXSTRING(_name);
}

PexStringRef& PexNamedFunction::getName()
{
	return name;
}

PexFunction& PexNamedFunction::getFunction()
{
	return func;
}
