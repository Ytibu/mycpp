#include <iostream>
#include <string>
using std::cout;
using std::string;

/**
 * 利用类模板实现一个栈
 */

template <class T, int kCapacity = 10>
class Stack
{
public:
    Stack() : _top(-1), _data(new T[kCapacity]()) {}
    ~Stack()
    {
        if (_data)
        {
            delete[] _data;
            _data = nullptr;
        }
    }
    bool empty() const;
    bool full() const;
    void push(const T &);
    void pop();
    T top();

private:
    int _top;
    T *_data;
};

template <class T, int kCapacity>
bool Stack<T, kCapacity>::empty() const
{
    return _top == -1;
}

template <class T, int kCapacity>
bool Stack<T, kCapacity>::full() const
{
    return _top == kCapacity - 1;
}

template <class T, int kCapacity>
void Stack<T, kCapacity>::push(const T &value)
{
    if (full())
        throw "Stack is full";
    _data[++_top] = value;
}

template <class T, int kCapacity>
void Stack<T, kCapacity>::pop()
{
    if (empty())
        throw "Stack is empty";
    _top--;
}

template <class T, int kCapacity>
T Stack<T, kCapacity>::top()
{
    if (empty())
        throw "Stack is empty";
    return _data[_top];
}

void test1()
{
    Stack<int, 10> s;
    cout << "empty? " << s.empty() << "\n";
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    cout << "top: " << s.top() << "\n";
    s.push(6);
    s.push(7);
    cout << "empty: " << s.empty() << "\n";
    s.push(8);
    s.push(9);
    cout << "full: " << s.full() << "\n";
    s.push(10);
    cout << "top: " << s.top() << "\n";
    cout << "full: " << s.full() << "\n";
}

void test2()
{
    Stack<int> stack;

    Stack<long, 20> stack2;

    Stack<string, 8> stack3;
}

int main()
{

    test1();
    test2();
}