#include <iostream>
using namespace std;
class Useless
{
private:
    int32_t n;
    char *pc;
    static int32_t ct;
    void showObject() const;

public:
    Useless();
    explicit Useless(int32_t k);
    Useless(int32_t k, char ch);
    Useless(const Useless &f);
    Useless(Useless &&f);
    ~Useless();
    Useless operator+(const Useless &f) const; //return new Useless
    Useless &operator=(const Useless &f);      //注释掉后：its copy assignment operator is implicitly deleted
    Useless &operator=(Useless &&f);
    void showData() const;
};

int Useless::ct = 0;

Useless::Useless()
{
    ++ct;
    n = 0;
    pc = nullptr;
    cout << "default constructor: " << ct << endl;
    showObject();
}

Useless::Useless(int32_t k)
{
    ++ct;
    cout << "int constructor: " << ct << endl;
    n = k;
    pc = new char[k];
    showObject();
}

Useless::Useless(int32_t k, char ch) : n(k)
{
    ++ct;
    cout << "int char constructor: " << ct << endl;
    n = k;
    pc = new char[n];
    for (size_t i = 0; i < k; i++)
    {
        pc[i] = ch;
    }
    showObject();
}

Useless::Useless(const Useless &f)
{
    ++ct;
    cout << "copy constructor: " << ct << endl;
    n = f.n;
    pc = new char[n]; //deep copy
    for (size_t i = 0; i < n; i++)
    {
        pc[i] = f.pc[i];
    }
    showObject();
}
Useless::Useless(Useless &&f)
{
    ++ct;
    cout << "move constructor: " << ct << endl;
    pc = f.pc;      //steal address
    f.pc = nullptr; //old object is broken
    f.n = 0;
    showObject();
}

Useless::~Useless()
{
    cout << "destructor called: objects left: " << --ct << endl;
    showObject();
    delete[] pc; //release
}

Useless Useless::operator+(const Useless &f) const
{
    cout << "Enter operator+()\n";
    Useless u = Useless(n + f.n);
    for (size_t i = 0; i < n; i++)
    {
        u.pc[i] = pc[i];
    }
    for (size_t i = n; i < u.n; i++)
    {
        u.pc[i] = f.pc[i - n];
    }
    cout << "temp object:\n";
    cout << "Leaving operator+()\n";
    return u; //invoke ~
}

Useless &Useless::operator=(const Useless &f)
{
    if (this == &f)
    {
        return *this;
    }
    cout << "Enter operator=()\n";
    delete[] pc; //如果pc指向了其他地址，则这个对象原先被分配的内存将没有机会得到释放
    n = f.n;
    pc = new char[n];
    for (size_t i = 0; i < n; i++)
    {
        pc[i] = f.pc[i];
    }
    cout << "Leave operator=()\n";
    return *this;
}

Useless &Useless::operator=(Useless &&f)
{
    if ((this == &f))
    {
        return *this;
    }
    cout << "Enter move operator=()\n";
    delete[] pc;
    n = f.n;
    pc = f.pc;
    f.n = 0;
    f.pc = nullptr;
    cout << "Leave move operator=()\n";
    return *this;
}

void Useless::showObject() const
{
    cout << "Number of elements: " << n;
    cout << " Data address: " << (void *)pc << endl;
}

void Useless::showData() const
{
    if (n == 0)
    {
        cout << "object is empty";
    }
    else
    {
        for (size_t i = 0; i < n; i++)
        {
            cout << pc[i];
        }
    }
    cout << endl;
}
// default constructor: 1
// Number of elements: 0 Data address: 0x0
// destructor called: objects left: 0
// Number of elements: 0 Data address: 0x0
static void defaultShow()
{
    Useless u; //C++隐式调用构造函数：未被初始化的对象，程序使用默认构造函数
}
static void defaultShow2()
{
    Useless u(12); //C++两种显示调用构造函数的方法1： Useless u(12);
}
static void defaultShow3()
{
    Useless u = Useless(12); //C++两种显示调用构造函数的方法2： Useless u = Useless(12);
}
static void defaultShow4()
{
    //这种方式初始化（有两种方式）：
    //1.直接类似Useless u(12, 'c');
    //2.或者C++允许(可能)编译器调用构造函数创造一个临时对象，然后复制到u中，同时删除掉临时对象
    Useless u = Useless(12, 'c');
}
static void defaultShow5()
{
    Useless u = {12, 'c'}; //c++11列表初始化（和构造函数匹配）
}
// default constructor: 1
// Number of elements: 0 Data address: 0x0

// int char constructor: 2
// Number of elements: 12 Data address: 0x7faafbc02a10

// Enter operator=()
// Leave operator=()

// destructor called: objects left: 1
// Number of elements: 12 Data address: 0x7faafbc02a10

// destructor called: objects left: 0
// Number of elements: 12 Data address: 0x7faafbc02a20
static void defaultShow6()
{
    {
        Useless u = Useless(); //初始化：创建指定值的对象，可能会创建临时对象也可能不会
        u = Useless{12, 'c'};  //(关键区别是u单独，貌似只有这种情况)调用的是赋值运算符：总会在赋值前创建临时对象
    }
}
// default constructor: 1
// Number of elements: 0 Data address: 0x0

// copy constructor: 2
// Number of elements: 0 Data address: 0x7fd340402a10

// destructor called: objects left: 1
// Number of elements: 0 Data address: 0x7fd340402a10

// destructor called: objects left: 0
// Number of elements: 0 Data address: 0x0
static void defaultShow7()
{
    {
        Useless u = Useless();
        Useless u2 = u; //调用的是复制构造函数
        // Useless u2(u);//调用的是复制构造函数
    }
}
static void defaultShow8()
{
    {
        Useless u = Useless();
        //下面两种是等效的，调用复制构造函数（也可能调用复制构造函数生成临时对象，然后将内容复制给u2）
        Useless u2 = u;
        Useless u3 = Useless(u);
        // Useless u2(u);//调用的是复制构造函数（第三种方式）
    }
}
//如果实参为右值，则const引用将指向一个临时变量
void showUseless()
{
    // defaultShow();
    // defaultShow2();
    // defaultShow7();
    Useless one(10, 'x');
    Useless two = one;
    Useless three(20, '0');
    Useless four(one + three);
    cout << "one" << endl;
    one.showData();
    cout << "two" << endl;
    two.showData();
    cout << "three" << endl;
    three.showData();
    cout << "four" << endl;
    four.showData();
    cout << "four" << endl;
    four = move(one);
}
