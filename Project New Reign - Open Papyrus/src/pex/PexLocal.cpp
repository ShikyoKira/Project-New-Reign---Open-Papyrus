#include "PexLocal.h"
#include "PexException.h"
#include <boost\algorithm\string.hpp>

using namespace std;

PexLocal::PexLocal(VarType _var)
{
	var = make_shared<VarType>(_var);
}

PexLocal::PexLocal(string _name, string _type)
{
	var = make_shared<VarType>(_name, _type);
}

papyrusBase::Value::ValueType PexLocal::getType()
{
	//string typeS = boost::to_lower_copy(var->getTypeName()->get());
	//string typeL = boost::to_upper_copy(typeS);
	//typeS[0] = typeL[0];
	return StringToType("String");
}

bool PexLocal::isInUsed()
{
	return inUsed;
}

void PexLocal::activate()
{
	inUsed = true;
}

void PexLocal::deactivate()
{
	inUsed = false;
}

PexLocal& PexLocals::get(VarType _var)
{
	return *getPtr(_var);
}

PexLocal& PexLocals::get(string _name, string _type)
{
	return *getPtr(VarType(_name, _type));
}

PexLocal& PexLocals::get(string _name, papyrusBase::Value::ValueType _type)
{
	return *getPtr(VarType(_name, _type));
}

PexLocal& PexLocals::getTemp(string _type)
{
	return *getTempPtr(_type);
}

PexLocal& PexLocals::getTemp(papyrusBase::Value::ValueType _type)
{
	return *getTempPtr(_type);
}

std::shared_ptr<PexLocal> PexLocals::getPtr(VarType _var)
{
	for (auto& var : *this)
	{
		if (var->operator VarType().getName() == _var.getName())
		{
			if (var->operator VarType().getTypeName() == _var.getTypeName()) return var;
			else throw papyrusBase::PexException("Data type not match (Data Name: " + var->operator VarType().getName()->get().operator std::string() + ", Expected Data Type: " +
				_var.getTypeName()->get().operator std::string() + ", Data Type Captured: " + var->operator VarType().getTypeName()->get().operator std::string() + ")");
		}
	}

	push_back(make_shared<PexLocal>(_var));
	return back();
}

shared_ptr<PexLocal> PexLocals::getPtr(std::string _name, std::string _type)
{
	return getPtr(VarType(_name, _type));
}

std::shared_ptr<PexLocal> PexLocals::getPtr(std::string _name, papyrusBase::Value::ValueType _type)
{
	return getPtr(VarType(_name, _type));
}

std::shared_ptr<PexLocal> PexLocals::getTempPtr(std::string _type)
{
	for (auto& temp : tempList)
	{
		if (!temp->isInUsed() && temp->operator VarType().getTypeName() == _type) return temp;
	}

	push_back(make_shared<PexLocal>(VarType("::temp" + to_string(tempCount++), _type)));
	tempList.push_back(back());
	return back();
}

std::shared_ptr<PexLocal> PexLocals::getTempPtr(papyrusBase::Value::ValueType _type)
{
	for (auto& temp : tempList)
	{
		if (!temp->isInUsed() && temp->operator VarType().getTypeName() == TypeToString(_type)) return temp;
	}

	push_back(make_shared<PexLocal>(VarType("::temp" + to_string(tempCount++), _type)));
	tempList.push_back(back());
	return back();
}

papyrusBase::Value::ValueType PexLocals::getType(std::string _type)
{
	for (auto& local : *this)
	{
		if (local->operator VarType().getName()->get() == _type) return local->getType();
	}

	throw papyrusBase::PexException("Data has not been defined nor declared (Data: " + _type + ")");
}

papyrusBase::Value::ValueType PexLocals::getType(PexStringRef _type)
{
	for (auto& local : *this)
	{
		if (local->operator VarType().getName() == _type) return local->getType();
	}

	throw papyrusBase::PexException("Data has not been defined nor declared (Data: " + _type->get().operator std::string() + ")");
}
