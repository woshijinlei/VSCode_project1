#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <iostream>
#include "StringBad.h"

using namespace std;
void showSetArray()
{
    const int N = 3;
    string s1[N] = {"buffoon", "thinkers", "for"};
    set<string> A(s1, s1 + N);
    for (auto &&i : A)
    {
        cout << i << endl;
    }
}

void showSet1()
{
    set<string> a = set<string>({"1", "2"});
    a.insert("1");
    for (auto &&i : a)
    {
        cout << i << endl;
    }
}
// 1
// 1
// 2
// 3
void showmultiset()
{
    multiset<string> s{"1", "2", "1", "3"};
    for (auto &&i : s)
    {
        cout << i << endl;
    }
}

void showSet()
{
    StringBad st("jinlei");
    StringBad ss("jinlei");  
}