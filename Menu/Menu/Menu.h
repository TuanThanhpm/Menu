#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <memory>
#include <map>
#include <exception>
#include "Object.h"
#include "Table.h"
#include "Utils.h"
#include "KeysEnum.h"
#include "ProductOperationsEnum.h"
#include "ProductToRowConverter.h"
#include "ProductToAttributeListConverter.h"



using std::cout, std::cin, std::getline, std::endl;
using std::swap;
using std::string, std::vector;
using std::map, std::exception;
using std::fstream, std::ios;
using std::unique_ptr, std::shared_ptr, std::make_shared, std::weak_ptr;

class Menu: public Object {
private:
    vector<Object*> _data;

public:
    vector<Object*> data() { return this->_data; }
    void setData(vector<Object*> data) { this->_data = data; }

public:
     void readFile(string);
     void mainMenu();
     void displayAllProducts();
     void addNewProduct();
     void deleteProductById();
     void sortDataById();
     void deleteProduct(int);
     void updateProduct(int);
     string toString();
};