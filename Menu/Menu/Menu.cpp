#include "Menu.h"

void Menu::mainMenu() {
    readFile("mockData.txt");
    vector<string> hints = {
        "1. Display all products(paging support - table)",
        "2. Add a new product",
        "3. Delete a product by id",
    };
    int selectedLine = 0, start = 0, end = static_cast<int> (hints.size());

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = static_cast<int>(Colors::lightBlue);

    while (true) {
        cout << "MyShop App.Please select a function :\n";
        for (int i = 0; i < hints.size(); i++) {
            if (selectedLine == i) {
                SetConsoleTextAttribute(hConsole, k);
            }
            else {
                SetConsoleTextAttribute(hConsole, static_cast<int>(Colors::white));
            }
            cout << hints[i] << endl;
        }
        SetConsoleTextAttribute(hConsole, static_cast<int>(Colors::white));
        cout << "\nPress escape to quit";

        unsigned char key = _getch();

        if (key == static_cast<int>(Keys::arrow)) {
            unsigned char arrow = _getch();

            switch (arrow) {
            case static_cast<int> (Keys::up):
                if (selectedLine > start) {
                    selectedLine--;
                }
                else {
                    selectedLine = end - 1;
                }
                break;
            case static_cast<int> (Keys::down):
                if (selectedLine < end - 1) {
                    selectedLine++;
                }
                else {
                    selectedLine = start;
                }
                break;
            }
        }
        else {
            switch (key) {
            case static_cast<int> (Keys::enter):
                SetConsoleTextAttribute(hConsole, static_cast<int>(Colors::white));
                system("cls");
                switch (selectedLine + 1) {
                case ProductOperation::displayAll:
                    displayAllProducts();
                    break;
                case ProductOperation::addNew:
                    addNewProduct();
                    break;
                case ProductOperation::deleteById:
                    deleteProductById();
                    break;
                }
                break;
            case static_cast<int> (Keys::escape):
                system("cls");
                return;
                break;
            }
        }

        SetConsoleTextAttribute(hConsole, static_cast<int>(Colors::white));
        system("cls");
    }
   
}

void Menu::readFile(string filename) {
    fstream reader;
    reader.open(filename, ios::in);
    string temp = "";
    if (!reader) {
        throw exception("Can not open file!");
    }
    else {
        while (!reader.eof()) {
            getline(reader, temp);
            vector<string> token = Utils::String::split(temp, " | ");
            Object* result = new Product(token[0], token[1], token[2]);
            _data.push_back(result);
        }
    }
    reader.close();
}

void Menu::displayAllProducts() {
    sortDataById();
    vector<string> headers = { "ID", "Name", "Price" };
    vector<int> widths = { 3, 30, 15 };

    int selectedLine = 0, selectedPage = 1;
    int start = 0, end = ProductPerPage;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = static_cast<int>(Colors::lightBlue);

    IValueConverter* converter = new ProductToRowConverter();
    while (true)
    {
        string temp = "";
        int distance, productCount, pageCount;

        distance = 0;
        productCount = static_cast<int> (_data.size());
        pageCount = productCount / ProductPerPage;
        if ((productCount % ProductPerPage) != 0)
            pageCount += 1;

        Table table(headers, widths, _data, converter);
        table.display(selectedLine, selectedPage, pageCount, start, end);

        unsigned char key = _getch();

        if (key == static_cast<int>(Keys::arrow)) {
            unsigned char arrow = _getch();

            switch (arrow) {
            case static_cast<int> (Keys::up):
                if (selectedLine > start) {
                    selectedLine--;
                }
                else {
                    selectedLine = end - 1;
                }
                break;
            case static_cast<int> (Keys::down):
                if (selectedLine < end - 1) {
                    selectedLine++;
                }
                else {
                    selectedLine = start;
                }
                break;
            case static_cast<int> (Keys::left):
                if (selectedPage > 1) {
                    distance = end - start;
                    start -= ProductPerPage;
                    if (distance < ProductPerPage)
                        end = productCount - distance;
                    else
                        end -= ProductPerPage;
                    selectedPage--;
                    selectedLine = start;
                }
                break;
            case static_cast<int> (Keys::right):
                if (selectedPage < pageCount) {
                    start += ProductPerPage;
                    end += ProductPerPage;
                    if (end > productCount)
                        end = productCount;
                    selectedPage++;
                    selectedLine = start;
                }
                break;
            case static_cast<int> (Keys::del):
                system("cls");
                deleteProduct(selectedLine);
                break;
            }
        }
        else {
            switch (key) {
            case static_cast<int> (Keys::enter):
                system("cls");
                updateProduct(selectedLine);
                break;
            case static_cast<int> (Keys::escape):
                system("cls");
                return;
                break;
            }
        }
        SetConsoleTextAttribute(hConsole, static_cast<int>(Colors::white));
        system("cls");
    }
    delete converter;
}

void Menu::addNewProduct() {
    string temp, id, name, price;
    temp = id = name = price = "";

    cout << "Do you want to add new a product? (Y/N) ";
    cin >> temp;
    if (temp != "Y") {
        return;
    }
    else {
        map<string, bool> m_id, m_name;
        for (int i = 0; i < _data.size(); i++) {
            Product* product = dynamic_cast<Product*>(_data[i]);
            m_id[product->id()] = true;
            m_name[product->name()] = true;
        }
        cout << "Enter new id: ";
        cin >> id;
        cin.ignore();
        cout << "Enter new name: ";
        getline(cin, name);
        cout << "Enter new price: ";
        cin >> price;
        if (m_id[id] || m_name[name]) {
            cout << "Data (id,name) is exist!\n";
            system("pause");
        }
        else {
            Object* new_product = new Product(id, name, price);
            this->_data.push_back(new_product);
        }
    }
}

void Menu::deleteProductById() {
    string temp, id;
    temp = id = "";
    int index = -1;

    cout << "Enter id: ";
    cin >> id;

    for (int i = 0; i < _data.size(); i++) {
        Product* product = dynamic_cast<Product*>(_data[i]);
        if (product->id() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "No data!\n\n";
        system("pause");
    }
    else {
        IValueConverter* converter = new ProductToAttributeListConverter();
        cout << converter->convert(_data[index]);

        cout << "\nDo you want to delete product? (Y/N) ";
        cin >> temp;
        if (temp != "Y") {
            return;
        }
        else{
            _data.erase(_data.begin() + index);
        }
        delete converter;
    }
}

void Menu::sortDataById() {
    for (int i = 0; i < _data.size() - 1; i++) {
        Product* p_a = dynamic_cast<Product*>(_data[i]);
        for (int j = i + 1; j < _data.size(); j++) {
            Product* p_b = dynamic_cast<Product*>(_data[j]);
            int num_a = stoi(p_a->id());
            int num_b = stoi(p_b->id());
            if (num_a > num_b)
                swap(_data[i], _data[j]);
        }
    }
}

void Menu::deleteProduct(int selectedLine) {
    string temp = "";
    IValueConverter* converter = new ProductToAttributeListConverter();
    cout << converter->convert(_data[selectedLine]);

    cout << "\nDo you want to delete this product? (Y/N) ";
    cin >> temp;
    if (temp != "Y") {
        return;
    }
    else {
        vector<Object*>::iterator it;
        it = _data.begin() + selectedLine;
        _data.erase(it);
    }
    delete converter;
}

void Menu::updateProduct(int selectedLine) {
    string temp = "";
    IValueConverter* converter = new ProductToAttributeListConverter();
    cout << converter->convert(_data[selectedLine]);

    cout << "\nDo you want to edit? (Y/N) ";
    cin >> temp;
    cin.ignore();
    if (temp != "Y") {
        return;
    }  
    else {
        Product* current = dynamic_cast<Product*>(_data[selectedLine]);
        string id, name, price;

        id = current->id();
        name = price = "";
        cout << "Enter new name:";
        getline(cin, name);
        cout << "Enter new price:";
        cin >> price;

        Object* product = new Product(id, name, price);
        _data[selectedLine] = product;

        delete current;
    }
    delete converter;
}

string Menu::toString() {
    return "Menu";
}