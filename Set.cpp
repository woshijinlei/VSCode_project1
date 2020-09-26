#include <map>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

void showMap()
{
    map<int, string> map; 
    pair<const int, string> item(1, "Los Angeles");
    map.insert(item);
    for (auto &&i : map)
    {
        cout<<i.first<<" "<<i.second<<endl;
    }
    
}