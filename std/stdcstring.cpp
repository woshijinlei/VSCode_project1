#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

static void showArrayString(const char w[], int lenght)
{
    int count = 0;
    cout << "showArray: \n";
    for (size_t i = 0; i < lenght; i++)
    {
        cout << count++ << ":" << w[i] << " ";
    }
    cout << "count: " << count << "\n";
}

static void showArrayString2(const char *w, int lenght)
{
    int count = 0;
    cout << "showArray: \n";
    for (size_t i = 0; i < lenght; i++)
    {
        cout << count++ << ":" << w[i] << " ";
    }
    cout << "count: " << count << "\n";
}
static void showStrncpy()
{
    size_t a = 10;
    cout << "size_t" << sizeof a << endl; //8字节
    //字符串地址
    const char *c1 = "w";
    cout << c1 << " " << (void *)c1 << endl; //0x100ef1558
    //字符串长度
    int lenght = strlen(c1); //可见字符串长度
    cout << "lenght: " << lenght << endl;
    //第一种strncpy
    char s2[3] = {'a', 'a', 'a'}; //why can't ={'\0'};
    showArrayString2(s2, sizeof(s2));
    char *s22 = strncpy(s2, c1, lenght);
    s2[lenght] = '\0';
    cout << "s2: " << s2
         << " s2地址：" << (void *)s2
         << " s22地址：" << (void *)s22
         << " s22：" << s22
         << " s2 size: " << sizeof s2
         << " s22 size: " << sizeof s22 //s2: woshijinlei s2地址：0x7ffee690f1d0 s22地址：0x7ffee690f1d0 s22：woshijinlei s2 size: 10 s22 size: 8
         << endl;                       //(初始化没有定义数组中元素，则元素值是不确定的，为之前驻留在其中的值)
    showArrayString(s22, sizeof(s2));
    //第二种strncpy
    char *s3 = new char[lenght + 1]{'\0'};
    strncpy(s3, c1, lenght);
    cout << "s3: " << s3 << " " << (void *)s3 << endl; //s3: w 0x7ff7cfc02a10
    showArrayString(s3, lenght + 1);
    //检查是否生成副本
    c1 = "woshijinhua";
    cout << c1 << endl
         << s2 << "\n"
         << s3 << endl;
    //数组字符串和数组字符
    char t1[] = {'a', 'b', 'a', 'b'};
    cout << t1 << endl; //abab*��� what this?
    char t2[] = {'a', 'b', '\0'};
    cout << t2 << endl; //ab
}
static void showStrcat()
{
    char *c = new char[100];
    // char c[100] = {'a'};
    // char *c = (char *)malloc(sizeof(char) * 4);
    const char *c2 = "www";
    showArrayString(c, 15);
    char *w = strcat(c, c2);
    cout << w << " " << (void *)w << endl;
    cout << c << " " << (void *)c << endl;

    strlcat(c, c2, strlen(c2));
    cout << c << endl;
}
static void showMemcpy()
{
    // char *d = "123";//Bus error: 10
    // char d[3] = {'a','a','a'}; //12a12���
    char *d = new char[1]; //发现申请的内存过少，也可以输出正确结果，可能会覆盖其他正常使用的内存
    const char s[] = {'1', '2'};
    memcpy(d, s, 2);
    cout << d << endl;
    showArrayString(d, 3);

    char a[] = {'a', '\0', 'a'};
    char b[] = {'a', 'a', '\0'};
    char c[] = {
        'a',
        'a',
    };
    cout << strlen(a)        //1
         << " " << strlen(b) //2
         << " " << strlen(c) //4(可能继续读取内存找到'\0'字符时才停止)
         << endl;
}
static void temp()
{
    cout << "temp: " << endl;
    int temp0[12] = {0};
    char *temp1 = new char[12]{'a', 'b'};
    char *temp2 = new char[3]{'a', 'b', '\0'};
    char *temp3 = "woshijinlei";
    cout << temp0 << endl; //非字符串默认打印指针的地址
    cout << temp1 << endl; //new 字符串默认打印字符
    cout << temp2 << endl; //new 字符串默认打印字符
    cout << temp3 << endl; //char* 字符串默认打印字符
}
static void showStrerror()
{
    // strerror(1);
    char *buffer = new char[100]{'a', 'b'};
    strerror_r(5, buffer, 100);
    //Undefined error: 0
    //Operation not permitted 1
    //No such process 3
    //Interrupted system call 4
    //Input/output error 5
    cout << buffer << endl;
}
static void showStrcmp()
{
    const char *one = "j";
    const char *two = "j";
    bool b = strcmp(one, two);
    cout.setf(ios_base::boolalpha);
    cout << b << endl;
    bool b2 = strncmp(one, two, 1);
    cout << b2 << endl;
    bool b3 = strcasecmp(one, two);
    cout << b3 << endl;
    cout << b2 << endl;
    bool b4 = strncasecmp(one, two, 1);
    cout << b4 << endl;
}
//第一次出现分割后的字符串（包含字符串）
static void showStrstr()
{
    const char *three = "wioshijinleiwioshijinleiwioshijinlei";
    const char *four = "jinle";
    const char *str = strstr(three, four);
    cout << str << endl; //jinleiwioshijinleiwioshijinlei
}
//第一次出现分割后的字符串（包含字符）
static void showStrchr()
{
    char *one = "wioshijinleiwioshijinleiwioshijinlei";
    char *ch = strchr(one, 'i');
    cout << ch << endl; //ioshijinleiwioshijinleiwioshijinlei
}
//brk中的每一个字符都会得到和two进行匹配，只要成功则停止检验
static void showStrpbrk()
{
    const char *two = "adjinjijinaji";
    const char *brk = strpbrk(two, "fbd");
    cout << brk << endl; //djinjijinaji
}
//第一次出现这个字符串的位置下标
static void showStrspn()
{
    const char *two = "da";
    const char *spn = "jfdafaf";
    int index = strspn(two, spn);
    cout << index << endl; //2
}
//第一次出现这个字符的位置下标(four中匹配任意一个)
static void showStrcspn()
{
    const char *two = "jinjijinaji";
    const char *four = "hfdiaak";
    int idex = strcspn(two, four);
    cout << idex << endl;
}

static void showMemset()
{
    char three[10];
    memset(three, 'a', 5);
    cout << three << endl;
}

static void showstrlcpy()
{
    char *m_tr = "123";
    int len = strlen(m_tr);
    cout << "lenght: " << len << endl;
    char *str = new char[1];
    //可不可以简单理解，返回发生实际复制的字符个数
    //n:同样具有截断原始字符串的作用或者就是原始字符串的长度size
    size_t size = strlcpy(str, m_tr, 2); //size_t	 strlcpy(char *__dst, const char *__source, size_t __size);
    cout << "size: " << size << endl;    //3
    cout << "c0: " << str << endl;       //1
}
static void showstrncpy()
{
    char *m_tr = "123";
    int len = strlen(m_tr);
    cout << "lenght: " << len << endl;
    char *str = new char[1];
    char *c1 = strncpy(str, m_tr, 3); //char	*strncpy(char *__dst, const char *__src, size_t __n);用来替代strcpy，防止覆盖相邻的内存
    cout << "c1: " << endl;
    cout << c1 << endl;  //123
    cout << str << endl; //123--同样会发生了内存覆盖，但可以通过n指定复制的长度来避免
}
static void showstrcpy()
{
    char *m_tr = "123";
    int len = strlen(m_tr);
    cout << "lenght: " << len << endl;
    char *str = new char[1];      //设置1
    char *c2 = strcpy(str, m_tr); //char	*strcpy(char *__dst, const char *__src);
    cout << "c2: " << endl;
    cout << c2 << endl;          //123--发生了内存覆盖
    cout << (void *)c2 << endl;  //0x7fb897402a10
    cout << (void *)str << endl; //0x7fb897402a10
}
void showCstring()
{
    // memmove(one, two, 3);
    // cout << one << endl;
    // showStrbrk();
    // showStrchr();
    // showStrSegmentation();
    // showStrspn();
    showstrlcpy();
}