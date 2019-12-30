#pragma once

#include "PexInstruction.h"
#include "PexDataType.h"

struct PexLocals;

struct PexSingleCondition
{
	enum CompareType
	{
		EQ,
		NOT_EQ,
		LESS_EQ,
		LESS,
		GREAT,
		GREAT_EQ
	};

	CompareType type;
	std::shared_ptr<papyrusBase::Value> value1;
	std::shared_ptr<papyrusBase::Value> value2;

	papyrusBase::dataType* data1;
	papyrusBase::dataType* data2;

	PexSingleCondition() {}
	PexSingleCondition(std::shared_ptr<papyrusBase::Value> _value1, std::shared_ptr<papyrusBase::Value> _value2, CompareType _type);
	PexSingleCondition(papyrusBase::dataType& _data1, papyrusBase::dataType& _data2, CompareType _type);
};

struct PexConditions
{
	enum Type
	{
		OR,
		AND
	};

private:
	bool not = false;

	Type c_type;
	PexSingleCondition condition;
	PexList<PexConditions> conditionStack;

public:
	PexConditions() {}
	PexConditions(std::shared_ptr<papyrusBase::Value> value1, std::shared_ptr<papyrusBase::Value> value2, PexSingleCondition::CompareType _type);
	PexConditions(papyrusBase::dataType& value1, papyrusBase::dataType& value2, PexSingleCondition::CompareType _type);
	PexConditions(PexSingleCondition _cond);
	PexConditions(const PexConditions& group);

	PexConditions operator!();
	PexConditions operator&&(const PexConditions& vand);
	PexConditions operator||(const PexConditions& vand);

	bool isGroup();
	Type getConditionType();

	PexList<PexConditions>& getConditionStack();
	PexInstructions asInstructions(PexLocals* locals, size_t rtn, size_t close);
};
