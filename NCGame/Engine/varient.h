#pragma once
#include "vector2D.h"

struct Varient
{

	enum eType
	{
		INTEGER,
		FLOAT,
		BOOL,
		VECTOR2D
	};

	eType type;

	union
	{
		int asInt;
		float asFloat;
		bool asBool;
		Vector2D asVector2D;
	};
	Varient() {}

};