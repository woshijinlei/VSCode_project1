#include <string>
#include <iostream>
namespace jinlei
{
    int what;
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
        StringBad &operator=(const StringBad &s);
        StringBad &operator=(char *c);
        StringBad &operator=(StringBad &&s);
        char &operator[](int i);
        friend std::ostream &operator<<(std::ostream &os, const StringBad &st);
        static int howMany();
    };

    //类定义描述类如何分配内存，但你并没有分配内存
    using namespace std;
    int StringBad::num_strings = 0;

    int StringBad::howMany()
    {
        return num_strings;
    }

    StringBad::StringBad(const char *m_tr)
    {
        len = strlen(m_tr);
        str = new char[len + 1];
        strlcpy(str, m_tr, len);
        num_strings++;
        cout << "StringBad created(char): " << num_strings << endl;
    }

    StringBad::StringBad()
    {
        str = new char[1];
        str[0] = '\0';
        num_strings++;
        cout << "StringBad created(default): " << num_strings << endl;
    }

    StringBad::StringBad(const StringBad &sb)
    {
        num_strings++;
        len = sb.len; //steal address
        str = new char[len + 1];
        strcpy(str, sb.str);
        cout << "StringBad created(copy): " << num_strings << endl;
    }
    StringBad::StringBad(StringBad &&sb)
    {
        str = sb.str;
        len = sb.len;
        sb.str = nullptr;
        sb.len = 0;
        num_strings++;
        cout << "StringBad created(&&): " << num_strings << endl;
    }
    StringBad &StringBad::operator=(const StringBad &s)
    {
        cout << "StringBad operator=" << endl;
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
        cout << "StringBad operator=(&&)" << endl;
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
        cout << "StringBad deleted" << endl;
        --num_strings;
        cout << num_strings << " objects left\n";
        delete[] str;
    }

    std::ostream &operator<<(std::ostream &os, const StringBad &st)
    {
        os << st.str;
        return os;
    }

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

    void __showSomeClass(int t)
    { 
        {
            int a = StringBad::Months;
            showArrayObject();
        }
    }

} // namespace jinlei