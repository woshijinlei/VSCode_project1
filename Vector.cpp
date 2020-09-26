#include <iostream>
#include <string>
#include <vector>
#include "TemplateFunction.h"

//STL提供了一组表示容器，迭代器，函数对象和算法的模版
using namespace std;

struct Stu
{
    char *name;
    int age;
};

//隐士实例化
void showTemplateFunction()
{
    int a = 10;
    int b = 20;
    SwapValue<int>(a, b);
    cout << "a: " << a << " b: " << b << endl;
    //函数模版重载
    int aa[] = {1, 2, 3};
    int bb[] = {4, 5, 6};
    SwapValue(aa, bb, 3);
    for (size_t i = 0; i < 3; i++)
    {
        cout << "aa: " << aa[i] << " bb: " << bb[i] << endl;
    }
    cout << "aa: " << aa << " bb: " << bb << endl;
}
//显示具体化：
template <>
void SwapValue<job>(job &a, job &b)
{
    char *temp = a.name;
    a.name = b.name;
    b.name = temp;
}

void showExplicitSpecializaiotn()
{
    job a{"jinlei", 29};
    job b{"jinhua", 28};
    SwapValue(a, b);
    cout << "a.name: " << a.name << " b.name: " << b.name << endl;
}

//显示实例化：当编译器看到char的显示实例化后后，便会使用模版来定义生成的SwapValue()函数
template void SwapValue<char>(char &, char &); //put here is really work?

void showExplicitInstantiation()
{
    char a = 'a';
    char b = 'b';
    SwapValue(a, b);
    cout << "a: " << a << " b: " << b << endl;
}
void showVectorCon()
{
    vector<int> v;
    cout << "size: " << v.size() << endl;
    vector<int> v1(15);
    for (size_t i = 0; i < 5; i++)
    {
        cout << v1[i] << endl; //默认值都为0
    }
    vector<int> v2(5, 1);
    for (auto &&i : v2)
    {
        cout << i << endl;
    }
    vector<int> v3 = {1, 2, 3, 4, 5, 4, 3};
    for (auto &&i : v3)
    {
        cout << i << endl;
    }
}
template <typename T>
void showVectorElements(vector<T> &v)
{
    //基于范围的for循环
    for (auto i : v)
    {
        cout << i << " ";
    }
    for (auto &&i : v)
    {
        cout << i << " ";
    }
    for (auto &i : v)
    {
        cout << i << " ";
    }
    for (const auto &i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}
template <>
void showVectorElements(vector<Stu> &v)
{
    //基于for_each
    for_each(v.begin(), v.end(), [](Stu &s) {
        cout << s.name << endl;
    });
}
void showVectorExplicitSpecializaiotn()
{
    vector<Stu> s{Stu{"jinlei", 29}, Stu{"jinhua", 28}};
    showVectorElements(s);
}
void showAssign()
{
    vector<int> v;
    v.assign({1, 2, 3, 4});
    v.assign(4, 1);
    showVectorElements<int>(v);
}
void showBackFront()
{
    vector<int> v({1, 2, 3, 4, 5});
    cout << v.back() << endl;
    cout << v.front() << endl;
    showVectorElements<int>(v);
}
void showBeginEnd()
{
    vector<int> v({1, 2, 3, 4, 5});
    cout << *(v.begin()) << endl; //1
    cout << *(v.end()) << endl;   //32754
    showVectorElements<int>(v);
}
void showSize()
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    cout << v.capacity() << endl;
    cout << v.size() << endl;
    showVectorElements<int>(v);
}
void showVValue()
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v.cbegin();
    for (auto i = v.begin(); i < v.end(); i++)
    {
        *i = 10;
        cout << *i << endl;
    }
    for (auto i = v.cbegin(); i < v.cend(); i++)
    {
        // *i = 10;//const
        cout << *i << endl;
    }
}
void showVReference()
{
    vector<Stu> v{Stu{"jinlei", 29}, Stu{"jinhua", 28}};
    for (auto i = v.crbegin(); i < v.crend(); i++)
    {
        // i->name = "who";
        cout << i->name << endl;
    }
    for (auto i = v.rbegin(); i < v.rend(); i++)
    {
        i->name = "who";
        cout << i->name << endl;
    }
}
void showErase()
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v.erase(v.begin() + 5); //1 2 3 4 5 3 5
    showVectorElements<int>(v);
}
void showInsert()
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v.insert(v.begin(), 10);
    showVectorElements<int>(v);
}
void showOperator()
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v = vector<int>(1, 0);
    showVectorElements<int>(v);
}
void showpopback() //前后概念位置begin为前 位置end为后
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v.pop_back();
    showVectorElements<int>(v); //1 2 3 4 5 2 3
}
void showpusback() //前后概念位置begin为前 位置end为后
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v.push_back(100);
    showVectorElements<int>(v); //1 2 3 4 5 2 3 5 100
}
void showResize()
{ //resize之前的会保留
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v.resize(3);
    v.resize(10, 0);
    showVectorElements<int>(v); //1 2 3 0 0 0 0 0 0 0
}
void showSwap()
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    vector<int> r{1};
    v.swap(r);
    showVectorElements<int>(v); //1
}
void showEmplace()
{
    vector<int> v({1, 2, 3, 4, 5, 2, 3, 5});
    v.emplace(v.begin(), 11);
    showVectorElements<int>(v); //11 1 2 3 4 5 2 3 5
}
void showDataAddress()
{
    vector<int> v({1, 2});
    cout << v.data() << endl; //0x7fe83f400640
    cout << &(v[0]) << endl;  //0x7fe83f400640
    showVectorElements<int>(v);
}
void showSTL()
{
    showEmplace();
}