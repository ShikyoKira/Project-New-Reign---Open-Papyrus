#pragma once

#include "VarType.h"

struct PexLocal
{
private:
	bool inUsed = false;
	std::shared_ptr<VarType> var;

public:
	PexLocal(VarType _var);
	PexLocal(std::string _name, std::string _type);

	operator VarType() { return *var; }

	papyrusBase::Value::ValueType getType();

	bool isInUsed();
	void activate();
	void deactivate();
};

struct PexLocals : public PexList<std::shared_ptr<PexLocal>>
{
private:
	PexList<std::shared_ptr<PexLocal>> tempList;
	size_t tempCount = 0;

public:
	papyrusBase::Value::ValueType getType(std::string _type);
	papyrusBase::Value::ValueType getType(PexStringRef _type);

	// reference
	PexLocal& get(VarType _var);
	PexLocal& get(std::string _name, std::string _type);
	PexLocal& get(std::string _name, papyrusBase::Value::ValueType _type);
	PexLocal& getTemp(std::string _type);
	PexLocal& getTemp(papyrusBase::Value::ValueType _type);

	// pointer
	std::shared_ptr<PexLocal> getPtr(VarType _var);
	std::shared_ptr<PexLocal> getPtr(std::string _name, std::string _type);
	std::shared_ptr<PexLocal> getPtr(std::string _name, papyrusBase::Value::ValueType _type);
	std::shared_ptr<PexLocal> getTempPtr(std::string _type);
	std::shared_ptr<PexLocal> getTempPtr(papyrusBase::Value::ValueType _type);
};