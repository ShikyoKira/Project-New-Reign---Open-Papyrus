#include "PexCondition.h"
#include "PexLocal.h"
#include "PexValue.h"
#include "PexException.h"

using namespace std;
using namespace papyrusBase;

Value::ValueType getValueType(shared_ptr<Value> value)
{
	return value->getType();
}

PexSingleCondition::PexSingleCondition(shared_ptr<Value> _value1, shared_ptr<Value> _value2, CompareType _type)
{
	value1 = _value1;
	value2 = _value2;
	type = _type;
}

PexSingleCondition::PexSingleCondition(papyrusBase::dataType& _data1, papyrusBase::dataType& _data2, CompareType _type)
{
	data1 = &_data1;
	data2 = &_data2;
	type = _type;
}

PexConditions::PexConditions(shared_ptr<Value> value1, shared_ptr<Value> value2, PexSingleCondition::CompareType _type)
{
	if (value1 == nullptr || value2 == nullptr) throw PexException("1 or 2 comparing data is not found");
	if (value1->getType() != value2->getType()) throw PexException("Data type mismatch during comparison");
	condition = PexSingleCondition(value1, value2, _type);
}

PexConditions::PexConditions(papyrusBase::dataType& data1, papyrusBase::dataType& data2, PexSingleCondition::CompareType _type)
{
	if (data1.type != data2.type) throw PexException("Data type mismatch during comparison");
	condition = PexSingleCondition(data1, data2, _type);
}

PexConditions::PexConditions(PexSingleCondition _cond)
{
	if (_cond.value1 == nullptr || _cond.value2 == nullptr) throw PexException("1 or 2 comparing data is not found");
	if (_cond.value1->getType() != _cond.value2->getType()) throw PexException("Data type mismatch during comparison");
	condition = _cond;
}

PexConditions::PexConditions(const PexConditions& group)
{
	conditionStack.push_back(group);
}

PexConditions PexConditions::operator!()
{
	PexConditions cond = *this;
	cond.not = true;
	return cond;
}

PexConditions PexConditions::operator&&(const PexConditions& vand)
{
	if (isGroup())
	{
		conditionStack.push_back(vand);
		return *this;
	}
	else
	{
		PexConditions cond;
		cond.conditionStack.push_back(*this);
		cond.conditionStack.push_back(vand);
		return cond;
	}
}

PexConditions PexConditions::operator||(const PexConditions& vand)
{
	c_type = OR;

	if (isGroup())
	{
		conditionStack.push_back(vand);
		return *this;
	}
	else
	{
		PexConditions cond;
		cond.conditionStack.push_back(*this);
		cond.conditionStack.push_back(vand);
		return cond;
	}
}

bool PexConditions::isGroup()
{
	return conditionStack.size() > 0;
}

PexConditions::Type PexConditions::getConditionType()
{
	return c_type;
}

PexList<PexConditions>& PexConditions::getConditionStack()
{
	return conditionStack;
}

PexInstructions PexConditions::asInstructions(PexLocals* locals, size_t rtn, size_t close)
{
	if (isGroup())
	{
		auto& stack = getConditionStack();
		PexInstructions store;
		PexInstructions temp = stack.back().asInstructions(locals, rtn, close);

		if (c_type == OR)
		{
			temp.back().setCode(PexInstruction::OpCode::Jmpt);
			temp.back().getArgs().back()->set(static_cast<int>(rtn + 1));
			close = 0;
		}

		store.insert(store.begin(), temp.begin(), temp.end());

		for (unsigned int i = stack.size() - 2; i >= 0; --i)
		{
			temp = stack[i].asInstructions(locals, rtn + store.size(), close + store.size());
			store.insert(store.begin(), temp.begin(), temp.end());
		}

		return store;
	}
	else
	{
		PexInstructions instrList;
		instrList.push_back(PexInstruction());
		auto& cur = instrList.back();
		cur.setCode(PexInstruction::OpCode::Cmp_Eq);
		auto& args = cur.getArgs();
		shared_ptr<Value> temp = make_shared<Value>(locals, getValueType(condition.value1));
		temp->getLocal()->activate();
		args.emplace_back(temp);
		args.emplace_back(condition.value1);
		args.emplace_back(condition.value2);
		instrList.push_back(PexInstruction());
		cur = instrList.back();

		if (getConditionType() == PexConditions::AND)
		{
			cur.setCode(PexInstruction::OpCode::Jmpf);
			args = cur.getArgs();
			args.emplace_back(temp);
			args.emplace_back(make_shared<Value>(close + 1));
			temp->getLocal()->deactivate();
		}
		else
		{
			cur.setCode(PexInstruction::OpCode::Jmpt);
			args = cur.getArgs();
			args.emplace_back(temp);
			args.emplace_back(make_shared<Value>(rtn + 1));
			temp->getLocal()->deactivate();
		}

		return instrList;
	}
}
