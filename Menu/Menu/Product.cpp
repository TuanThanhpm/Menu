#include "Product.h"
#include <regex>
#include <exception>

using std::regex, std::regex_match;
using std::exception;

Product::Product() {
	this->_id = "000";
	this->_name = "Macbook";
	this->_price = "25000000";
}

Product::Product(string id, string name, string price) {
	if (!checkCategories(id, name, price)) {
		throw exception("Invalid value. ID must be a number. Name must not be none. Price must be larger than or equal to 1000.");
	}
	else {
		this->_id = id;
		this->_name = name;
		this->_price = price;
	}
}

bool Product::checkCategories(string id, string name, string price) {
	const regex idPattern("^[0-9]+$");
	const regex pricePattern("^[1-9][0-9]+$");

	if (!regex_match(id, idPattern) || name == "" || !regex_match(price, pricePattern)) {
		return false;
	}
	return true;
}

string Product::toString() {
	return "Product";
}