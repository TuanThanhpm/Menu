#pragma once

#include <string>
#include <sstream>

using std::string, std::stringstream;

class Object {
public:
	virtual string toString() = 0;
};