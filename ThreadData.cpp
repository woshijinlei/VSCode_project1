#include <thread>
#include "StringBad.h"
#include <iostream>
#include <vector>
#include <list>
#include <mutex>
using namespace std;
void printData(int inum)
{
    cout << "printData: " << std::this_thread::get_id() << " " << inum << endl;
}
list<thread> threads;

void showListThreads()
{
    for (size_t i = 0; i < 5; i++)
    {
        threads.push_back(thread(printData, 1));
    }
    for (auto &&i : threads)
    {
        i.join();
    }
    threads.clear();
    cout << "main thread is over." << endl;
}
class Message
{
private:
    list<int> msgQueue;
    mutex m;
public:
    void inMsgReviQueue()
    {
        lock_guard<mutex> sbgurad(m);
        for (size_t i = 0; i < 1000; i++)
        {
            // m.lock();
            cout << "插入元素：" << endl;
            msgQueue.push_back(i);
            // m.unlock();
        }
    }
    void outMsgReviQueue()
    {
        for (size_t i = 0; i < 1000; i++)
        {
            m.lock();
            if (msgQueue.empty())
            {
                cout << "queue is empty.";
            }
            else
            {
                cout << "移除元素" << endl;
                msgQueue.pop_front();
            }
            m.unlock();
        }
    }
};

void showThreadData()
{
    Message a;
    thread s(&Message::outMsgReviQueue, &a);
    thread b(&Message::inMsgReviQueue, &a);
    s.join();
    b.join();
    cout << "main thread is over." << endl;
}