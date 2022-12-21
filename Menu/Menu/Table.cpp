#include "Table.h"


Table::Table(vector<string> headers, vector<int> widths, vector<Object*> objects, IValueConverter* converter) {
    _headers = headers;
    _widths = widths;
    _data = objects;
    _converter = converter;
}
string Table::toString() {
    return "Table";
}

void Table::display(int selectedLine, int selectedPage, int pageCount, int start, int end) {
    int productCount = static_cast<int> (this->_data.size());
    int productCurrent = end - start;
  
    cout << "All product. Page " << selectedPage << "/" << pageCount
        << ". Displaying " << productCurrent << "/" << productCount << endl;


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int k = static_cast<int>(Colors::lightBlue);

    for (int i = 0; i < _headers.size(); i++) {
        cout << setw(_widths[i]) << _headers[i] << "|";
    }
    cout << endl;

    int sum = 0;
    for (auto &width : _widths) {
        sum += width;
    }
    sum += _headers.size();

    for (int i = 0; i < sum; i++) {
        cout << "=";
    }
    cout << endl;

    for (int i = start; i < end; i++) {
        if (selectedLine == i) {
            SetConsoleTextAttribute(hConsole, k);
        }
        else {
            SetConsoleTextAttribute(hConsole, static_cast<int>(Colors::white));
        }
        string line = _converter->convert(_data[i]);
        cout << line << endl;
    }
    SetConsoleTextAttribute(hConsole, static_cast<int>(Colors::white));

    cout << "\nUse left and right arrow to go to next/previous page"
        << "\nTo delete a row, select then press del"
        << "\nTo view the detail of a product for editing, press enter"
        << "\nPress escape to go back to main menu";
}