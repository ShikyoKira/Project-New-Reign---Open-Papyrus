#pragma once

#include "PexStringRef.h"
#include "PexCondition.h"
#include "PexReturn.h"
#include "PexAssignIdentifier.h"

struct PexLocals;
struct PexLocal;

namespace papyrusBase
{
	struct Return;

	struct Value : public std::enable_shared_from_this<Value>
	{
		enum ValueType
		{
			None = 0,
			Identifier = 1,
			String = 2,
			Integer = 3,
			Float = 4,
			Bool = 5
		};

	private:
		typedef PexLocals* PexIdentifier;

		ValueType type;

		union data
		{
			PexLocal* identity;
			PexStringRef string;
			int integer;
			float real;
			bool boolean;
			data() {}
			~data() {}
		} value;

		void copy(const Value& _value);

	public:
		inline Value() : type(None) {}
		Value(int _int);				// int
		Value(size_t _int);				// int
		Value(float _float);			// float
		Value(bool _bool);				// bool
		Value(std::string _string);		// string
		Value(PexStringRef _string);	// string
		Value(PexIdentifier _local, ValueType _type);		// temporary identifier
		Value(std::string _string, PexIdentifier _local, ValueType _type = None);		// identifier
		Value(PexStringRef _string, PexIdentifier _local, ValueType _type = None);		// identifier
		Value(const Value& _data);
		Value(dataType& _data);

		PexStringRef getString();
		int getInt();
		float getFloat();
		unsigned char getBool();
		papyrusBase::Value::ValueType getType();
		PexLocal* getLocal();
		void typeCheck(ValueType n_type);

		void set(int _int);
		void set(float _real);
		void set(bool _bool);
		void set(std::string _string);
		void set(PexStringRef _string);
		void set(ValueType _type);
		void set(PexIdentifier _local, ValueType _type);
		void set(std::string _string, PexIdentifier _local, ValueType _type);
		void set(PexStringRef _string, PexIdentifier _local, ValueType _type);

		Value& operator=(Value _value);
		PexConditions operator==(Value _value);
		PexConditions operator!=(Value _value);
		PexConditions operator<=(Value _value);
		PexConditions operator>=(Value _value);
		PexConditions operator<(Value _value);
		PexConditions operator>(Value _value);
	};

	struct Cast
	{
		bool end = false;
		dataType fromData;
		dataType toData;

		Cast(dataType _toData, dataType _fromData) : toData(_toData), fromData(_fromData) {}
	};

	struct Int : public dataType
	{
	private:
		int data;

	public:
		Int(std::string name = "\"empty\"");
		Int(const Int& _data);
		Int(int _data);

		operator int();
		Int& operator=(int _data);
		PexAssignIdenfier operator=(Int _data);

		Cast asString();
		Cast asBool();
		Cast asFloat();
		Cast operator=(Cast _data);

		PexConditions operator==(dataType& _value);
		PexConditions operator!=(dataType& _value);
		PexConditions operator<=(dataType& _value);
		PexConditions operator>=(dataType& _value);
		PexConditions operator<(dataType& _value);
		PexConditions operator>(dataType& _value);

		PexConditions operator==(int _value);
		PexConditions operator!=(int _value);
		PexConditions operator<=(int _value);
		PexConditions operator>=(int _value);
		PexConditions operator<(int _value);
		PexConditions operator>(int _value);
	};

	struct String : public dataType
	{
	private:
		std::string data;

	public:
		String(std::string name = "\"empty\"");
		String(const String& _data);

		operator std::string();
		String& operator=(std::string _data);
		PexAssignIdenfier operator=(String _data);

		Cast asInt();
		Cast asBool();
		Cast asFloat();
		Cast operator=(Cast _data);

		PexConditions operator==(dataType& _value);
		PexConditions operator!=(dataType& _value);
		PexConditions operator<=(dataType& _value);
		PexConditions operator>=(dataType& _value);
		PexConditions operator<(dataType& _value);
		PexConditions operator>(dataType& _value);

		PexConditions operator==(std::string _value);
		PexConditions operator!=(std::string _value);
		PexConditions operator<=(std::string _value);
		PexConditions operator>=(std::string _value);
		PexConditions operator<(std::string _value);
		PexConditions operator>(std::string _value);
	};

	struct Float : public dataType
	{
	private:
		float data;

	public:
		Float(std::string name = "\"empty\"");
		Float(const Float& _data);

		operator float() { return data; }

		Float& operator=(float _data);
		PexAssignIdenfier operator=(Float _data);

		Cast asString();
		Cast asInt();
		Cast asBool();
		Cast operator=(Cast _data);

		PexConditions operator==(dataType& _value);
		PexConditions operator!=(dataType& _value);
		PexConditions operator<=(dataType& _value);
		PexConditions operator>=(dataType& _value);
		PexConditions operator<(dataType& _value);
		PexConditions operator>(dataType& _value);

		PexConditions operator==(float _value);
		PexConditions operator!=(float _value);
		PexConditions operator<=(float _value);
		PexConditions operator>=(float _value);
		PexConditions operator<(float _value);
		PexConditions operator>(float _value);
	};

	struct Bool : public dataType
	{
	private:
		bool data;

	public:
		Bool(std::string name = "\"empty\"");
		Bool(const Bool& _data);

		operator bool();
		Bool& operator=(bool _data);
		PexAssignIdenfier operator=(Bool _data);

		Cast asString();
		Cast asInt();
		Cast asFloat();
		Cast operator=(Cast _data);

		PexConditions operator==(dataType& _value);
		PexConditions operator!=(dataType& _value);
		PexConditions operator<=(dataType& _value);
		PexConditions operator>=(dataType& _value);
		PexConditions operator<(dataType& _value);
		PexConditions operator>(dataType& _value);

		PexConditions operator==(bool _value);
		PexConditions operator!=(bool _value);
		PexConditions operator<=(bool _value);
		PexConditions operator>=(bool _value);
		PexConditions operator<(bool _value);
		PexConditions operator>(bool _value);
	};
	
#define PEXCAST(toData, fromData) Cast(toData, fromData);
}
