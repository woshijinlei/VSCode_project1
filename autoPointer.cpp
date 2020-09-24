#include <iostream>
#include <memory>
#include <string>

using namespace std;
class Report
{
private:
    string str;

public:
    Report() : Report("default"){};
    Report(string m_str) : str(m_str) {}
    ~Report()
    {
        cout << "Object deleted\n";
    }
    void comment() { cout << str << endl; }
};
void showUniquePtr()
{
    unique_ptr<Report> pu(new Report("unique"));//pu将会存在一段时间
    unique_ptr<Report> pu2;
    // pu2 = pu;//compile error
    pu2 = unique_ptr<Report>(new Report(""));//
}
void showUniquePtr2()
{
    unique_ptr<Report[]> pda(new Report[5]);
    pda.get()[0].comment();
}
//what happened？
unique_ptr<int> make_int(int value){
    return unique_ptr<int>(new int(value));
}
void show_int(unique_ptr<int>& pi){
    cout<<*(pi.get())<<endl;
}
#include <vector>
void showPtrVector(){
    vector<unique_ptr<int>> vp(10);
    for (size_t i = 0; i < vp.size(); i++)
    {
        vp[i] = make_int(i);
    }
    vp.push_back(make_int(rand()%1000));
    for_each(vp.begin(),vp.end(),show_int);
}
void showAutoPointer()
{
    {
        std::shared_ptr<Report> pd(new Report("share_ptr"));
        pd->comment();
    }
    {
        std::unique_ptr<Report> pd(new Report("share_ptr"));
        pd->comment();
    }
    showUniquePtr2();
    showPtrVector();
}