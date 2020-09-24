#include <iostream>
#include <string>
#include <vector>
using namespace std;
//STL提供了一组表示容器，迭代器，函数对象和算法的模版
void showSTL()
{
    vector<int> v(5);
    for (size_t i = 0; i < 5; i++)
    {
        cout<<v[i]<<endl;
    } 
}