#pragma once
#include "Object.h"

class IParsable : public Object {
	virtual Object* parse(string) = 0;
};