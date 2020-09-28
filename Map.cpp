#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include "StringBad.h"

using namespace std;

void showNormalMap()
{
    map<int, string> map;
    pair<const int, string> item(1, "Los Angeles");
    map.insert(item);
    for (auto &&i : map)
    {
        cout << i.first << " " << i.second << endl;
    }
}
void showmultimap()
{
    multimap<int, string> map;
    map.insert(pair<int, string>(1, "1"));
    map.insert(pair<int, string>(1, "2"));
    map.insert(pair<int, string>(1, "3"));
    map.insert(pair<int, string>(1, "1"));
    for (auto &&i : map)
    {
        cout << i.first << " " << i.second << endl;
    }
}

void showunorderMap()
{
    unordered_map<int, string> map{
        pair<int, string>(1, "jinlei"),
        pair<int, string>(1, "jinhua"),
        pair<int, string>(1, "baobao")};
    for (auto &&i : map)
    {
        cout << i.first << " " << i.second << endl;
    }
}
// StringBad created(char): 1
// StringBad created(copy): 2
// StringBad created(&&): 3
// StringBad created(copy): 4
// StringBad deleted
// 3 objects left
// StringBad deleted
// 2 objects left
// 1 jinle
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showunorderMapStringbad()
{
    StringBad s("jinlei");
    unordered_map<int, StringBad> map{
        pair<int, StringBad>(1, s)};
    for (auto &&i : map)
    {
        cout << i.first << " " << i.second << endl;
    }
}

// StringBad created(char): 1
// 1 jinle
// StringBad deleted
// 0 objects left
void showunorderMapstringbad()
{
    StringBad s("jinlei");
    unordered_map<int, StringBad &> map{
        pair<int, StringBad &>(1, s)};
    for (auto &&i : map)
    {
        cout << i.first << " " << i.second << endl;
    }
}

void showMap()
{
    showunorderMapstringbad();
}