#include <iostream>
using namespace std;
void inputOneline(string& content)
{
    cout << "输入一行文字，并以回车键结束" << endl;
    char temp;
    while (cin.get(temp))
    {
        if (temp != '\n')
        { 
            content+=temp;
        }
        else
        {
            cout << "你的输入是：" << content << endl;
            break;
        }
    }
}