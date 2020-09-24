#include <iostream>
#include <functional>
using namespace std;

//answer = ef(q): 可调用类型

template <typename T, typename F>
T use_f(T v, F f)
{
    static int count = 0;
    count++;
    cout << "count: " << count << endl;
    return f(v);
}

template <class T>
T use_f2(T v,function<T(T)> f){

}

typedef function<double(double)> fdd;

void showSomedef(fdd f)
{ 
    std::function<double(double)> f1 = [](double d){return d;};
}