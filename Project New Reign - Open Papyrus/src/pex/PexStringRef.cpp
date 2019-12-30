#include "PexStringRef.h"
#include "src\pex\PexException.h"


papyrusBase::PexStringIndexRef::PexStringIndexRef(std::string _string)
{
	set(_string);
}

papyrusBase::PexStringIndexRef::PexStringIndexRef(unsigned short _index)
{
	set(_index);
}

PexStringData papyrusBase::PexStringIndexRef::operator+(std::string _string)
{
	return PexStringData(get().operator std::string() + _string);
}

PexStringData papyrusBase::PexStringIndexRef::operator+(PexStringData _string)
{
	return PexStringData(get().operator std::string() + _string.operator std::string());
}

bool papyrusBase::PexStringIndexRef::operator==(std::string _string)
{
	return get() == _string;
}

bool papyrusBase::PexStringIndexRef::operator!=(std::string _string)
{
	return get() != _string;
}

void papyrusBase::PexStringIndexRef::set(std::string n_string)
{
	try
	{
		index = find(n_string);
	}
	catch (papyrusBase::PexException&)
	{
		index = static_cast<unsigned short>(tableRef.size());
		tableRef.push_back(n_string);
	}
}

void papyrusBase::PexStringIndexRef::set(unsigned short n_index)
{
	if (n_index >= tableRef.size())
	{
		throw papyrusBase::PexException("Index is out of scope. Index: " + std::to_string(n_index));
	}

	index = n_index;
}

unsigned short papyrusBase::PexStringIndexRef::find(std::string n_string)
{
	for (unsigned short _index = 0; _index < tableRef.size(); ++_index)
	{
		if (tableRef[_index] == n_string) return _index;
	}

	throw papyrusBase::PexException("String not found. String: " + std::to_string(index));
}

PexStringData& papyrusBase::PexStringIndexRef::get()
{
	return tableRef[index];
}

papyrusBase::PexStringIndexRef& papyrusBase::PexStringIndexRef::operator=(std::string n_string)
{
	set(n_string);
	return *this;
}

papyrusBase::PexStringIndexRef& papyrusBase::PexStringIndexRef::operator=(unsigned short n_index)
{
	set(n_index);
	return *this;
}

unsigned short papyrusBase::PexStringIndexRef::getIndex()
{
	return index;
}

PexStringRef::PexStringRef(std::string _string)
{
	*this = ADD_PEXSTRING(_string);
}

PexStringRef& PexStringRef::operator=(std::shared_ptr<papyrusBase::PexStringIndexRef> _string)
{
	*this = static_cast<PexStringRef&>(_string);
	return *this;
}

PexStringRef& PexStringRef::operator=(std::string _string)
{
	*this = ADD_PEXSTRING(_string);
	return *this;
}

bool PexStringRef::operator==(std::string _string)
{
	return *this->get() == _string;
}

bool PexStringRef::operator!=(std::string _string)
{
	return *this->get() != _string;
}

bool PexStringRef::operator==(PexStringRef& _string)
{
	return this->get()->get() == _string->get();
}

bool PexStringRef::operator!=(PexStringRef& _string)
{
	return this->get()->get() != _string->get();
}
