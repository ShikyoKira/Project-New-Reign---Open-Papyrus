#pragma once

#include "src\pex\PexFile.h"

PexNamedFunction Event(std::string name, std::string returnType, bool isGlobal, bool isNative, std::vector<VarType> _param, unsigned int flag, std::string doc);
