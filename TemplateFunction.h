//模版函数为何可行：
//1.通过将类型通过参数传递给模版，可以使编译器生成该类型的参数
//2.（模版函数本行并不定义任何函数，而只是告诉编译器如何定义函数，如果交换int则生成int这样的函数）
//3.将同一种算法用于不同类型的函数
//4.最终的代码不包含任何模版，而只是包含了为程序生成的实际函数，使用模版可以生成多个函数定义同时简单可靠
//5.比如我们在main函数中调用： SwapValue(a,b)属于隐士实例化
template <typename T>
void SwapValue(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <typename T>
void SwapValue(T a[], T b[], int n)
{
    T temp;
    for (size_t i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
struct job
{
    char* name;
    int age;
};

template<> void SwapValue<job>(job& a,job& b);