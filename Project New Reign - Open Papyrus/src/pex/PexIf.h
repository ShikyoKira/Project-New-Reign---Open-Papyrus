#pragma once

#include "PexCondition.h"

struct PexIf
{
	size_t close;
	PexList<PexConditions> ifList;	
};

struct If : public PexIf
{
	size_t size;
	PexConditions cond;

	If(PexConditions _cond);
};

struct ElseIf
{
	size_t size;
	PexConditions cond;

	ElseIf(PexConditions _cond);
};

struct Else
{

};

struct EndIf
{

};
