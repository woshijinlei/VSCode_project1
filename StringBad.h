#include <string>
#include <iostream>

class StringBad
{
private:
    char *str; //定义的是一个指针，表面类申明没有为字符串本身分配存储空间，而是通过构造函数new，动态的申请内存
    int len;
    static int num_strings; //静态存储类型，静态类成员
public:
    static const int Months = 12;
    StringBad(const char *m_tr);
    StringBad(const StringBad &sb); // = delete;//出现StringBad s3 = StringBad(s1)错误，值传递到方法也错误
    StringBad(StringBad &&s);
    StringBad();
    ~StringBad();
    void show(StringBad &s);       //lvalue
    void show(const StringBad &s); //const lvalue or rlvaue
    void show(StringBad &&s);      //rvalue
    int getLength() const { return strlen(str); };
    char *getStr() const { return str; };
    StringBad &operator=(const StringBad &s);
    StringBad &operator=(char *c);
    StringBad &operator=(StringBad &&s);
    // bool operator<(const StringBad &s2);
    char &operator[](int i);
    friend std::ostream &operator<<(std::ostream &os, const StringBad &st);
    static int howMany();
};
