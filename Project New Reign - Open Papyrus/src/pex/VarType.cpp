#include "PexValue.h"
#include "VarType.h"
#include "PexException.h"
#include <boost\algorithm\string.hpp>

using namespace std;

void TypeToString(PexStringRef& _string, papyrusBase::Value::ValueType _type)
{
	switch (_type)
	{
		case papyrusBase::Value::String:
		{
			_string = ADD_PEXSTRING("String");
			break;
		}
		case papyrusBase::Value::Identifier:
		{
			_string = ADD_PEXSTRING("String");
			break;
		}
		case papyrusBase::Value::Integer:
		{
			_string = ADD_PEXSTRING("Int");
			break;
		}
		case papyrusBase::Value::Float:
		{
			_string = ADD_PEXSTRING("Float");
			break;
		}
		case papyrusBase::Value::Bool:
		{
			_string = ADD_PEXSTRING("Bool");
			break;
		}
		case papyrusBase::Value::None:
		{
			_string = ADD_PEXSTRING("None");
				break;
		}
		default:
		{
			_string = ADD_PEXSTRING("None");
		}
	}
}

PexStringRef TypeToString(papyrusBase::Value::ValueType _type)
{
	switch (_type)
	{
		case papyrusBase::Value::String: return "String";
		case papyrusBase::Value::Identifier: return "String";
		case papyrusBase::Value::Integer: return "Int";
		case papyrusBase::Value::Float: return "Float";
		case papyrusBase::Value::Bool: return "Bool";
		case papyrusBase::Value::None: return "None";
		default: return "None";
	}
}

papyrusBase::Value::ValueType StringToType(std::string _string)
{
	if (_string == "String") return papyrusBase::Value::String;
	else if (_string == "Int") return papyrusBase::Value::Integer;
	else if (_string == "Float") return papyrusBase::Value::Float;
	else if (_string == "Bool") return papyrusBase::Value::Bool;
	return papyrusBase::Value::None;
}

papyrusBase::Value::ValueType StringToType(PexStringRef _string)
{
	return StringToType(_string->get());
}

void TypeToString(PexStringRef& _string, std::string _type)
{
	if (_type.length() == 0)
	{
		_type = "None";
	}
	else
	{
		boost::to_lower(_type);

		if (_type == "bool") _type = "Bool";
		else if (_type == "string") _type = "String";
		else if (_type == "int") _type = "Int";
		else if (_type == "float") _type = "Float";
		else throw papyrusBase::PexException("Invalid data type (Data Type: " + _type + ")");
	}

	_string = ADD_PEXSTRING(_type);
}

VarType::VarType(std::string _name, std::string _type)
{
	setName(_name);
	setTypeName(_type);
}

VarType::VarType(std::string _name, papyrusBase::Value::ValueType _type)
{
	setName(_name);
	setTypeName(_type);
}

void VarType::setName(string _name)
{
	name = ADD_PEXSTRING(_name);
}

void VarType::setTypeName(string _type)
{
	TypeToString(typeName, _type);
}

void VarType::setTypeName(papyrusBase::Value::ValueType _type)
{
	TypeToString(typeName, _type);
}

PexStringRef& VarType::getName()
{
	return name;
}

PexStringRef& VarType::getTypeName()
{
	return typeName;
}
