#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>

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

class InvalidInputException: public exception
{
public:

    const char *what() const noexcept override
    {
        return "The assignment is not a number"; //не число
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

class Basket
{
    string item;
    int quantity;

private:
    map<string, int> basket;

public:
    void add(const string &item, int quantity)
    {
        auto it = store_db.find(item);
        if(it != store_db.end())
        {
            if(quantity > it->second)
            {
                throw invalid_argument("The specified quantity of goods is not available");
            }
            it->second -= quantity;
            basket[item] += quantity;
        } else
        {
            throw invalid_argument("There is no such item in the store");
        }
    }

    void remove(const string &item, int quantity)
    {
        auto it = basket.find(item);
        if(it != basket.end())
        {
            if(quantity > it->second)
            {
                throw invalid_argument("The specified quantity of goods is not available");
            }
            it->second -= quantity;
            if(it->second == 0)
            {
                basket.erase(it);
            }
            store_db[item] += quantity;
        } else
        {
            throw invalid_argument("There is no such item in the basket");
        }
    }

    void print()
    {
        for(const auto &item:basket)
        {
            cout << item.first << ": " << item.second << endl;
        }
    }
};



void addInBasket(Basket &basket)
{
    while(true)
    {
        string item;
        int quantity;

        cout << "Article: ";
        getline(cin, item);

        if(item.empty())
            break;

        cout << "Quantity: ";
        cin >> quantity;
        if(cin.fail())
        {
            cin.clear(); // Очистить состояние ошибки
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); // Пропустить оставшиеся символы в буфере до символа новой строки
            throw InvalidInputException();
        }

        cin.ignore();


        if(quantity <= 0)
        {
            throw CheckingPositiveNumberException();

        }


        try
        {
            basket.add(item, quantity);
        }
        catch(const invalid_argument &e)
        {
            cerr << "Exception: " << e.what() << endl;
        }
        cin.clear();
    }
    basket.print();
}


void removeFromBasket(Basket &basket)
{
    while(true)
    {
        string item;
        int quantity;

        cout << "Article: ";
        getline(cin, item);
        cout << "Quantity: ";
        cin >> quantity;

        if(item.empty())
            break;
        if(quantity <= 0)
        {
            throw CheckingPositiveNumberException();

        }


        try
        {
            basket.remove(item, quantity);
        }
        catch(const invalid_argument &e)
        {
            cerr << "Exception: " << e.what() << endl;
        }

    }
    basket.print();
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
            if(addStore_db())
                break;
        }
        catch(const CheckingPositiveNumberException &e)
        {
            cerr << "Exception: " << e.what() << endl;

        }
    }

    Basket basket;

    string operation;

    while(true)
    {
        cout << "Enter (add/remove/exit): ";
        getline(cin, operation);
        if(operation == "exit")
        {
            break;
        }

        if(operation == "add")
        {
            addInBasket(basket);
            cout << "---------------" << endl;

        } else if(operation == "remove")
        {
            removeFromBasket(basket);
            cout << "---------------" << endl;
        } else
        {
            throw invalid_argument("Unknown operation");
        }
    }

}