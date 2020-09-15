#include<iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    vector<string> msg {
        "hello",
        "C++"
    };
    int length = msg.size();
    for (size_t i = 0; i < length; i++)
    {
        cout<<msg.at(i)<<" ";
    }
    for(const string& world:msg){
        cout<<world<<" ";
    }
    cout<<endl;
    return 0;
}