#include "IValueConverter.h"
#include "Product.h"
#include <iomanip>

using std::setw;
class ProductToRowConverter: public IValueConverter {
public:
    ProductToRowConverter() {}
public:
    string convert(Object*);
    string toString();
};