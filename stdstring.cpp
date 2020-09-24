#include <string>
#include <iostream>
using namespace std;
//输入：a a并点击enter
// enter string:
// a a
//  a
// jinleideMini:firstC++ jinlei$
void showStringInput1()
{
    cout << "enter string: " << endl;
    char info[100];
    cin >> info;
    char c;
    c = cin.get(); //空格
    cout << c;
    c = cin.get(); //a
    cout << c;
    c = cin.get(); //\n
    cout << c;
}
//读取一行，并且将驻留在queue中的\n自动移除
void showStringInput2()
{
    cout << "enter string: " << endl;
    char info[100];
    cin.getline(info, 100);
    cout << info;
    char c;
    c = cin.get(); //这个地方可以输入，代表\n不在queue中
}
//一种情况：超出：后续的都会驻留在队列中
// enter string:
// zxcvbn
// zxcvbnjinleideMini:firstC++ jinlei$
//一种情况：不超出：发现\n驻留在队列中，并没有计入info中
// enter string:
// a
// a
// a--仅仅有一次输入机会，说明\n消耗了一次输入机会
// ajinleideMini:firstC++ jinlei$
void showStringInput3()
{
    cout << "enter string: " << endl;
    char info[5];
    cin.get(info, 5);
    cout << info;
    char c = 'f';
    c = cin.get();
    cout << c;
    c = cin.get();
    cout << c;
}
void showStringInput4()
{
    cout << "enter string: " << endl;
    string s;
    cin >> s;
    cout << s << endl;
}
//一个关键好处：自动调整string的大小
void showStringInput5()
{
    cout << "enter string: " << endl;
    string s;
    getline(cin, s);
    cout << s << endl;
}
void showStringCustruct()
{
    cout << "sizeof: " << sizeof(string) << endl;                       //24个字节
    cout << "npos: " << (string::npos) << endl;                         //18446744073709551615
    cout << "npos: " << 18446744073709551615 / 1024.0 / 1024.0 << endl; //24M
    const char *c = "jinlei";
    string s1; //nothing
    s1 = 'q';
    s1 = "woshijinlei";
    s1 = c; //const
    string s2(c);
    cout << "s2: " << s2 << endl;
    string s3 = string(s2);
    cout << "s3: " << s3 << endl;
    s2 += "jinhua";
    cout << "s2: " << s2 << " s3: " << s3 << endl;
    string s4 = string({'1', '2'});
    cout << "s4: " << s4 << endl;
    string s5 = string(10, '1');
    cout << "s5: " << s5 << endl;
    string s6 = string(c, 2);
    cout << "s6: " << s6 << endl;
    string s7("jinlei");
    char all[] = {'a', 'b', 'c', 'd'};
    string s8(all, all + 2); //数组名和对象名是有区别的，对象名不能执行+1这样的操作，没有意义
    cout << "s8: " << s8 << endl;
    string s9(s2, 0, 2);
    cout << "s9: " << s9 << endl;
}
void showUseString()
{
    string one("023abcca");
    string two("A");
    string three("a");
    if (one < two)
    {
        cout << "one<two" << endl;
    }
    auto p = one.find('z');
    cout << "find: " << p << endl; //18446744073709551615
    size_t p2 = one.find("23");
    cout << p2 << endl; //1
    auto p3 = one.find_first_of('2');
    cout << p3 << endl; //1
    size_t p4 = one.find_last_of("c");
    cout << p4 << endl; //6
    auto p5 = one.rfind('a');
    cout << p5 << endl; //7
    auto p6 = one.find_first_not_of("0123");
    cout << p6 << endl; //3
}
void showCapacity()
{
    string s = "woshijineliwohijinelijjjjjjjjjjj"
               "jjjjjjjj"
               "jjjjjjjfda";
    string s2;
    cout << s.capacity() << endl
         << s2.capacity() << endl;
    s2.reserve();//reserve(0) shrink_to_fit()
    cout << s2.capacity() << endl;
    s2.reserve(16*3);
    cout << s2.capacity() << endl;
}
void showString()
{
    showCapacity();
}