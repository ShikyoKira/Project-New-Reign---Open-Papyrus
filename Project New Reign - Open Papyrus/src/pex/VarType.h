#pragma once

#include "PexValue.h"

struct VarType
{
private:
	PexStringRef name;
	PexStringRef typeName;

public:
	VarType() {}
	VarType(std::string _name, std::string _type);
	VarType(std::string _name, papyrusBase::Value::ValueType _type);

	void setName(std::string _name);
	void setTypeName(std::string _type);
	void setTypeName(papyrusBase::Value::ValueType _type);

	PexStringRef& getName();
	PexStringRef& getTypeName();
};

void TypeToString(PexStringRef& _string, papyrusBase::Value::ValueType _type);
PexStringRef TypeToString(papyrusBase::Value::ValueType _type);
papyrusBase::Value::ValueType StringToType(std::string _string);
papyrusBase::Value::ValueType StringToType(PexStringRef _string);

