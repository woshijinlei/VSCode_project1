#include <vector>
#include <iostream>

using namespace std;
//新的函数声明语法
void a(int a);
auto b(int a)->void;

auto mod3 = [](int x)->bool{return x%3;};
void needFn(bool (*f)(int)){//函数指针
    auto b = mod3(3);
}

class f_mod
{
private:
    int div;
public:
    f_mod(int d = 1):div(d){};
    bool operator()(int x){
        return x%3;
    } 
};

static void showfmod(){
    //显式构造函数创建存储特定值的f对象
    f_mod f(3);
    //函数形式调用
    bool i = f(3);
    //函数符-使用这个匿名对象的operator()()方法
    vector<int> v(100);
    generate(v.begin(),v.end(),rand);
    count_if(v.begin(),v.end(),f_mod(2));
}
 
inline bool f3(int x){return x%3==0;};
//函数对象：函数指针（函数名） 函数对象   lambda
void showFunction(){
    vector<int> v(100);
    generate(v.begin(),v.end(),rand); 
    int c = count_if(v.begin(),v.end(),f3);
    cout<<"c: "<<c<<endl;
    int div = 4;
    int g = count_if(v.begin(),v.end(),[&](int x){//需不需要->bool返回类型后置？
        int y = 10;
        return (x+y)%div;
    });
    cout<<"y: "<<g<<endl;
}