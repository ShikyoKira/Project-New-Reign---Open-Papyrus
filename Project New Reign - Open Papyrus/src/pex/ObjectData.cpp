#include "ObjectData.h"

void papyrusBase::Variable::setName(std::string n_name)
{
	name = ADD_PEXSTRING(n_name);
}

PexStringRef& papyrusBase::Variable::getName()
{
	return name;
}

unsigned short papyrusBase::Variable::getNameIndex()
{
	return name->getIndex();
}

void papyrusBase::Variable::setType(std::string _type)
{
	type = ADD_PEXSTRING(_type);
}

PexStringRef& papyrusBase::Variable::getType()
{
	return type;
}

unsigned short papyrusBase::Variable::getTypeIndex()
{
	return type->getIndex();
}

void papyrusBase::Variable::setUserFlag(unsigned int flag)
{
	userFlags = flag;
}

unsigned int papyrusBase::Variable::getUserFlags()
{
	return userFlags;
}

void papyrusBase::Variable::setDefaultValue(const papyrusBase::Value& n_dv)
{
	DefaultValue = n_dv;
}

papyrusBase::Value& papyrusBase::Variable::getDefaultValue()
{
	return DefaultValue;
}

void papyrusBase::Property::setName(std::string _name)
{
	name = ADD_PEXSTRING(_name);
}

PexStringRef& papyrusBase::Property::getName()
{
	return name;
}

unsigned short papyrusBase::Property::getNameIndex()
{
	return name->getIndex();
}

void papyrusBase::Property::setType(std::string _type)
{
	type = ADD_PEXSTRING(_type);
}

PexStringRef& papyrusBase::Property::getType()
{
	return type;
}

unsigned short papyrusBase::Property::getTypeIndex()
{
	return type->getIndex();
}

void papyrusBase::Property::setDocString(std::string _docString)
{
	docString = ADD_PEXSTRING(_docString);
}

PexStringRef& papyrusBase::Property::getDocString()
{
	return docString;
}

unsigned short papyrusBase::Property::getDocStringIndex()
{
	return docString->getIndex();
}

void papyrusBase::Property::setUserFlags(unsigned int _flag)
{
	userFlags = _flag;
}

unsigned int papyrusBase::Property::getUserFlags()
{
	return userFlags;
}

void papyrusBase::Property::setFlags(unsigned char _flags)
{
	flags = static_cast<PropertyFlag>(_flags);
}

void papyrusBase::Property::setFlags(PropertyFlag _flags)
{
	flags = _flags;
}

unsigned char papyrusBase::Property::getFlags()
{
	return static_cast<unsigned char>(flags);
}

void papyrusBase::Property::setAutoName(std::string _auto)
{
	autoVarName = ADD_PEXSTRING(_auto);
}

PexStringRef& papyrusBase::Property::getAutoName()
{
	return autoVarName;
}

unsigned short papyrusBase::Property::getAutoNameIndex()
{
	return autoVarName->getIndex();
}

bool papyrusBase::Property::isAuto()
{
	return (flags & PropertyFlag::AUTOVAR) != PropertyFlag::NO_FLAGS;
}

bool papyrusBase::Property::isReadable()
{
	return (flags & PropertyFlag::READ) != PropertyFlag::NO_FLAGS;
}

bool papyrusBase::Property::isWritable()
{
	return (flags & PropertyFlag::WRITE) != PropertyFlag::NO_FLAGS;
}

PexFunction& papyrusBase::Property::getReader()
{
	return reader;
}

PexFunction& papyrusBase::Property::getWriter()
{
	return writer;
}

papyrusBase::PropertyFlag papyrusBase::operator&(PropertyFlag & i, PropertyFlag o)
{
	return static_cast<PropertyFlag>(std::underlying_type<PropertyFlag>::type(i) & std::underlying_type<PropertyFlag>::type(o));
}
