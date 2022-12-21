#pragma once
#include "Object.h"
#include "IValueConverter.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "ColorsEnum.h"

constexpr auto ProductPerPage = 10;

using std::cout, std::endl;
using std::setw;
using std::vector;

class Table : public Object {
public:
    vector<string> _headers;
    vector<int> _widths;
    vector<Object*> _data;
    IValueConverter* _converter;

public:
    Table(vector<string> headers, vector<int> widths, vector<Object*> objects, IValueConverter* converter);
    string toString();
    void display(int, int, int, int, int);
};