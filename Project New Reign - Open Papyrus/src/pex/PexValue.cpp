#include "PexValue.h"
#include "PexFunction.h"
#include "PexException.h"

void papyrusBase::Value::copy(const Value& _value)
{
	type = _value.type;

	switch (type)
	{
		case Identifier:
		{
			value.identity = _value.value.identity;
			break;
		}
		case String:
		{
			value.string = _value.value.string;
			break;
		}
		case Integer:
		{
			value.integer = _value.value.integer;
			break;
		}
		case Float:
		{
			value.real = _value.value.real;
			break;
		}
		case Bool:
		{
			value.boolean = _value.value.boolean;
		}
	}
}

papyrusBase::Value::Value(int _int)
{
	set(_int);
}

papyrusBase::Value::Value(size_t _int)
{
	set(static_cast<int>(_int));
}

papyrusBase::Value::Value(float _float)
{
	set(_float);
}

papyrusBase::Value::Value(bool _bool)
{
	set(_bool);
}

papyrusBase::Value::Value(std::string _string)
{
	set(_string);
}

papyrusBase::Value::Value(PexStringRef _string)
{
	set(_string);
}

papyrusBase::Value::Value(PexIdentifier _local, ValueType _type)
{
	set(_local, _type);
}

papyrusBase::Value::Value(std::string _string, PexIdentifier _local, ValueType _type)
{
	if (_type == None) _type = _local->getType(_string);
	set(_string, _local, _type);
}

papyrusBase::Value::Value(PexStringRef _string, PexIdentifier _local, ValueType _type)
{
	if (_type == None) _type = _local->getType(_string);
	set(_string, _local, _type);
}

papyrusBase::Value::Value(const Value& _data)
{
	copy(_data);
}

papyrusBase::Value::Value(dataType& _data)
{
	if (_data.type == dataType::BOOL) set(static_cast<papyrusBase::Bool&>(_data));
	else if (_data.type == dataType::INT) set(static_cast<papyrusBase::Int&>(_data));
	else if (_data.type == dataType::FLOAT) set(static_cast<papyrusBase::Float&>(_data));
	else if (_data.type == dataType::STRING) set(static_cast<papyrusBase::String&>(_data));
}

PexStringRef papyrusBase::Value::getString()
{
	try
	{
		typeCheck(String);
		return value.string;
	}
	catch (PexException&)
	{
		typeCheck(Identifier);
		return value.identity->operator VarType().getName();
	}
}

int papyrusBase::Value::getInt()
{
	typeCheck(Integer);
	return value.integer;
}

float papyrusBase::Value::getFloat()
{
	typeCheck(Float);
	return value.real;
}

unsigned char papyrusBase::Value::getBool()
{
	typeCheck(Bool);
	return static_cast<unsigned char>(value.boolean);
}

papyrusBase::Value::ValueType papyrusBase::Value::getType()
{
	return type;
}

PexLocal* papyrusBase::Value::getLocal()
{
	return value.identity;
}

void papyrusBase::Value::set(int _int)
{
	type = Integer;
	value.integer = _int;
}

void papyrusBase::Value::set(float _real)
{
	type = Float;
	value.real = _real;
}

void papyrusBase::Value::set(bool _bool)
{
	type = Bool;
	value.boolean = _bool;
}

void papyrusBase::Value::set(std::string _string)
{
	type = String;
	value.string = _string;
}

void papyrusBase::Value::set(PexStringRef _string)
{
	type = String;
	value.string = _string;
}

void papyrusBase::Value::set(PexIdentifier _local, ValueType _type)
{
	type = Identifier;
	value.identity = &_local->getTemp(_type);
}

void papyrusBase::Value::set(std::string _string, PexIdentifier _local, ValueType _type)
{
	type = Identifier;
	value.identity = &_local->get(_string, _type);
}

void papyrusBase::Value::set(PexStringRef _string, PexIdentifier _local, ValueType _type)
{
	type = Identifier;
	value.identity = &_local->get(_string->get().operator std::string(), _type);
}

void papyrusBase::Value::set(ValueType _type)
{
	type = _type;
}

void papyrusBase::Value::typeCheck(ValueType n_type)
{
	if (type != n_type)
	{
		throw PexException("Invalid Variable Type");
	}
}

papyrusBase::Value& papyrusBase::Value::operator=(Value _value)
{
	copy(_value);
	return *this;
}

PexConditions papyrusBase::Value::operator==(Value _value)
{
	return PexConditions(shared_from_this(), std::make_shared<Value>(_value), PexSingleCondition::EQ);
}

PexConditions papyrusBase::Value::operator!=(Value _value)
{
	return PexConditions(shared_from_this(), std::make_shared<Value>(_value), PexSingleCondition::NOT_EQ);
}

PexConditions papyrusBase::Value::operator<=(Value _value)
{
	return PexConditions(shared_from_this(), std::make_shared<Value>(_value), PexSingleCondition::LESS_EQ);
}

PexConditions papyrusBase::Value::operator>=(Value _value)
{
	return PexConditions(shared_from_this(), std::make_shared<Value>(_value), PexSingleCondition::GREAT_EQ);
}

PexConditions papyrusBase::Value::operator<(Value _value)
{
	return PexConditions(shared_from_this(), std::make_shared<Value>(_value), PexSingleCondition::LESS);
}

PexConditions papyrusBase::Value::operator>(Value _value)
{
	return PexConditions(shared_from_this(), std::make_shared<Value>(_value), PexSingleCondition::GREAT);
}

#pragma region Integer

papyrusBase::Int::Int(std::string name)
{
	varName = name;
	type = INT;
}

papyrusBase::Int::Int(const Int& _data)
{
	data = _data.data;
	varName = _data.varName;
	type = INT;
}

papyrusBase::Int::Int(int _data)
{
	data = _data;
	type = INT;
}

papyrusBase::Int::operator int()
{
	return data;
}

papyrusBase::Int& papyrusBase::Int::operator=(int _data)
{
	data = _data;
	return *this;
}

PexAssignIdenfier papyrusBase::Int::operator=(Int _data)
{
	return PexAssignIdenfier(*this, _data);
}

papyrusBase::Cast papyrusBase::Int::asString()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Int::asBool()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Int::asFloat()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Int::operator=(Cast _data)
{

	_data.end = true;
	_data.toData.type = type;
	_data.toData.varName = varName;
	return _data;
}

PexConditions papyrusBase::Int::operator==(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::EQ);
}

PexConditions papyrusBase::Int::operator!=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::NOT_EQ);
}

PexConditions papyrusBase::Int::operator<=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS_EQ);
}

PexConditions papyrusBase::Int::operator>=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT_EQ);
}

PexConditions papyrusBase::Int::operator<(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS);
}

PexConditions papyrusBase::Int::operator>(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT);
}

PexConditions papyrusBase::Int::operator==(int _value)
{
	return PexConditions(*this, papyrusBase::Int(_value), PexSingleCondition::EQ);
}

PexConditions papyrusBase::Int::operator>(int _value)
{
	return PexConditions();
}

#pragma endregion Integer
#pragma region String

papyrusBase::String::String(std::string name)
{
	varName = name;
	type = STRING;
}

papyrusBase::String::String(const String& _data)
{
	data = _data.data;
	varName = _data.varName;
	type = STRING;
}

papyrusBase::String::operator std::string()
{
	return data;
}

papyrusBase::String& papyrusBase::String::operator=(std::string _data)
{
	data = _data;
	return *this;
}

PexAssignIdenfier papyrusBase::String::operator=(String _data)
{
	return PexAssignIdenfier(*this, _data);
}

papyrusBase::Cast papyrusBase::String::asInt()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::String::asBool()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::String::asFloat()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::String::operator=(Cast _data)
{

	_data.end = true;
	_data.toData.type = type;
	_data.toData.varName = varName;
	return _data;
}

PexConditions papyrusBase::String::operator==(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::EQ);
}

PexConditions papyrusBase::String::operator!=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::NOT_EQ);
}

PexConditions papyrusBase::String::operator<=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS_EQ);
}

PexConditions papyrusBase::String::operator>=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT_EQ);
}

PexConditions papyrusBase::String::operator<(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS);
}

PexConditions papyrusBase::String::operator>(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT);
}

#pragma region String
#pragma region Float

papyrusBase::Float::Float(std::string name)
{
	varName = name;
	type = FLOAT;
}

papyrusBase::Float::Float(const Float& _data)
{
	data = _data.data;
	varName = _data.varName;
	type = FLOAT;
}

papyrusBase::Float& papyrusBase::Float::operator=(float _data)
{
	data = _data;
	return *this;
}

PexAssignIdenfier papyrusBase::Float::operator=(Float _data)
{
	return PexAssignIdenfier(*this, _data);
}

papyrusBase::Cast papyrusBase::Float::asString()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Float::asInt()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Float::asBool()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Float::operator=(Cast _data)
{
	_data.end = true;
	_data.toData.type = type;
	_data.toData.varName = varName;
	return _data;
}

PexConditions papyrusBase::Float::operator==(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::EQ);
}

PexConditions papyrusBase::Float::operator!=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::NOT_EQ);
}

PexConditions papyrusBase::Float::operator<=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS_EQ);
}

PexConditions papyrusBase::Float::operator>=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT_EQ);
}

PexConditions papyrusBase::Float::operator<(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS);
}

PexConditions papyrusBase::Float::operator>(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT);
}

#pragma endregion Float
#pragma region Bool

papyrusBase::Bool::Bool(std::string name)
{
	varName = name;
	type = BOOL;
}

papyrusBase::Bool::Bool(const Bool& _data)
{
	data = _data.data;
	varName = _data.varName;
	type = BOOL;
}

papyrusBase::Bool::operator bool()
{
	return data;
}

papyrusBase::Bool& papyrusBase::Bool::operator=(bool _data)
{
	data = _data;
	return *this;
}

PexAssignIdenfier papyrusBase::Bool::operator=(Bool _data)
{
	return PexAssignIdenfier(*this, _data);
}

papyrusBase::Cast papyrusBase::Bool::asString()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Bool::asInt()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Bool::asFloat()
{
	return Cast(dataType(), *this);
}

papyrusBase::Cast papyrusBase::Bool::operator=(Cast _data)
{

	_data.end = true;
	_data.toData.type = type;
	_data.toData.varName = varName;
	return _data;
}

PexConditions papyrusBase::Bool::operator==(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::EQ);
}

PexConditions papyrusBase::Bool::operator!=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::NOT_EQ);
}

PexConditions papyrusBase::Bool::operator<=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS_EQ);
}

PexConditions papyrusBase::Bool::operator>=(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT_EQ);
}

PexConditions papyrusBase::Bool::operator<(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::LESS);
}

PexConditions papyrusBase::Bool::operator>(dataType& _value)
{
	return PexConditions(*this, _value, PexSingleCondition::GREAT);
}

#pragma endregion BOOL
