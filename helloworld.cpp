#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "StringBad.h"
using namespace std;

const int SLEW = 10;
inline void eatline()
{
    while (cin.get() != '\n')
        continue;
}
void testOstreamPut()
{
    //put char
    cout.put('j') << endl;
    //write char*
    const char *s = "wohijinlei";
    //将换行符发送到缓冲区后，将刷新缓冲区
    //这个地方输入即将发生时就会刷新缓冲区
    cout.write(s, strlen(s));
    //flush两种方式
    cout.flush();
    cout << flush;
}

#include <iomanip>
void testOtreamFormat()
{
    //default
    cout << 122.233455566 << endl;        //122.233
    cout << 1.233455566 << endl;          //1.23346
    cout << 133333.3455566 << endl;       //133333
    cout << 1333333.3455566 << endl;      //1.33333e+06
    cout << 0.000013333333455566 << endl; //1.33333e-05
    cout << 1 / 3.0 << endl;              //0.333333

    // hex(cout);//16进制
    // oct(cout);//8进制
    // fixed(cout);//10进制
    // cout << 13 << endl;

    // 默认宽度等于值的长度，比如字符显示在宽度为一个字符的字段中
    cout << cout.width() << endl; //默认字段宽度为0，但是C++总会增产字段，以容纳数据
    cout.width(12);               //对下一次输入有效
    cout.fill('*');
    cout << 12 << '#' << endl;

    // 默认模式，6位精度
    // 定点模式，精度指的是总位数
    // 科学技术模式，精度指的是小数点后面的位数
    cout.precision(4);
    cout << 12.3333 << endl;        //12.33
    cout << 12.3 << endl;           //12.3
    cout << 12 << endl;             //12
    cout.setf(ios_base::showpoint); //类级静态常量
    cout << 12 << endl;             //12
    cout << 12.123456 << endl;      //12.12
    cout << 12.0 << endl;           //12.00
    cout << true << endl;
    cout.setf(ios_base::boolalpha);
    cout << true << endl;
    // 两种方式实现fixed模式
    // cout.setf(ios_base::fixed,ios_base::floatfield);
    cout << fixed << 177888888000000233188888800000023318888880000002331.0 << endl; //177888888000000235058467210278741772105458781257728.0000
    cout << fixed << 17.0 << endl;                                                  //17.0000
    cout.unsetf(ios_base::floatfield);
    cout << 177888888000000233188888800000023318888880000002331.0 << endl; //1.779e+50
    cout << 17.0 << endl;
    //17.00
    // iomanip
    cout << right;
    cout << setw(12) << setfill('#') << 12 << endl
         << setw(12) << setfill('*') << setprecision(4) << 12.0 << endl
         << setw(12) << setfill('#') << setprecision(4) << 12.0 << endl;
}

//>>
void testIstream()
{
    cout << "enter numbers: " << endl;
    int sum = 0;
    int input;
    //格式不正确抽取运算符将不会修改input的值，并返回0
    while (cin >> input)
    {
        sum += input;
    }
    cout << "last value  = " << input << endl;
    cout << "sum = " << sum << endl;
    cout << cin.bad() << endl  //0
         << cin.fail() << endl //1
         << cin.eof() << endl; //0
    //清楚状态位
    cin.clear();
    //不匹配的输入仍然停留在队列中
    cout << "enter another num: " << endl;
    while (!isspace(cin.get()))
    {
        continue;
    }
    // while (cin.get() != '\n')
    // {
    //     continue;
    // }
    cin >> input;
    cout << "the another num: " << input << endl;
}

//cin.get(ch)，逐个字符读取，也读区空格，直到读取到换行符为止
void testget1()
{
    int ct = 0;
    char ch;
    cin.get(ch);
    cout << ch << endl;
    while (ch != '\n')
    {
        cout << ch;
        ct++;
        cin.get(ch);
        // cin>>ch;抽取运算符这个例子会读到空格和换行符时停止读取，表示为跳过这个字符
    }
    cout << ct << endl;
}
//cin.get(ch)，读取到ch，也可以读取空格，换行符
void testget2()
{
    char ch = 's';
    cout << ch << endl;
    while (cin.get(ch)) //到达文件末尾时为false
    {
        cout << ch;
    }
    cout << "end" << endl;
}
//cin.get()返回一个数值
void testget3()
{
    int ch;
    while ((ch = cin.get()) != EOF) //到达文件末尾时为false
    {
        cout << ch;
    }
    cout << "end" << endl;
}

const int Limit = 5;

//读取最大数目字符，但是行中还有其他字符，failbit
//超过Limit的输入将会终止输入
//达到#字符，后面的字符依然合法，驻留在输入流中
void testgetline()
{
    char input[Limit];
    cout << "enter a line" << endl;
    cin.getline(input, Limit, '#');
    cout << input << endl;
    //这段代码可以清楚状态位
    // cout << cin.bad() << endl  //0
    //      << cin.fail() << endl //1
    //      << cin.eof() << endl; //0
    // cin.clear();
    cout << "next char: " << endl;
    char c;
    cin.get(c); //getline丢弃掉#字符
    cout << c << endl;
    if (c != '\n')
    {
        cin.ignore(Limit, '\n'); //读取并丢弃Limit个字符或者换行符
    }
    cout << "enter another char: " << endl;
    char e;
    cin.get(e);
    cout << e << endl;
}

//get(),保存了换行符
// 12345
// 1234
// last char is not 换行符
//空行
//空行
// 1
// 1
//空行
//空行
void testget()
{
    //分配动态内存
    char *input = new char;
    cout << "enter a line" << endl;//输入：12345分析
    //分隔符\n
    cin.get(input, 5);
    cout << input << endl;//这个地方添加的endl会影响换行的判断
    if (cin.get() == '\n')//这个地方得注意，会消耗掉队列中换行符
    {
        cout << "last char is 换行符" << endl;
    }
    else
    {
        cout << "last char is not 换行符" << endl;
        char c;
        cin.get(c);
        cout << c << endl;
        cin.get(c);
        cout << c << endl;
    }
    // 这个地方测试：
    // 如果读取了最大数目的字符，也就没有10字符长度，依然可以继续输入读取
    // 如果超过了10个字符，依然可以继续输入读取，但是队列中字符依然保留（包括换行符）
    char c;
    cin.get(c);
    cout << c << endl;
    delete input;
}
void testPeeker1()
{
    char ch;
    while (cin.get(ch))
    {
        if (ch != '#')
        {
            cout << ch;
        }
        else
        {
            cin.putback(ch);
            break;
        }
    }
    if (!cin.eof())
    {
        cin.get(ch);
        cout << ch << endl;
    }
    else
    {
        cout << "Enf of file reached\n";
        exit(0);
    }
    while (cin.peek() != '#')
    {
        cin.get(ch);
        cout << ch;
    }
    if (!cin.eof())
    {
        cin.get(ch);
        cout << ch << endl;
    }
    else
    {
        cout << "Enf of file reached\n";
        exit(0);
    }
}

void testPeeker2()
{
    char name[SLEW];
    cout << "enter yout name: ";
    //这里两种情况，输入太短或者太长
    cin.get(name, SLEW);
    if (cin.peek() != '\n')
    {
        cout << "soory,we only have enough room for " << name << endl;
    }
    eatline();
    cout << "Dear " << name << " ok." << endl;
}
void inputOneline(string &content);

//fout从程序逐个字节收集输出，当缓冲区填满后，边将缓冲区内容一同传输给目标文件
void testOfstream()
{
    ofstream fout;
    //有文件将打开文件并清空文件，没有文件将创建新的文件 out.open("/Users/jinlei/tempDir/one/text.txt");
    //发现不管相对路径还是绝对路径都没有问题
    fout.open("text.txt");
    fout.write("fuck", 10);
    fout << "fuxk";
    //这个地方关闭文件会刷新缓冲区
    fout.close();

    ifstream fin("text.txt");
    string content;
    getline(fin, content);
    cout << content << endl;
}

void testFileIO()
{
    string fileName;
    cout << "enter a file name: ";
    cin >> fileName;
    ofstream ofs(fileName.c_str());
    ofs << "For your eyes only!\n";
    cout << "Enter your ecret number: ";
    float secret;
    cin >> secret;
    ofs << "Your secret number is " << secret << endl;
    ofs.close();
    ifstream ifs(fileName.c_str());
    if (!ifs.is_open())
    {
        return;
    }
    cout << "Here are the contents of " << fileName << ":\n";
    char ch;
    while (ifs.get(ch))
    {
        cout << ch;
    }
    cout << "Done\n";
    ifs.close();
}

void testCount(int argc, char *argv[])
{
    if (argc == 1)
    {
        cerr << "Usage: " << argv[0] << " filename[s]\n";
        exit(EXIT_FAILURE);
    }
    ifstream ifs;
    long count = 0;
    long total = 0;
    char temp;
    for (size_t i = 1; i < argc; i++)
    {
        ifs.open(argv[i]);
        if (!ifs.is_open())
        {
            cerr << "Counld not open " << argv[i] << endl;
            ifs.clear();
            continue;
        }
        count = 0;
        //一个字节一个字节的读取
        while (ifs.get(temp)) //文件的结尾
        {
            count++;
        }
        cout << count << "char in " << argv[i] << endl;
        total += count;
        ifs.clear(); //重置流
        ifs.close(); //disconnect file
    }
    cout << total << " chars in all files\n";
}

void testTextappend()
{
    ofstream ofs;
    ofs.open("name", ios_base::out | ios_base::app);
    if (!ofs.is_open())
    {
        cout << "open the file is failed.";
        return;
    }
    ofs << "wohijinlei";
    ofs.put('n');
    ofs.write("jin", 3);
    ofs.close();
}

struct helloworld
{
    char name[12];
    double g;
};

void testBinary()
{
    helloworld h{
        "jinlei",
        29};
    ofstream ofs;
    ofs.open("name3.txt", ios_base::out | ios_base::binary);
    if (!ofs.is_open())
    {
        cout << "open the file is failed.";
        return;
    }
    ofs << "wohijinlei";
    ofs.write((char *)&h, sizeof(h));
    ofs.close();
}

#include <sstream>
void testStringIO()
{
    ostringstream ost;
    double price = 380.0;
    char *ps = "for a copy";
    ost.precision(2);
    ost << fixed;
    ost << "Pay only CHF " << price << ps << endl;
    string mesg = ost.str(); //将缓冲区的内容的字符串初始化为mesg对象
    cout << mesg << endl;

    istringstream ist("12 34 5");
    int n;
    int sum;
    while (ist >> n)
    {
        sum += n;
    }
    cout << sum << endl;
}

#include <cstdio>
void testTempName()
{
    cout << "This system can generate up to " << TMP_MAX                 //308915776
         << " temporary name of up tp " << L_tmpnam << " characters.\n"; //1024
    char pszName[L_tmpnam] = {'\0'};
    for (size_t i = 0; i < 10; i++)
    {
        char *c = mktemp(pszName);
        cout << pszName << endl;
    }
}

//__attribute__ ((__visibility__("default"))) 修饰到来类名的前面
//_LIBCPP_CONSTEXPR_AFTER_CXX11 constexpr 修饰到返回值的前面
void sum(std::initializer_list<double> list)
{
    double tot = 0;
    for (auto p = list.begin(); p != list.end(); p++)
    {
        tot += *p;
    }
    for (std::initializer_list<double>::iterator p = list.begin();
         p != list.end(); p++)
    {
        tot += *p;
    }
    cout << tot << endl;
}

typedef std::vector<std::string> vstring;
using uvs = std::vector<std::string>;
template <typename T>
using uvs2 = std::array<T, 12>;

void CNewShengming()
{
    uvs us;
    vstring vs;
    // uvs2<double> uvs2;
}

//以前C++提供一种语法，用于指示函数可能引发哪些异常
//void f(int) throw(bag_dog);
//void n(int) throw();
//现在摒弃这种异常规范
//然而指出函数不会引发异常有一定的价值--noexception
enum Dog
{
    ONE,
    TWO,
    THREE
};
enum struct Dog2
{
    ONE,
    TWO
};
// enum Dog3{ONE,TWO};//redefinition of enumerator 'ONE'
void testEnume(Dog2 d)
{
}
//枚举其实提供了一种创建名称常量的形式
//枚举名称的作用域为枚举定义所属的定义域，所以同名的两个枚举出现编译错误
void testEume(Dog d)
{
    Dog::ONE;
    testEnume(Dog2::ONE);
    //  testEnume(ONE);
    cout << static_cast<int32_t>(Dog::ONE) << endl;
}

//显示转换运算符 explicit
//单参数的构造函数，自动具备将单参数转换为对象
//转换函数--操作符重载函数

//类成员初始化
class Session
{
private:
    int32_t mem1 = 10;
    double mem2 = {111.11};
    int16_t mem3;

public:
    Session(){};
    Session(int16_t b) : mem2(b){};
    ~Session();
};

//基于范围的for循环
double prices[5] = {1, 2, 3, 4};
void testForeach()
{
    for (auto i : prices)
    {
        cout << i << endl;
    }
    for (auto &&i : prices)
    {
        //todo
    }
}
#include <array>
#include <list>
#include <valarray>
//新的STL容器
void testContainer()
{
    valarray<int32_t> v = {1, 2, 3, 4, 5};
    cout << v.size() << endl
         << v.sum() << endl
         << v.min() << endl
         << v.max() << endl;
    auto newAddValarray = v += 12;
    auto newShiftValarray = v.shift(2);
    auto newCircleShiftValarray = v.cshift(2);
    auto newValarray = v.apply([](int32_t x) {
        return x * x;
    });
    v.resize(2, 23); // int a = int(5);
    for (auto i : newCircleShiftValarray)
    {
        cout << i << endl;
    }
    std::list<int32_t> list;
    list.insert(list.begin(), 21);
    for (auto i : list)
    {
        cout << i << endl;
    }
    //why we can use this?
    std::array<int32_t, 12> ms = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int *f = ms.begin();
    cout << f << endl;
    for (int *i = f; i < ms.end(); i++)
    {
        cout << i << endl;
        cout << *i << endl;
    }

    for (auto i : ms)
    {
        cout << i << endl;
    }

    // int8_t w = ms.__elems_[0];
    // cout << w << endl;
    // cout<<ms[0]<<endl;
    // cout<<ms.at(1)<<endl;
}

void CNew11()
{
    int8_t a;
    int8_t b = 10;
    int16_t g = 10;
    int32_t e = 10;
    int64_t f = 10;
    int c = 10;
    long h = 10;
    INT8_C(10);
    char ca = 'a';
    char16_t cb = 'a';
    char32_t cc = 'a';
    // char* con = r"jinlei";
    cout << sizeof(b) << endl
         << sizeof(g) << endl
         << sizeof(e) << endl
         << sizeof(e) << endl
         << sizeof(h) << endl
         << sizeof(ca) << endl  //1
         << sizeof(cb) << endl  //2
         << sizeof(cc) << endl; //4
    cout << ca << (char)cb << (char)cc << endl;
    int32_t ii = {1};
    cout << LONG_MAX << endl;   //9223372036854775807
    cout << INT32_MAX << endl;  //2147483647
    cout << CHAR_BIT << endl;   //8
    cout << ULLONG_MAX << endl; //18446744073709551615 = 9223372036854775807*2
    cout << "\u00F6" << endl;
    float fa = 10.0 / 3;
    cout << fa << endl;
    double da = 10.0 / 3;
    cout << da << endl;
    int64_t factor = 100000000000L;
    cout.setf(ios_base::fixed);
    cout << fa * factor << endl; //333333331968.000000
    cout << da * factor << endl; //333333333333.333374
    //有效位数：c++要求float32位，double64位，但是实际float 6位，double 15位
    //指数位数：至少37 -37
    float fff = 1.01234567890123456789e38;   //101234566793021598177691506007701716992.000000
    double ddd = 1.01234567890123456789e108; //101234567890123460063797408509923867893735953251135413766668542803968.000000
    cout << fff << endl;
    cout << ddd << endl;
    cout << ddd * 2 << endl;
    cout << __DBL_MAX_10_EXP__ << endl; //308
    cout << __FLT_MAX_10_EXP__ << endl; //38
    cout << __FLT_MAX_EXP__ << endl;    //128

    char cc1 = 1234456;
    cout << cc1 << endl;
    // char cc2 = {1122344};//初始化列表语法禁止缩窄语法，compile error
    // cout<<cc2<<endl;
}

void showUseless();
void showSomeclass();
void showFunction();
void showRandomFile();
void showComposeData();
void showCstring();
void showString();
void showAutoPointer();
void showSTL();
using namespace jinlei;
using jinlei::__showSomeClass; 
int main(int argc, char *argv[])
{
    cout << "argc: " << argc << endl;
    for (size_t i = 0; i < argc; i++)
    {
        //第一个参数: /Users/jinlei/VSCodeWorkSpace/firstC++/helloworld
        cout << argv[i] << endl;
    }
    // testOstreamPut();
    // testOtreamFormat();
    // testIstream();
    // testget1();
    // testget2();
    // testget3();
    ///testget4();
    // testgetline();
    // testget();
    // testPeeker1();
    // testPeeker2();

    // char* content = new char;
    // string inputString;
    // inputOneline(inputString);
    // cout<<inputString<<endl;
    // testOfstream();
    // testFileIO();
    // testCount(argc, argv);
    // testTextappend();
    // testBinary();
    // testTempName();
    // testStringIO();
    // CNew11();
    // sum({1, 2, 3});
    // testEume(THREE);
    // testContainer();
    {
        // showRandomFile();
    }
    __showSomeClass(0);
    return 0;
    vector<string> msg{"hello", "C++"};
    int length = msg.size();
    for (size_t i = 0; i < length; i++)
    {
        cout << msg.at(i) << '\n';
    }
    for (const string &world : msg)
    {
        cout << world << '\n';
    }
    cout << "what" << endl;
    return 0;
}