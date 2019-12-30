#pragma once

#include "PexFunction.h"

namespace papyrusBase
{
	struct Variable
	{
	private:
		PexStringRef name;
		PexStringRef type;
		unsigned int userFlags;
		Value DefaultValue;


	public:
		void setName(std::string _name);
		PexStringRef& getName();
		unsigned short getNameIndex();

		void setType(std::string _type);
		PexStringRef& getType();
		unsigned short getTypeIndex();

		void setUserFlag(unsigned int flag);
		unsigned int getUserFlags();

		void setDefaultValue(const Value& n_dv);
		Value& getDefaultValue();
	};

	enum class PropertyFlag : unsigned char
	{
		NO_FLAGS = 0,
		READ = 1 << 0,
		WRITE = 1 << 1,
		AUTOVAR = 1 << 2
	};

	PropertyFlag operator&(PropertyFlag& i, PropertyFlag o);

	struct Property
	{
	private:

		PexStringRef name;
		PexStringRef type;
		PexStringRef docString;
		unsigned int userFlags;
		PropertyFlag flags;

		PexStringRef autoVarName;
		PexFunction reader;
		PexFunction writer;

	public:
		void setName(std::string _name);
		PexStringRef& getName();
		unsigned short getNameIndex();

		void setType(std::string _type);
		PexStringRef& getType();
		unsigned short getTypeIndex();

		void setDocString(std::string _docString);
		PexStringRef& getDocString();
		unsigned short getDocStringIndex();

		void setUserFlags(unsigned int _flag);
		unsigned int getUserFlags();

		void setFlags(unsigned char _flags);
		void setFlags(PropertyFlag _flags);
		unsigned char getFlags();

		void setAutoName(std::string _auto);
		PexStringRef& getAutoName();
		unsigned short getAutoNameIndex();

		bool isAuto();
		bool isReadable();
		bool isWritable();

		PexFunction& getReader();
		PexFunction& getWriter();
	};

	struct State
	{
		PexStringRef name;
		PexList<PexNamedFunction> functions;
	};

	struct ObjectData
	{
		PexStringRef parentName;		// script name
		PexStringRef docString;
		unsigned int userFlags;
		PexStringRef autoStateName;
		PexList<Variable> Variables;
		PexList<Property> numProperties;
		PexList<State> numStates;
	};
}
