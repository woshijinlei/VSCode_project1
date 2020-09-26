#include <iostream>
#include <vector>
#include <iterator>

//对象编程关注的是编程数据方面的问题
//泛型编程关注的是算法，指在编写独立于数据类型的代码

//模版使得算法独立于存储的数据类型，但是迭代器使得算法独立于容器类型
using namespace std;
double *find_ar(double *ar, int n, const double &val)
{
    for (size_t i = 0; i < n; i++)
    {
        if (ar[i] == val) //可以用模版将这种算法推广到包含==运算符的，任意类型的数组
        {
            return &ar[i];
        }
        ar++;
    }
    return nullptr;
}

template <typename T>
T *find_template_ar(T *ar, int n, const T &val)
{
    for (size_t i = 0; i < n; i++)
    {
        if (ar[i] == val) //T类型需要包含==运算符
        {
            return &ar[i];
        }
        ar++;
    }
    return nullptr;
}

struct Node
{
    double item;
    Node *p_next;
};
Node *find_node(Node *node, int n, double &val)
{
    Node *start;
    for (start = node; start != nullptr; start = start->p_next)
    {
        if (start->item == val)
        {
            return start;
        }
    }
    return nullptr;
}
//这两种算法都表示：将值和容器中的每个值进行比较，知道找到匹配的位置
//fanxing编程旨在实现同一个find函数，完成数组，链等容器的查找
//两个通用表示：
//数据类型通用表示：模版
//容器中值的通用表示：迭代器（基本要求：*运算符 ++ --运算符等）

void showIteOne()
{
    vector<double> v{1, 2, 3, 4};
    vector<double>::iterator it;
    for (it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }
}
void output(const std::string &s)
{
    cout << s << endl;
}
void showIterator()
{
    vector<string> s(4);
    string r[] = {"one", "two", "three", "four"};
    string r2[] = {"five", "six"};
    string r3[] = {"eight"};
    copy(r, r + 4, s.begin());
    for_each(s.begin(), s.end(), output);
    copy(r2, r2 + 2, back_insert_iterator<vector<string>>(s));
    for_each(s.begin(), s.end(), output);
    copy(r3, r3 + 1,  insert_iterator<vector<string>>(s,s.begin()));
    for_each(s.begin(), s.end(), output);
}
