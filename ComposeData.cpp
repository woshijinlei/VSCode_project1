#include <iostream> 
using namespace std;
static void showArray()
{
    short a[12]; //这个申明创建一个名为a的数组，该数组有12个元素，每个元素都可以存储一个short类型的值
    for (size_t i = 0; i < 12; i++)
    {
        // -2192
        // -21008
        // 32767
        // 0
        // -2192
        // -21008
        // 32767
        // 0
        // 4784
        // -5414
        // 32766
        // 0
        cout << a[i] << endl; //元素值并不会确定，由之前驻留在该内存中的值
    }
    //sizeof 返回类型或者数据对象的长度
    cout << sizeof(a[0]) << endl //2 byte
         << sizeof(a) << endl;   //24 byte
    int lenght = 12;
    // short b[lenght] = {0}; why can not?
    short d[lenght]; //why can?
    d[0] = 12;
    //一个好处是禁止缩窄转换
    short b[12] = {0};
    short c[] = {1, 2, 3, 4, 5};
    short f[32] = {};
}

//1.计算机使用数字代码来存储字符
//2.ACII码是美国最常用的编码，他是Unicode的一个子集
//3.C++标记字符的方式是用单引号扩起来‘A',也可以用反斜杠配合八进制或者十六禁止编码表示单个字符，‘\012' '\0xa'
//4.\转移字符也可嵌入到字符串中
static void showChar()
{
    //概念：字符串常量或者字符串字面值
    //用引号扩起来的字符串隐士包含结尾的空字符，程序读取字符串到char数组时，自动在结尾加上空字符
    // char a[4] = "1234";//error
    char a[5] = "1234"; //char字符串数组需要包含空字符
    int a2[5];
    int w = 'a'; //在ASCII中，‘a'只会97的一种表示
    int b = 0;
    cout << w << endl;          //97
    cout << sizeof(&w) << endl  //8个字节   地址长度
         << sizeof(a2) << endl  //20个字节   数组总长度（每个元素字节长度叠加）
         << sizeof(a) << endl   //5个字节   字符串总长度（包括空字符）实际是数组长度
         << strlen(a) << endl   //4个字节   可见字符
         << sizeof(&a) << endl  //8个字节   地址长度
         << sizeof(b) << endl   //4个字节   int变量长度
         << sizeof('a') << endl //1个字节   单个字符长度
         << sizeof(32) << endl; //4个字节   int值长度
    //字符串拼接：空格或者换行或者制表符串联起来的字符串
    char c[32] = "jinlei"
                 "jinhua";
    cout << c << endl;
}

static void showString()
{
    string s1;
    string s2 = "w";
    string s3 = {"woshijinlei"};
    cout << s1 << endl;
    cout << s2 << endl;
    cout << sizeof(s1) << endl  //内存占用大小：why 24 字节
         << sizeof(s2) << endl; //内存占用大小：why 24 字节
    string one = "one";
    string two = "two";
    string three = one + two;
    cout << &one << endl    //0x7ffeee48c230
         << &two << endl    //0x7ffeee48c218
         << &three << endl; //0x7ffeee48c200
    string ss1 = "ss1";
    string ss2 = ss1;
    ss1 = "new ss1";
    cout << ss1 << endl; //new ss1
    cout << ss2 << endl; //ss1   这个地方应该是深赋值运算符
    //原始字符串
    char rc[] = R"(woshijinlei\n")";
    char rc2[] = R"+*("(how are you?)",she whispered.)+*"; //R"+*(   )+*"
    cout << rc << endl;
    cout << rc2 << endl;
}

static void showStringApi()
{
    string s = "wohijinlei";
    string append = s.append("jinhua");
    cout << s << endl;       //wohijinleijinhua
    cout << &s << endl;      //0x7ffee124b288
    cout << &append << endl; //0x7ffee124b270
    string assign = s.assign({'1', '2'});
    cout << assign << endl   //12
         << s << endl        //12
         << &s << endl       //0x7ffee674a288
         << &assign << endl; //0x7ffee7b20248
    char &at = s.at(0);
    cout << at << endl; //1
}
struct inflatable
{
    char name[20];
    float volume;
    double price;
};

//数据占用的地址是相同的
//分配的公用体长度为其最大成员长度
union id
{
    long id_num;
    char id_char[20];
};

enum bits
{
    ONE = 0,
    TWO = 1,
    THREE = 3
}; //枚举类型的long类型的值

static void showStuct(id id, bits b)
{
    inflatable i = {"jinhua", 12.3, 11.0};
    cout << i.name << i.volume << i.price << endl;
    inflatable j;
    cout << "struct: " << endl;
    cout << sizeof(i) << endl; //32
    cout << sizeof(j) << endl; //wo can find memeory is ths same!20+4+8 = 32
    cout << "union: " << endl;
    cout << id.id_num << endl;
    cout << sizeof(id) << endl;
    cout << "enum: " << endl;
    bits bits = bits::ONE;
    cout << bits << endl;
    cout << b << endl;
    cout << sizeof(b) << endl;
    cout << sizeof(bits) << endl;
}

static void showPointer()
{
    int a;
    inflatable i;
    //     p���
    // 6.95313e-310
    // 4.59163e-41
    //再次说明未初始化的值是未确定的
    cout << a << endl
         << i.name << endl
         << i.price << endl
         << i.volume << endl;
    inflatable j = {"jinlei", 29, 100};
    inflatable *pj = &j;
    inflatable **pj2 = &pj;
    cout << pj << endl            //地址：一个十六进制的值 0x7ffeeebc2258
         << &pj << endl           //地址：这个指针变量的地址 0x7ffeef297250
         << pj2 << endl           //0x7ffeef297250
         << sizeof(pj) << endl    //8个字节
         << (*pj).volume << endl; //29

    //指针：在运行阶段分配未命名的内存来存储值
    //指针：执行一个变量的地址
    int *age = new int;
    delete age; //这会删除age指向的内存，但是不会删除age本身，可以继续指向其他内存
    inflatable *ni = new inflatable{"jinlei", 21, 100};
    inflatable *ni2 = new inflatable;
    cout << "test new default: " << endl;
    //通过new分配的未初始化的值具有默认值
    cout << ni->name << endl
         << ni2->name << endl    //空
         << ni2->price << endl   //0
         << ni2->volume << endl; //0
    cout << "test new array: " << endl;
    int array1[3] = {0};
    int *array2 = new int[3]{0}; //这个地方不能使用=号
    for (size_t i = 0; i < 3; i++)
    {
        cout << array1[i] << endl;
        cout << array2[i] << endl;
    }
    cout << "enter lenght:\n";
    int length = 0;
    cin >> length;
    int array3[length];
    array3[0] = 1;
    array3[1] = 2;
    array3[2] = 3;
    int *array4 = new int[length];
    array4[0] = 1;
    array4[1] = 2;
    array4[2] = 3;
    for (size_t i = 0; i < length; i++)
    {
        cout << array3[i] << endl;
        cout << array4[i] << endl;
    }
    delete[] array4;
    cout << "what is array name:\n";
    int array5[10];
    int(*pss)[10] = &array5; //这个指向20个元素的数组的地址
    //数组名解释为数组第一个元素的地址
    cout << array5 << endl  //0x7ffee401f140
         << &array5 << endl //0x7ffee401f140 这里对数组名获得地址和array是相同的，但是表达的含义确实不同的
         << sizeof(array5) << endl
         << sizeof(array5[0]) << endl
         << &array5[0] << endl;
    //这里字符串字面值可能编译器保存多个副本也可能只会保存一个副本，如果后者，则会印象其他地方的使用情况，所以申明为const
    //可以采用strcpy()库函数实现copy副本，注意数组后面内存被覆盖的情形，采用strncpy();--一个主要的用途是将字符串复制到数组
    const char *name = "woshijinlei";
}

//问题：输入year后，换行符还在队列中，造成getline直接读取空行
static void showSimpleInput()
{
    cout << "Enter year: " << endl;
    int year;
    cin >> year;
    cout << "Enter address: " << endl;
    cin.get(); //消耗掉换行符
    char address[20];
    cin.getline(address, 20);
    cout << "result: " << year << " " << address << endl;
}

void showComposeData()
{
    // showArray();
    // showChar();
    // showSimpleInput();
    // showString();
    // showStringApi();
    // id i;
    // i.id_num = 10;
    // showStuct(i,bits::ONE);
    showPointer();
}