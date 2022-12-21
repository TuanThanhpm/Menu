#pragma once
#include "Object.h"

class Product : public Object {
private:
	string _id;
	string _name;
	string _price;

public:
	Product();
	Product(string, string, string);

public:
	string id() { return this->_id; }
	string name() { return this->_name; }
	string price() { return this->_price; }
	void setID(string id) { this->_id = id; }
	void setName(string name) { this->_name = name; }
	void setPrice(string price) { this->_price = price; }

public:
	string toString();
	bool checkCategories(string, string, string);
};