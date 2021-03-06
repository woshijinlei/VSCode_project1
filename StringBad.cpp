#include <iostream>
#include "StringBad.h"
#include <thread>
//类定义描述类如何分配内存，但你并没有分配内存
using namespace std;
int StringBad::num_strings = 0;

// bool StringBad::operator<(const StringBad &s2)
// {
//      cout << "StringBad operator< inner" << endl;
//     if (this->len < s2.len)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

// bool StringBad::operator()(const StringBad &s1, const StringBad &s2)
// {
//     cout << "StringBad operator()" << endl;
//     if (s1.getLength() < s2.getLength())
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

bool operator<(const StringBad &s1, const StringBad &s2)
{
    cout << "StringBad operator< outer" << endl;
    if (s1.getLength() < s2.getLength())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int StringBad::howMany()
{
    return num_strings;
}
void StringBad::show(StringBad &s)
{
    cout << s.str << endl;
}
void StringBad::show(const StringBad &s)
{
    cout << s.str << endl;
}
void StringBad::show(StringBad &&s)
{
    cout << s.str << endl;
}
StringBad::StringBad(const char *m_tr)
{
    len = strlen(m_tr);
    str = new char[len + 1];
    strlcpy(str, m_tr, len);
    num_strings++;
    cout << "StringBad created(char): " << this << " threadID: " << std::this_thread::get_id() << endl;
}

StringBad::StringBad()
{
    str = new char[1];
    str[0] = '\0';
    num_strings++;
    cout << "StringBad created(default): " << this << " threadID: " << std::this_thread::get_id() << endl;
}

StringBad::StringBad(const StringBad &sb)
{
    num_strings++;
    len = sb.len; //steal address
    str = new char[len + 1];
    strcpy(str, sb.str);

    cout << "StringBad created(copy): " << this << " threadID: " << std::this_thread::get_id() << endl;
}
StringBad::StringBad(StringBad &&sb)
{
    str = sb.str;
    len = sb.len;
    sb.str = nullptr;
    sb.len = 0;
    num_strings++;
    cout << "StringBad created(&&): " << this << " threadID: " << std::this_thread::get_id() << endl;
}
StringBad &StringBad::operator=(const StringBad &s)
{
    cout << "StringBad operator=: " << this
         << " threadID: " << std::this_thread::get_id() << endl;
    if (this == &s)
    {
        return *this;
    }
    delete[] str;
    len = s.len;
    str = new char[len + 1];
    strcpy(str, s.str);
    return *this;
}
StringBad &StringBad::operator=(StringBad &&s)
{
    cout << "StringBad operator=(&&): " << this
         << " threadID: " << std::this_thread::get_id() << endl;
    if (this == &s)
    {
        return *this;
    }
    delete[] str;
    len = s.len;
    str = new char[len + 1];
    strcpy(str, s.str);
    s.str = nullptr;
    s.len = 0;
    return *this;
}

char &StringBad::operator[](int i)
{
    return str[i];
}

StringBad::~StringBad()
{
    cout << "StringBad deleted: " << this
         << " threadID: " << std::this_thread::get_id() << endl;
    --num_strings;
    cout << num_strings << " objects left\n";
    delete[] str;
}

std::ostream &operator<<(std::ostream &os, const StringBad &st)
{
    os << st.str;
    return os;
}