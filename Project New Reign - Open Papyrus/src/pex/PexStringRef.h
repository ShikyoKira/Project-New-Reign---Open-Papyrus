#pragma once

#include <string>
#include <memory>
#include "StringTable.h"

#define ADD_PEXSTRING(param) std::make_shared<papyrusBase::PexStringIndexRef>(param)

namespace papyrusBase
{
	struct PexStringIndexRef
	{
	private:
		unsigned short index;

	public:
		PexStringIndexRef() {}
		PexStringIndexRef(std::string _string);
		PexStringIndexRef(unsigned short _index);

		PexStringData operator+(std::string _string);
		PexStringData operator+(PexStringData _string);

		bool operator==(std::string _string);
		bool operator!=(std::string _string);

		void set(std::string n_string);
		void set(unsigned short n_index);

		unsigned short find(std::string n_string);
		unsigned short getIndex();

		PexStringData& get();

		PexStringIndexRef& operator=(std::string n_string);
		PexStringIndexRef& operator=(unsigned short n_index);
	};
}

struct PexStringRef : public std::shared_ptr<papyrusBase::PexStringIndexRef>
{
	PexStringRef() {}
	PexStringRef(std::string _string);
	PexStringRef& operator=(std::shared_ptr<papyrusBase::PexStringIndexRef> _string);
	PexStringRef& operator=(std::string _string);
	bool operator==(std::string _string);
	bool operator!=(std::string _string);
	bool operator==(PexStringRef& _string);
	bool operator!=(PexStringRef& _string);
};
