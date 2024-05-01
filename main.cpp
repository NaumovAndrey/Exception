#include <iostream>
#include "vector"

using namespace std;

template<typename T>
struct Message
{
    char *data;

    Message(char *inData): data(inData)
    {

    }

    void print()const{
        cout << data << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    Message<string> message("hell");
    message.print();

    return 0;
}
