#include <iostream>
#include "vector"

using namespace std;

template<typename T1, typename T2>
T2 maxNum(T1 a, T2 b)
{
    return a > b ? a : b;
}

template<typename T>
T maxNum(const vector<T> &v)
{
    if(v.size() == 0)
    {
        throw invalid_argument("'v' can`t be empty!");
    }
    T m = v[0];
    for(int i = 0; i < v.size(); ++i)
    {
        if(v[i] > m)
        {
            m = v[i];
        }
    }
    return m;
}

int main()
{
    setlocale(LC_ALL, "rus");

    vector<double> test = {10.5, 8.4, 3.4};
    cout << "result: " <<  maxNum(test) << endl;

    return 0;
}
