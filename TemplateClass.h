//模版不是类和成员函数定义，他们不能单独编译
//他们是C++编译指令，说明类如何生成类和成员函数定义
//不能将模版类成员函数放到独立的实现文件中
#ifndef STACKTP_H
#define STACKTP_H
#include <iostream>
#include <string>

namespace jinlei
{
    typedef int item;
    class Stack1
    {
    private:
        enum
        {
            MAX = 10
        };
        item items[MAX];
        item top;

    public:
        Stack1(){};
        bool isEmpty() const;
        bool isFull() const;
        bool pup(item &item);
        bool push(const item &item);
        ~Stack1() {}
    };

    template <typename Type>
    class Stack2
    {
    private:
        enum
        {
            MAX = 10
        };
        Type items[MAX];
        Type top;

    public:
        Stack2();
        bool isEmpty() const;
        bool isFull() const;
        bool pup(Type &item);
        bool push(const Type &item);
        ~Stack2(){};
    };
    template <typename Type>
    Stack2<Type>::Stack2()
    {
        top = 0;
    }
    template <typename Type>
    bool Stack2<Type>::isEmpty() const
    {
        return top == 0;
    }
    template <typename Type>
    bool Stack2<Type>::isFull() const
    {
        return top == MAX;
    }
    template <typename Type>
    bool Stack2<Type>::push(const Type &item)
    {
        if (top < MAX)
        {
            items[top++] = item; //top==1,top++=0
            return true;
        }
        else
        {
            return false;
        }
    }
    template <typename Type>
    bool Stack2<Type>::pup(Type &item)
    {
        if (top > 0)
        {
            item = items[--top];
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Type>
    class Stack
    {
    private:
        enum
        {
            SIZE = 10
        };
        int stacksize;
        Type *items; //hold stack items
        int top;

    public:
        explicit Stack(int ss = SIZE);
        Stack(const Stack &s);
        Stack &operator=(const Stack &s);
        ~Stack() { delete[] items; };
        bool isempty() { return top == 0; };
        bool isfull() { return top == stacksize; };
        bool push(const Type &item);
        bool pop(Type &item);
    };
    template <typename Type>
    Stack<Type>::Stack(int ss) : stacksize(ss), top(0)
    {
        items = new Type[ss];
    }
    template <typename Type>
    Stack<Type>::Stack(const Stack &s)
    {
        stacksize = s.stacksize;
        top = s.top;
        delete[] items; //need this?不需要，因为是构造函数
        items = new Type[stacksize];
        for (int i = 0; i < stacksize; i++)
        {
            items[i] = s.items[i];
        }
    }
    template <typename Type>
    bool Stack<Type>::push(const Type &t) //是引用
    {
        if (top < stacksize)
        {
            items[top++] = t;
            return true;
        }
        else
        {
            return false;
        }
    }
    template <typename Type>
    bool Stack<Type>::pop(Type &item) //是引用
    {
        if (top > 0)
        {
            item = items[--top];
            return true;
        }
        else
        {
            return false;
        }
    }
    template <typename Type>
    Stack<Type> &Stack<Type>::operator=(const Stack<Type> &stack)
    {
        if (this == &stack)
        {
            return *this;
        }
        delete[] this->items; //此时items实例是存在的
        stacksize = stack.stacksize;
        top = stack.top;
        items = new Type[stacksize];
        for (size_t i = 0; i < stacksize; i++)
        {
            items[i] = stack[i];
        }
        return *this;
    }

    template <class T, int n>
    class ArrayTp
    {
    private:
        T ar[n];

    public:
        ArrayTp(){};
        explicit ArrayTp(const T &t);
        virtual T &operator[](int i);
        virtual T operator[](int i) const;
    };
    template <class T, int n>
    ArrayTp<T, n>::ArrayTp(const T &t)
    {
        for (size_t i = 0; i < n; i++)
        {
            ar[i] = t;
        }
    }
    template <class T, int n>
    T &ArrayTp<T, n>::operator[](int i)
    {
        if (i < 0 || i >= n)
        {
            std::cerr << "Error in array limits: " << i << " is out of range" << std::endl;
            exit(EXIT_FAILURE);
        }
        return ar[i];
    }
    template <class T, int n>
    T ArrayTp<T, n>::operator[](int i) const
    {
        if (i < 0 || i >= n)
        {
            std::cerr << "Error in array limits: " << i << " is out of range" << std::endl;
            exit(EXIT_FAILURE);
        }
        return ar[i];
    }
    template <class T1, class T2 = int>
    class Pair
    {
    private:
        T1 a;
        T2 b;

    public:
        Pair() {}
        Pair(const T1 aval, const T2 bval) : a(aval), b(bval) {}
        T1 &first();
        T2 &second();
        T1 first() const { return a; }
        T2 second() const { return b; }
    };
    template <class T1, class T2>
    T1 &Pair<T1, T2>::first()
    {
        return a;
    }
    template <class T1, class T2>
    T2 &Pair<T1, T2>::second()
    {
        return b;
    }

    template <>
    class Pair<char, char>
    {
        ~Pair()
        {
            std::cout << "~Pair" << std::endl;
        }
    };

} // namespace jinlei
#endif