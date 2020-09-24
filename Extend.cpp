#include <iostream>
using namespace std;

class BaseClass
{
private:
    char *name;

public:
    BaseClass();
    BaseClass(char *name);
    virtual void show() const = 0;
    //纯虚函数
    virtual void description() const final
    { //不能使用final修饰非虚函数
        cout << name << endl;
    }
};

BaseClass::BaseClass(char *m_age)
{
    name = m_age;
}

class StringBad : public BaseClass
{
private:
    int age;

public:
    //why can do this?
    StringBad() : BaseClass(nullptr)
    {
        age = 0;
    };
    StringBad(int m_age);
    StringBad(const StringBad &s) = delete;
    StringBad &operator=(const StringBad &) = delete;
    void redo(double d);
    void redo(int d) = delete;
    virtual void show() const override final;
    // virtual void description() const;//无法重写final函数
};

StringBad::StringBad(int m_age) : BaseClass(nullptr)
{
    age = m_age;
}
void StringBad::show() const
{
    cout << "show" << endl;
}

void StringBad::redo(double d)
{
    cout << "redo: " << d << endl;
}

void showSomeclass()
{
    //多态
    StringBad bc;
    BaseClass &b = bc;
    bc.show();
    //delete
    StringBad s;
    b = s;
    s.redo(1.0);
}
