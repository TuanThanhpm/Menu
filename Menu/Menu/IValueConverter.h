#pragma once
#include "Object.h"

class IValueConverter : public Object {
public:
	virtual string convert(Object*) = 0;
};