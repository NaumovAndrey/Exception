#include <iostream>
#include "vector"
#include <map>
#include <string>

using namespace std;

map<string, int> store_db;

class CheckingPositiveNumberException: public exception
{
public:
    const char *what() const noexcept override
    {
        return "The number of products must be greater than zero"; //значение <= 0
    }
};

bool addStore_db()
{
    string item;
    int quantity;

    cout << "Article: ";
    getline(cin, item);
    if(item.empty())
    {
        return true;
    }
    cout << "Quantity: ";
    cin >> quantity;
    cin.ignore();
    if(quantity <= 0)
    {
        throw CheckingPositiveNumberException();

    }
    store_db[item] = quantity;

    return false;
}

int main()
{
    setlocale(LC_ALL, "rus");

    // Заполнение базы данных магазина

    cout << "Enter the article and the number of products in the store (enter an empty line to complete the input):"
         << endl; //Введите артикул и количество товаров в магазине (введите пустую строку для завершения ввода).
    while(true)
    {
        try
        {
            if (addStore_db()) break;
        }
        catch(const CheckingPositiveNumberException &e)
        {
            cerr << "Exception: " << e.what() << endl;

        }
    }



    return 0;
}
