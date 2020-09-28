#include <thread> 
#include "StringBad.h"
#include <iostream>
using namespace std;

class Runnable
{
private:
    long sleep;

public:
    Runnable(long m_sleep) : sleep(m_sleep)
    {
        cout << "Runnable: " << &sleep << endl;
    };
    Runnable(const Runnable &r);
    ~Runnable();
    void operator()()
    {
        cout << "operator(): " << &sleep << endl;
    }
};

Runnable::Runnable(const Runnable &r)
{
    cout << "Runnable copy: " << &sleep << endl;
    sleep = r.sleep;
}

Runnable::~Runnable()
{
    cout << "~Runnable " << &sleep << endl;
}

void myprint()
{
    cout << "myprint1: " << myprint << endl;
    cout << "myprint2: " << myprint << endl;
    cout << "myprint3: " << myprint << endl;
}

void showThreadMethod()
{
    thread t(myprint);
    t.join();
    // cout << t.joinable() << endl;
    // t.detach();
    // cout << t.joinable() << endl;
}

// Runnable: 0x7ffeed3d4280
// Runnable copy: 0x7ffeed3d41f8
// Runnable copy: 0x7fa8da402a78
// ~Runnable 0x7ffeed3d41f8
// ~Runnable 0x7ffeed3d4280
// operator(): 0x7fa8da402a78
// ~Runnable 0x7fa8da402a78
void showThreadObject()
{
    thread t(Runnable(1000));
    t.join();
}
// Runnable: 0x7ffeeb209288
// Runnable copy: 0x7ffeeb2091f8
// Runnable copy: 0x7fa6d6402a78
// ~Runnable 0x7ffeeb2091f8
// operator(): 0x7fa6d6402a78
// ~Runnable 0x7fa6d6402a78
// ~Runnable 0x7ffeeb209288
void showThreadObject2() //同名的函数名称编译不通过
{
    Runnable r(1000);
    thread t(r);
    t.join();
}

void showThreadLambda()
{
    thread t([] {
        cout << "what happened." << endl;
    });
    t.join();
}

void showParam(int type, StringBad s)
{
    cout << "showThreadParam: " << myprint << endl;
}
void showParam3(int type, const StringBad &s)
{
    cout << "showThreadParam: " << myprint << endl;
}

// StringBad created(char): 0x7ffeedb17270 threadID: 0x1078355c0    //StringBad s("jinlei")
// StringBad created(copy): 0x7ffeedb171a0 threadID: 0x1078355c0    //创建临时拷贝对象（thread()的参数）
// StringBad created(&&): 0x7fd832500068 threadID: 0x1078355c0      //直接使用右值构造对象，传递到子线程（子线程内存）
// StringBad deleted: 0x7ffeedb171a0 threadID: 0x1078355c0          //首先删除临时对象
// 2 objects left
// StringBad created(&&): 0x70000b126e68 threadID: 0x70000b127000   //子线程再次使用右值构造函数，作为子线程内部使用（showParam参数）
// showThreadParam: 1
// StringBad deleted: 0x70000b126e68 threadID: 0x70000b127000       //在子线程中删除子线程中创建的对象
// 2 objects left
// StringBad deleted: 0x7fd832500068 threadID: 0x70000b127000       //在子线程中删除主线程构建的对象
// 1 objects left
// StringBad deleted: 0x7ffeedb17270 threadID: 0x1078355c0          //删除主线程中创建的对象
// 0 objects left
void showThreadParam1()
{
    StringBad s("jinlei");
    thread t(showParam, 1, s);
    t.join();
}
// StringBad created(char): 0x7ffeed9c8260 threadID: 0x111e535c0
// StringBad created(&&): 0x7ffeed9c81a0 threadID: 0x111e535c0       //创建临时拷贝对象（thread()的参数）
// StringBad created(&&): 0x7f8dbb402a98 threadID: 0x111e535c0
// StringBad deleted: 0x7ffeed9c81a0 threadID: 0x111e535c0
// 2 objects left
// StringBad deleted: 0x7ffeed9c8260 threadID: 0x111e535c0
// 1 objects left
// StringBad created(&&): 0x7000025e3e68 threadID: 0x7000025e4000   //子线程再次使用右值构造函数，作为子线程内部使用（showParam参数）
// showThreadParam: 1
// StringBad deleted: 0x7000025e3e68 threadID: 0x7000025e4000
// 1 objects left
// StringBad deleted: 0x7f8dbb402a98 threadID: 0x7000025e4000
// 0 objects left
void showThreadParam2()
{
    thread t(showParam, 1, StringBad("jinlei"));
    t.join();
}
// StringBad created(char): 0x7ffee8063270 threadID: 0x10ecc45c0    //初始创建实例
// StringBad created(copy): 0x7ffee80631a0 threadID: 0x10ecc45c0    //创建一个临时对象（thread()的参数）
// StringBad created(&&): 0x7fd3c8d00068 threadID: 0x10ecc45c0      //直接使用右值构造对象，传递到子线程（子线程内存）(因为是引用，直接使用这个内存)
// StringBad deleted: 0x7ffee80631a0 threadID: 0x10ecc45c0
// 2 objects left
// showThreadParam: 1
// StringBad deleted: 0x7fd3c8d00068 threadID: 0x70000f7d0000
// 1 objects left
// StringBad deleted: 0x7ffee8063270 threadID: 0x10ecc45c0
// 0 objects left
void showThreadParam3()
{
    StringBad s("jinlei");
    thread t(showParam3, 1, s);
    t.join();
}

// StringBad created(char): 0x7ffeed120260 threadID: 0x107ae25c0
// StringBad created(&&): 0x7ffeed1201a0 threadID: 0x107ae25c0
// StringBad created(&&): 0x7fdf5cd00068 threadID: 0x107ae25c0
// StringBad deleted: 0x7ffeed1201a0 threadID: 0x107ae25c0
// 2 objects left
// StringBad deleted: 0x7ffeed120260 threadID: 0x107ae25c0
// 1 objects left
// showThreadParam: 1
// StringBad deleted: 0x7fdf5cd00068 threadID: 0x70000c4a4000
// 0 objects left
void showThreadParam4()
{
    thread t(showParam3, 1, StringBad("jinlei"));
    t.join();
}
void showT(StringBad &&a) {}
void showT(StringBad &a) {}

void showParam4(StringBad &s)
{
    s.changeNumber(100);
}

// StringBad created(char): 0x7ffee9fec280 threadID: 0x110d2e5c0
// showThreadParam: 1
// StringBad deleted: 0x7ffee9fec280 threadID: 0x110d2e5c0
// 0 objects left
void showThreadParam5()
{
    StringBad s("jinlei");
    thread t(showParam3, 1, std::ref(s));
    t.join();
}
// StringBad created(char): 0x7ffeed8da280 threadID: 0x1046d35c0
// StringBad deleted: 0x7ffeed8da280 threadID: 0x1046d35c0
// 0 objects left
void showParam5(StringBad *s)
{
    s->changeNumber(100);
}
void showThreadParam6()
{
    StringBad s("jinlei");
    thread t(showParam5, &s);
    t.join();
}

void showThread()
{
    showThreadParam6();
}