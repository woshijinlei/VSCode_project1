//内置C++数据类型分两组：基本数据类型和复合数据类型

//基本数据类型：整形和浮点型
//复合类型：数组 字符串 指针 结构

//int braincount;
//brancount = 100;
//含义：声明中使用的类型描述了信息的类型，通过变量名符号表示信息的值
//含义：程序找到一块能够存储整数的内存，将该内存单元标记为braintcount，并将100复制到该内存单元中，然后在程序中使用braintcount来访问该内存单元

//整形字面值：1 0x1 01  1L
//1492: 这种类型如果有后缀则表示其他类型，如果值太大则转换为其他类型，否则都为int

//char型和小整形：
//字符变量和字符常量

//char字面值：
//1.常见的形式：'a'
//2.转意序列：有些字符通过键盘并不能键入enter，程序编辑器将enter解释为在源码中切换下一行，双引号C++赋予来新的含义，也不能放到字符串中 ,比如\n表示n作为换行符而不是常规字符n，\“表示双引号作为常规字符
//3.Unicode编码：ASCII字符集为其子集

//const限定符：限定声明的含义，如果对const修饰的变量进行更改，则g++编译器将报错

//有效位数：c++要求float32位，double64位，但是实际float 6位，double 15位
//指数位数：至少37 -37
void testBaseData()
{
}