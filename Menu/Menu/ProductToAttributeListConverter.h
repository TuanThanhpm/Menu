#include "IValueConverter.h"
#include "Product.h"
#include <iomanip>

using std::setw;
class ProductToAttributeListConverter : public IValueConverter {
public:
    ProductToAttributeListConverter() {}
public:
    string convert(Object*);
    string toString();
};