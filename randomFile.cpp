#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

static const int LIM = 20;

struct planet
{
    char name[LIM];
    double population;
    double g;
};
const char *file = "planets.dat";
inline void eatliner()
{
    while (std::cin.get() != '\n')
    {
        continue;
    }
}

#include <fstream>
static void addNewData()
{
    using namespace std;
    planet pl;
    ofstream ofs(file, ios_base::out | ios_base::app | ios_base::binary);
    if (!ofs.is_open())
    {
        cerr << "Can't open " << file << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Enter planer name or enter blank line to quit: \n";
    cin.get(pl.name, 20);
    while (pl.name[0] != '\0')
    {
        eatliner();
        cout << "Enter planetary population: ";
        cin >> pl.population;
        cout << "Enter planer's acc: ";
        cin >> pl.g;
        eatliner();
        ofs.write((char *)&pl, sizeof(pl));
        cout << "Enter planet name or enter blank line to quit: \n";
        cin.get(pl.name, 20);
    }
}

void showRandomFile()
{
    // addNewData();
    // return;
    using namespace std;
    //构建结构体
    planet pl;
    //浮点数格式(非科学基数法)
    cout << fixed;
    //构建fstream
    fstream finout;
    //in：读取（default）
    //out: 没有文件建立文件  文件存在删除内容在写入内容（defalut）
    //out app: 只追加
    //in out: 读写（指定位置写入）
    finout.open(file, ios_base::in | ios_base::out | ios_base::binary);
    int ct = 0;
    if (finout.is_open())
    {
        //输入流位置0
        finout.seekg(0);
        cout << "Here is the content of " << file << endl;
        while (finout.read((char *)&pl, sizeof(pl))) //读到最后返回-1 or right?
        {
            cout << ct++ << ": " << setw(LIM) << pl.name << ": "
                 << setprecision(12) << setw(12) << pl.population
                 << setprecision(6) << setw(6) << pl.g << endl;
        }
        //文件读取完毕是不是文本末尾状态
        if (finout.eof())
        {
            finout.clear();
        }
        else
        {
            cerr << "Error in reading " << file << endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        cerr << file << "could not be opended--bye" << endl;
        exit(EXIT_FAILURE);
    } 
    cout << "Enter the recored number you wish to change: ";
    int64_t rec;
    cin >> rec;//直接输入数字
    eatliner(); //git rid of newline
    if (rec < 0 || rec >> ct)
    {
        cerr << "Invalid record number--bye." << endl;
        exit(EXIT_FAILURE);
    }
    //fps
    streampos place = rec * sizeof(pl);
    finout.seekg(place);
    cout << "your selection:\n";
    cout << rec << ": " << setw(LIM) << pl.name << ": "
         << setprecision(0) << setw(12) << pl.population
         << setprecision(2) << setw(6) << pl.g << endl;
    //check state
    if (finout.eof())
    {
        finout.clear();
    }
    cout << "Enter planet name: ";
    cin.get(pl.name, LIM);
    eatliner();
    cout << "Enter population: ";
    cin >> pl.population;//忽略空格和换行
    cout << "Enter acc: ";
    cin >> pl.g;//忽略换行和空格
    finout.seekp(place); //go back
    finout.write((char *)&pl, sizeof(pl)) << flush;
    //写入操作后再一次检查状态
    if (finout.fail())
    {
        cerr << "Error on attempted write.\n";
        exit(EXIT_FAILURE);
    }
    ct = 0;
    finout.seekg(0);
    cout << "Here are the new contents:" << endl;
    while (finout.read((char *)&pl, sizeof(pl)))
    {
        cout << ct++ << ": " << setw(LIM) << pl.name << ": "
             << setprecision(0) << setw(12) << pl.population
             << setprecision(2) << setw(6) << pl.g << endl;
    }
    finout.close();
    cout << "Done.\n";
}
