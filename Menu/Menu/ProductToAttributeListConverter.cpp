#include "ProductToAttributeListConverter.h"


string ProductToAttributeListConverter::convert(Object* object) {
    Product* product = dynamic_cast<Product*>(object);

    stringstream builder;
    builder << "\nSelected product:\n";
    builder << "ID = " << product->id() << ", ";
    builder << "Name = " << product->name() << ", ";
    builder << "Price = " << product->price() << "\n";

    string result = builder.str();
    return result;
}

string ProductToAttributeListConverter::toString() {
    return "ProductToAttributeListConverter";
}
