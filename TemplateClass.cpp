#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "TemplateClass.h"
#include "StringBad.h"

using namespace std;
const int Num = 8;
void showTemplateString()
{
    using jinlei::Stack;
    std::srand(std::time(0)); //randomize rand()
    cout << "Please enter stack size: \n";
    int stacksize;
    cin >> stacksize;
    Stack<const char *> st(stacksize);
    const char *in[Num] = {"1: B", "2: B", "3: C", "4: D", "6: E", "7: F", "8: G", "9: H"};
    const char *out[Num];
    int processed = 0;
    int nextin = 0;
    int i = 0;
    while (i < 5)
    {
        cout << rand() << endl;
        i++;
    }
    while (processed < Num)
    {
        if (st.isempty())
        {
            st.push(in[nextin++]);
        }
        else if (st.isfull())
        {
            st.pop(out[processed++]);
        }
        else if (std::rand() % 2 && nextin < Num)
        {
            st.push(in[nextin++]);
        }
        else
        {
            st.pop(out[processed++]);
        }
    }
    for (size_t i = 0; i < Num; i++)
    {
        std::cout << out[i] << endl;
    }
    cout << "byte.\n";
}

// StringBad created(default): 1
// StringBad created(default): 2
// StringBad created(default): 3
// StringBad deleted
// 2 objects left
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showTemplateStack()
{
    using jinlei::Stack;
    Stack<StringBad> v(3); //这个地方内部数组会新建实例
}

// StringBad created(default): 1
// StringBad created(default): 2
// StringBad created(default): 3
// StringBad created(char): 4
// StringBad operator=//数组中本来有default对象，添加新的对象需要调用赋值运算符
// StringBad deleted
// 3 objects left
// StringBad deleted
// 2 objects left
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showTemplateStackPush()
{
    using jinlei::Stack;
    Stack<StringBad> v(3);
    StringBad s("jinlei");
    v.push(s);
}

//这个地方n为非类型参数，限于整形，枚举，引用，指针；
//不会生成动态内存，但是每个n都会生成一套自己的模版，相当于独立的声明
void showNoTypeTemplate()
{
    using jinlei::ArrayTp;
    ArrayTp<int, 4> a(10);
    cout << a[0] << endl;
}
// jinlei
// 29
// jinhua
// 28
// baobao
// 0
void showPairTemplate()
{
    using jinlei::Pair;
    Pair<string, int> ratings[2] = {
        Pair<string, int>("jinlei", 29),
        Pair<string, int>("jinhua", 28)};
    int joints = sizeof(ratings) / sizeof(Pair<string, int>);
    for (size_t i = 0; i < 2; i++)
    {
        cout << ratings[i].first() << endl;
        cout << ratings[i].second() << endl;
    }
    ratings[0].first() = "baobao";
    ratings[0].second() = 0;
    cout << ratings[0].first() << endl;
    cout << ratings[0].second() << endl;
}

//方式二
template class jinlei::ArrayTp<string, 10>; //显示实例化，编译器没有创建类对象，但是也会生成类声明包括方法定义

void showTemplateSpecialization()
{ 
    //方式一
    using namespace jinlei;
    ArrayTp<double, 10> *a;
    a = new ArrayTp<double, 10>(); //编译器在需要对象是才会生成类声明
    //方式三--需要定义全部的方法？
    // Pair<char,char> p('a','b');
}

void showTemplateTypeDefine(){
    typedef jinlei::ArrayTp<double,12> arrd;
    arrd d;
    using arrri = jinlei::ArrayTp<double,24>;
    arrri i;
}
void showTemplateClass()
{
}