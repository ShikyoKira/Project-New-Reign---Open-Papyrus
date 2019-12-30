#pragma once

#include "PexFlag.h"
#include "PexLocal.h"
#include "PexInstruction.h"
#include "PexReturn.h"
#include "PexIf.h"

struct PexFunction
{
	enum FLAG
	{
		none = 0,
		global = 1 << 0,
		native = 1 << 1
	};
	
private:
	PexStringRef returnTypeName;
	PexStringRef docString;
	unsigned int userFlags;
	PexFlag<FLAG> flags;
	PexList<VarType> parameters;
	PexLocals locals;
	PexInstructions instructions;
	unsigned int curBracket;
	PexList<unsigned int> condLayers;

	PexList<std::shared_ptr<papyrusBase::Value>>& addAssign();
	void toAssign(papyrusBase::dataType& _data, papyrusBase::Value::ValueType _type, papyrusBase::dataType& _data2);
	void toAssign(papyrusBase::Bool& _data, papyrusBase::Bool& _data2 = papyrusBase::Bool());
	void toAssign(papyrusBase::Int& _data, papyrusBase::Int& _data2 = papyrusBase::Int());
	void toAssign(papyrusBase::Float& _data, papyrusBase::Float& _data2 = papyrusBase::Float());
	void toAssign(papyrusBase::String& _data, papyrusBase::String& _data2 = papyrusBase::String());

public:
	void setTypeName(papyrusBase::Value::ValueType _name);
	void setTypeName(std::string _name);
	void setDocString(std::string _doc);
	void setUserFlags(unsigned int _flags);
	void setFlags(unsigned char _flags);
	void setGlobal();
	void setNative();

	PexStringRef& getReturnType();
	PexStringRef& getDoc();
	unsigned int& getUserFlags();
	unsigned char getFlags();
	PexList<VarType>& getParameters();
	PexLocals& getLocals();
	PexInstructions& asInstructions();

	void p_Function(papyrusBase::Int num);
	void p_Function(papyrusBase::Float num);
	void p_Function(papyrusBase::Bool num);
	void p_Function(papyrusBase::String num);
	void p_Function(papyrusBase::Cast cast);
	void p_Function(papyrusBase::Return rtn);
	void p_Function(PexInstructions instr);
	void p_Function(PexAssignIdenfier assign);
	void p_Function(If condition);
	void p_Function(ElseIf condition);
	void p_Function(Else condition);
	void p_Function(EndIf condition);

	template<typename ...other>
	void p_Function(papyrusBase::Int num, other ...scripts)
	{
		p_Function(num);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(papyrusBase::Float num, other ...scripts)
	{
		p_Function(num);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(papyrusBase::Bool b, other ...scripts)
	{
		p_Function(b);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(papyrusBase::String str, other ...scripts)
	{
		p_Function(str);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(papyrusBase::Cast cast, other ...scripts)
	{
		p_Function(cast);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(papyrusBase::Return rtn, other ...scripts)
	{
		p_Function(rtn);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(PexInstructions instr, other ...scripts)
	{
		p_Function(instr);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(PexAssignIdenfier assign, other ...scripts)
	{
		p_Function(assign);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(If condition, other ...scripts)
	{
		p_Function(condition);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(ElseIf condition, other ...scripts)
	{
		p_Function(condition);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(Else condition, other ...scripts)
	{
		p_Function(condition);
		p_Function(scripts...);
	}

	template<typename ...other>
	void p_Function(EndIf condition, other ...scripts)
	{
		p_Function(condition);
		p_Function(scripts...);
	}
};

struct PexNamedFunction
{
private:
	PexStringRef name;
	PexFunction func;

public:
	PexNamedFunction() {}
	PexNamedFunction(std::string _name);

	void setName(std::string _name);

	PexStringRef& getName();
	PexFunction& getFunction();
};