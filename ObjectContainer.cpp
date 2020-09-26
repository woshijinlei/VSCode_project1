#include <iostream>
#include "StringBad.h"
#include <vector>
#include <list>

using namespace std;

void callme1(StringBad &rsb)
{
    cout << "by reference" << endl;
    cout << rsb << endl;
}
//值传递会造成调用复制构造函数的发生
void callme2(StringBad sb)
{
    cout << "by value" << endl;
    cout << sb << endl;
}

// StringBad created(char): 1
// StringBad created(copy): 2
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showCopyConstruct()
{
    StringBad s1("jinhua");
    StringBad s3 = StringBad(s1); //有可能创建临时对象
}

// StringBad created(char): 1
// StringBad created(copy): 2
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showCopyConstruct2()
{
    StringBad s1("jinhua");
    StringBad s3 = s1; //有可能创建临时对象
}
// StringBad created(char): 1
// StringBad created(default): 2
// StringBad operator=
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showAssignConstruct()
{
    StringBad s1("jinhua");
    StringBad s3;
    s3 = s1; //s3这样已经构建完毕对象，然后在使用，会发生赋值运算符的情形
}

// StringBad created(char): 1
// j
// StringBad deleted
// 0 objects left

StringBad showReturnObject() //函数返回对象时，应返回对象而不是引用，因为局部对象会被销毁，这里直接返回了对象，并没有执行copy
{
    StringBad s("jh");
    return s; // StringBad("jh");
}

// tringBad created(char): 1
// StringBad created(copy): 2
// j
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
StringBad showReturnObject2(StringBad &s) //函数返回对象时，应返回对象而不是引用，因为局部对象会被销毁，这里调用赋值构造函数(copy)
{
    return s;
}
//StringBad created(char): 1
// j
// StringBad deleted
// 0 objects left
StringBad &showReturnObject3(StringBad &s) //函数引用
{
    return s;
}

void showRightCounstruct()
{
    //1.发现不强转，并没有执行移动构造函数
    // StringBad created(char): 1
    // StringBad created(&&): 2
    // StringBad deleted
    // 1 objects left
    // StringBad deleted
    // 0 objects left
    // StringBad k(static_cast<StringBad &&>(StringBad("jinhua")));

    //2.直接创建一个对象（应该是编译器优化过）
    //StringBad created(char): 1
    // StringBad deleted
    // 0 objects left
    StringBad k(StringBad("jinhua"));

    //1.移动赋值函数
    // StringBad created(char): 1
    // StringBad created(char): 2
    // StringBad operator=(&&)
    // StringBad deleted
    // 1 objects left
    // StringBad deleted
    // 0 objects left

    //2.如果没有移动构造函数，这里将会调用赋值函数=
    // StringBad created(char): 1
    // StringBad created(char): 2
    // StringBad operator=
    // StringBad deleted
    // 1 objects left
    // StringBad deleted
    // 0 objects left

    // StringBad k("jinhua");
    // k = StringBad("who");

    // StringBad j("jinlei");
    // StringBad k("jinhua");
    // k = move(j);
}

// StringBad created(default): 1
// StringBad created(char): 2
// StringBad operator=(&&)
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showRightAssign()
{
    StringBad k;
    k = StringBad("jinhua");
}

// StringBad created(default): 1
// StringBad created(default): 2
// StringBad created(default): 3
// StringBad created(char): 4
// StringBad operator=(&&)  这个地方得做一个说明：如果没有移动赋值运算符，这个地方则会使用直接赋值运算符
// StringBad deleted
// 3 objects left
// StringBad deleted
// 2 objects left
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showArrayObject()
{
    StringBad sa[3];
    sa[0] = StringBad("jinlei"); //右值
}

void showStringBadShow()
{
    StringBad s;
    const StringBad w("jinlei");
    s.show(StringBad("jinhua"));
    s.show(s);
    s.show(w);
}
#include <vector>
void showVectorSTL()
{
    vector<StringBad> v{StringBad("jinlei")};
    for (auto i : v)
    {
        cout << i.getLength() << endl;
    }
}
void showVectorSTL2()
{
    StringBad s1 = StringBad("jinlei");
    vector<StringBad> v;
    v.push_back(s1);
    for (auto i : v)
    {
        cout << i.getLength() << endl;
    }
}
void showVectorSTL3()
{
    StringBad s1 = StringBad("jinlei");
    vector<StringBad *> v;
    v.push_back(&s1);
    for (auto i : v)
    {
        cout << i->getLength() << endl;
    }
}

// StringBad created(char): 1
// StringBad created(copy): 2
// StringBad deleted
// 1 objects left
// 6
// StringBad deleted
// 0 objects left
void showVectorSTL4()
{
    vector<StringBad> v{StringBad("jinlei")};
}

// StringBad created(char): 1
// 0x7ffee6d2e290
// StringBad created(copy): 2
// 0x7ffee6d2e2a0 6
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showVectorSTL5()
{
    vector<StringBad> v;
    StringBad s1 = StringBad("jinlei");
    cout << &s1 << endl;
    v.assign(1, s1);
    for (auto &i : v)
    {
        cout << &v << " " << i.getLength() << endl;
    }
}

// StringBad created(char): 1
// StringBad created(char): 2
// StringBad created(char): 3
// StringBad created(copy): 4
// StringBad created(copy): 5
// StringBad created(copy): 6
// StringBad deleted
// 5 objects left
// StringBad deleted
// 4 objects left
// StringBad deleted
// 3 objects left
// StringBad created(&&): 4
// StringBad operator=(&&)
// StringBad operator=(&&)
// StringBad deleted
// 3 objects left
// StringBad created(&&): 4
// StringBad operator=(&&)
// StringBad operator=(&&)
// StringBad deleted
// 3 objects left
// ji
// jinle
// leiaaa
// StringBad deleted
// 2 objects left
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showVectorSort()
{
    vector<StringBad> v{StringBad("leiaaaa"), StringBad("jin"), StringBad("jinlei")};
    sort(v.begin(), v.end(), [](const StringBad &s1, const StringBad &s2) {
        if (s1.getLength() < s2.getLength())
        {
            return true;
        }
        else
        {
            return false;
        }
    });
    for (auto &i : v)
    {
        cout << i.getStr() << endl;
    }
}
// StringBad created(char): 1
// StringBad created(char): 2
// StringBad created(char): 3
// StringBad created(copy): 4
// StringBad created(copy): 5
// StringBad created(copy): 6
// StringBad deleted
// 5 objects left
// StringBad deleted
// 4 objects left
// StringBad deleted
// 3 objects left
// StringBad created(default): 4
// StringBad deleted
// 3 objects left
// StringBad deleted
// 2 objects left
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showVectorCons1()
{
    vector<StringBad> v{StringBad("leiaaaa"), StringBad("jin"), StringBad("jinlei")}; //注意：创造的临时对象，执行copy构造函数，随后就被销毁
    StringBad s;
}

// StringBad created(char): 1
// StringBad created(char): 2
// StringBad created(char): 3
// StringBad created(copy): 4
// StringBad created(copy): 5
// StringBad created(copy): 6
// StringBad deleted
// 5 objects left
// StringBad deleted
// 4 objects left
// StringBad deleted
// 3 objects left
// StringBad deleted
// 2 objects left
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showVectorCons2()
{
    vector<StringBad> v;
    v.assign({StringBad("leiaaaa"), StringBad("jin"), StringBad("jinlei")});
}
// StringBad created(char): 1
// StringBad created(char): 2
// StringBad created(copy): 3
// StringBad created(copy): 4
// StringBad deleted
// 3 objects left
// StringBad deleted
// 2 objects left
// jinhu
// jinle
// StringBad deleted
// 1 objects left
// StringBad deleted
// 0 objects left
void showListRe()
{
    list<StringBad> l{StringBad("jinlei"), StringBad("jinhua")};
    l.reverse();
    for (auto &w : l)
    {
        cout << w.getStr() << endl;
    }
}

void showListMer()
{
    list<StringBad> l{StringBad("12"), StringBad("123456"), StringBad("123"), StringBad("123456"), StringBad("123")};
    l.sort([](const StringBad &a, const StringBad &b) {
        cout << "sort: " << a.getLength() << " " << b.getLength() << endl;
        return b.getLength() - a.getLength();
    });
    for (auto &w : l)
    {
        cout << w.getStr() << endl;
    }
}

void __showSomeClass()
{
    {
        showListMer();
    }
}