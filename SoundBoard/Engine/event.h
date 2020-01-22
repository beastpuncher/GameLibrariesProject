#pragma once
#include "id.h"
#include "varient.h"

class  Entity;

struct Event
{

	ID eventID;
	Entity* sender;
	Entity* reciver;
	Varient varient;
	Varient varients[3];

	Event() {}
};