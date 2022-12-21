#include "ProductToRowConverter.h"


string ProductToRowConverter::convert(Object* object) {
    Product* product = dynamic_cast<Product*>(object);

    stringstream builder;
    builder << setw(3) << product->id() << "|";
    builder << setw(30) << product->name() << "|";
    builder << setw(15) << product->price() << "|";

    string result = builder.str();
    return result;
}

string ProductToRowConverter::toString() {
    return "ProductToRowConverter";
}
