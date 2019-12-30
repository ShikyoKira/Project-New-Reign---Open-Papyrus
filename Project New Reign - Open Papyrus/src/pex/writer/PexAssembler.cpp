#include "PexAssembler.h"
#include "Writer.h"

void WriterHeader(PexWriter& writer, PexFile& pex);
void WriteStringTable(PexWriter& writer, PexFile& pex);
void WriteDebugInfo(PexWriter& writer, PexFile& pex);
void WriteUserFlags(PexWriter& writer, PexFile& pex);
void WriterObject(PexWriter& writer, PexFile& pex);
void WriterValue(PexWriter& writer, PexFile& pex, papyrusBase::Value& value);
void WriteProperties(PexWriter& writer, PexFile& pex, papyrusBase::Property& prop);
void WriteFunction(PexWriter& writer, PexFile& pex, PexFunction& func);
void WriteState(PexWriter& writer, PexFile& pex, papyrusBase::State& state);

void WritePexFile(PexFile& pex, std::string dir)
{
	if (dir.back() != '\\' && dir.back() != '/') dir.push_back('\\');

	boost::filesystem::path filename(dir + pex.sourceFileName);
	filename.replace_extension(".pex");
	PexWriter writer(filename.string());
	
	if (writer.GetFile())
	{
		WriterHeader(writer, pex);
		WriteStringTable(writer, pex);
		WriteDebugInfo(writer, pex);
		WriteUserFlags(writer, pex);
		WriterObject(writer, pex);
	}
}

void WriterHeader(PexWriter& writer, PexFile& pex)
{
	writer.WriteLine(pex.magic, pex.version, pex.gameId, pex.time, pex.sourceFileName, pex.userName, pex.machineName);
}

void WriteStringTable(PexWriter& writer, PexFile& pex)
{
	writer.WriteLine(pex.stringTable->size());

	for (auto& s : *pex.stringTable)
	{
		writer.WriteLine(s.length());
		writer.WriteLine(s);
	}
}

void WriteDebugInfo(PexWriter& writer, PexFile& pex)
{
	writer.WriteLine(pex.debugInfo.getHasDebug());

	if (!pex.debugInfo.getHasDebug()) return;

	writer.WriteLine(pex.debugInfo.getModifTime(), pex.debugInfo.getFunctions().size());

	for (auto& f : pex.debugInfo.getFunctions())
	{
		writer.WriteLine(f->objectName->getIndex(), f->stateName->getIndex(), f->functionName->getIndex(), f->functionType, f->lineNumbers.size());

		for (auto& lineNum : f->lineNumbers)
		{
			writer.WriteLine(lineNum);
		}
	}
}

void WriteUserFlags(PexWriter& writer, PexFile& pex)
{
	writer.WriteLine(pex.userFlags.size());

	for (auto& flag : pex.userFlags)
	{
		writer.WriteLine(flag.getName()->getIndex(), flag.getFlagIndex());
	}
}

void WriterObject(PexWriter& writer, PexFile& pex)
{
	writer.WriteLine(pex.pexObjects.size());

	for (auto& obj : pex.pexObjects)
	{
		writer.WriteLine(obj.nameIndex->getIndex(), obj.size, obj.data.parentName->getIndex(), obj.data.docString->getIndex(), obj.data.userFlags,
			obj.data.autoStateName->getIndex(), obj.data.Variables.size());

		for (auto& var : obj.data.Variables)
		{
			writer.WriteLine(var.getNameIndex(), var.getTypeIndex(), var.getUserFlags());
			WriterValue(writer, pex, var.getDefaultValue());
		}

		writer.WriteLine(obj.data.numProperties.size());

		for (auto& prop : obj.data.numProperties)
		{
			WriteProperties(writer, pex, prop);
		}

		writer.WriteLine(obj.data.numStates.size());

		for (auto& state : obj.data.numStates)
		{
			WriteState(writer, pex, state);
		}
	}
}

void WriterValue(PexWriter& writer, PexFile& pex, papyrusBase::Value& value)
{
	unsigned char type = value.getType();
	writer.WriteLine(type);

	switch (type)
	{
		case 0:
		{
			break;
		}
		case 1:
		{
			writer.WriteLine(value.getString()->getIndex());
			break;
		}
		case 2:
		{
			writer.WriteLine(value.getString()->getIndex());
			break;
		}
		case 3:
		{
			writer.WriteLine(value.getInt());
			break;
		}
		case 4:
		{
			writer.WriteLine(value.getFloat());
			break;
		}
		case 5:
		{
			writer.WriteLine(value.getBool());
		}
	}
}

void WriteProperties(PexWriter& writer, PexFile& pex, papyrusBase::Property& prop)
{
	writer.WriteLine(prop.getNameIndex(), prop.getTypeIndex(), prop.getDocStringIndex(), prop.getUserFlags(), prop.getFlags());

	if (prop.isAuto()) writer.WriteLine(prop.getAutoNameIndex());
	else if (prop.isReadable()) WriteFunction(writer, pex, prop.getReader());
	else if (prop.isWritable()) WriteFunction(writer, pex, prop.getWriter());
}

void WriteFunction(PexWriter& writer, PexFile& pex, PexFunction& func)
{
	writer.WriteLine(func.getReturnType()->getIndex(), func.getDoc()->getIndex(), func.getUserFlags(), func.getFlags(), func.getParameters().size());

	for (auto& param : func.getParameters())
	{
		writer.WriteLine(param.getName()->getIndex(), param.getTypeName()->getIndex());
	}

	writer.WriteLine(func.getLocals().size());

	for (auto& local : func.getLocals())
	{
		writer.WriteLine(local->operator VarType().getName()->getIndex(), local->operator VarType().getTypeName()->getIndex());
	}

	writer.WriteLine(func.asInstructions().size());

	for (auto& instr : func.asInstructions())
	{
		writer.WriteLine(static_cast<unsigned char>(instr.getCode()));

		for (auto& arg : instr.getArgs())
		{
			switch (arg->getType())
			{
				case 1:
				{
					writer.WriteLine(arg->getString()->getIndex());
					break;
				}
				case 2: 
				{
					writer.WriteLine(arg->getString()->getIndex());
					break;
				}
				case 3:
				{
					writer.WriteLine(arg->getInt());
					break;
				}
				case 4:
				{
					writer.WriteLine(arg->getFloat());
					break;
				}
				case 5:
				{
					writer.WriteLine(arg->getBool());
				}
			}
		}
	}
}

void WriteState(PexWriter& writer, PexFile& pex, papyrusBase::State& state)
{
	writer.WriteLine(state.name->getIndex(), state.functions.size());

	for (auto& func : state.functions)
	{
		writer.WriteLine(func.getName()->getIndex());
		WriteFunction(writer, pex, func.getFunction());
	}
}
