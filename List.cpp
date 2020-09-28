#include <list>
#include <string>
#include <iostream>
//序列(7种)：dequeue    forward_list    list    queue   priority_queue  stack   vector
using namespace std;

void listConstruct()
{
    list<int> l1 = list<int>();
    list<int> l2 = list<int>(allocator<int>());
    list<int> l3 = list<int>(list<int>{1, 2, 3, 4});
    list<int> temp{1, 2, 3, 4};
    list<int> l4 = list<int>(temp);
    list<int> l5 = list<int>(4); //size
    list<int> l6 = list<int>({1, 2, 3, 4});
    list<int> l7 = list<int>(6, 1);
}

template <typename T>
void showSequences(T &t)
{
    cout << "enter template" << endl;
    for (auto &&i : t)
    {
        cout << i << endl;
    }
}
template <>
void showSequences(list<int> &l)
{
    cout << "enter template<list>" << endl;
    for (auto &&i : l)
    {
        cout << i << endl;
    }
}

void showlistreverse()
{
    list<int> l{1, 2, 3, 4, 5, 6};
    for_each(l.rbegin(), l.rend(), [](int &r) {
        cout << r << endl;
    });
}
void listOutput(const int &i)
{
    cout << i << endl;
}

void showListForeach()
{
    list<int> l{1, 2, 3};
    for_each(l.begin(), l.end(), listOutput);
    for_each(l.rbegin(), l.rend(), listOutput);
    for_each(l.cbegin(), l.cend(), listOutput);
    for_each(l.crbegin(), l.crend(), listOutput);
}

void showListEmplace()
{
    list<int> l{1, 2, 3};
    l.emplace(++l.cbegin(), 100);
    l.emplace_front(200);
    l.emplace_back(300);
    l.__emplace_back(123);
}

void showListErase()
{
    list<int> l{1, 2, 3};
    auto p = l.cbegin();
    p++;
    p++;
    l.erase(p);
    showSequences(l);
}

void showFront()
{
    list<int> l{1, 2, 3};
    cout << l.front() << endl;
    cout << l.back() << endl;
}

// 12
// 2
// 13
void showpoppush()
{
    list<int> l{1, 2, 3};
    l.pop_front();
    l.pop_back();
    l.push_back(13);
    l.push_front(12);
    showSequences(l);
}

// 5
// 5
// 5
// 5
// 5
// 12
// 12
// 100
// 1
// 2
// 3
void showListInsert()
{
    list<int> l{1, 2, 3};
    l.insert(l.begin()++, 100);
    auto what = list<int>{6, 6, 6};
    l.insert(l.begin(), {12, 12});
    l.insert(l.begin(), 5, 5);
    showSequences(l);
}

void showListRemoveIf()
{
    list<int> l{1, 2, 3};
    l.remove_if([](int &i) {
        return i == 1;
    });
    showSequences(l);
}

// 1
// 2
// 3
// 4
// 5
// 6
void showListMerage() //发生了排序
{
    list<int> l{1, 2, 6};
    l.merge(list<int>{3, 4, 5});
    showSequences(l);
}

// 1
// 2
// 3
// 4
// 5
// 6
void showListSort()
{
    list<int> l{1, 2, 6, 3, 2};
    l.sort([](const int &a, const int &b) {
        return b - a;
    });
}

// 1
// 3
// 3
// 2
void showListUnique()
{
    list<int> l{1, 2, 3, 6, 3, 2};
    l.unique([](const int &a, const int &b) {
        return b == 2 * a;
    });
    showSequences(l);
}

// enter template<list>
// enter template<list>
// 1
// 3
// 2
void showListSlice()
{
    list<int> origin{1};
    list<int> l{3, 2};
    l.splice(l.cbegin(), origin);
    showSequences(origin);
    showSequences(l);
}

//list在任何位置插入和删除的一件都会固定的
//vector强调的快速随机访问
void showList()
{  
}