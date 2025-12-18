#include <string.h>
#include <iostream>
using std::cout;

/**
 * 根据接收地对象是左值还是右值，选择不同的拷贝构造函数
 * 左值引用：只能接收左值，但是不能修改接收的左值对象
 * 右值引用：只能接收右值，因此专门负责浅拷贝赋值，通过直接修改右值来方便浅拷贝
 * const左值引用：无法区分左值和右值，因此可以专门负责深拷贝赋值(右值引用自动处理浅拷贝)
 *
 *
 * 总结：
 *      const左值引用，const不修改非临时对象内容，引用可以减少拷贝，但是不能区分左值和右值，因此只能负责深拷贝赋值
 *      右值引用，为了浅拷贝，可以修改临时对象内容，并且值接收右值，因此可以专门负责浅拷贝赋值
 *      左值引用，只能接收左值，但是缺失const，无法确保引用对象内容不会被修改，因此只能一般情况下不适用
 */

class String
{
public:
    String()
        : _str(new char[1]())
    {
        cout << "String()" << "\n";
    }

    /*带参构造函数*/
    String(const char *pstr)
        : _str(new char[strlen(pstr) + 1]())
    {
        strcpy(_str, pstr);
        cout << "String(const char *)" << "\n";
    }

    /*默认拷贝构造函数,错误，根据实际情况：
    右值只需要浅拷贝，左值需要深拷贝*/
    // String(const String &rhs)
    // :_str(rhs._str)
    // { }

    /* 拷贝构造函数：浅拷贝，非临时对象，只能将数据拷贝过来*/
    String(const String &rhs)
        : _str(new char[strlen(rhs.c_str()) + 1]()) // 分配内存
    {
        strcpy(_str, rhs.c_str()); // 拷贝数据
        cout << "String(const String &rhs)" << "\n";
    }

    /* 移动构造函数：浅拷贝，临时对象随时释放，直接将其数据移动过来*/
    String(String &&rhs)
        : _str(rhs._str) // 浅拷贝
    {
        rhs._str = nullptr; // 防止内存泄漏
        cout << "String(String &&rhs)" << "\n";
    }

    /* 拷贝赋值运算符：深拷贝，非临时对象，只能将数据拷贝过来*/
    String &operator=(const String &rhs)
    {
        if (this != &rhs) // 防止自赋值
        {
            delete[] _str;                              // 释放内存
            _str = new char[strlen(rhs.c_str()) + 1](); // 分配内存
            strcpy(_str, rhs.c_str());                  // 赋值
        }
        cout << "operator=(const String &rhs)" << "\n";
        return *this;
    }

    /* 移动赋值运算符：浅拷贝，临时对象，直接将其数据移动过来*/
    String &operator=(String &&rhs)
    {
        if (this != &rhs) // 防止自赋值
        {
            delete[] _str;      // 释放内存
            _str = rhs._str;    // 赋值
            rhs._str = nullptr; // 置空
        }
        cout << "operator=(String &&rhs)" << "\n";
        return *this;
    }

    const char *c_str() const
    {
        return _str;
    }

    /* 析构函数*/
    ~String()
    {
        if (_str)
        {
            delete[] _str;
            _str = nullptr;
        }
        cout << "~String()" << "\n";
    }

    void print()
    {
        cout << _str << "\n";
    }

    const size_t length() const
    {
        return strlen(_str);
    }

private:
    char *_str;
};

void test1()
{
    String s1 = "hello world";
    String s2(s1);
    String s3("hello world");
    s3 = String("hello world");
    s2 = s3;
    String("hello world") = String("hello world");
}

void test2()
{
    String s1;                // 默认构造函数
    String s2("hello world"); // 带参构造函数
    String s3(s2);            // 拷贝构造函数
    String s4(std::move(s2)); // 移动构造函数
    s4 = s3;                  // 拷贝赋值构造函数
    s4 = std::move(s3);       // 移动赋值构造函数
}

int main()
{
    test2();
}
