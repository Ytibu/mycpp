#include <iostream>
#include <cstring>
using std::cout;

class Student {
public:
    Student(): _age(0), _name(nullptr)   // 构造函数
    {
        cout << "Student()" << "\n";
    }


    /*构造函数
    注意：深浅拷贝问题
    */
    Student(int age, char *name)    // 构造函数
    :_age(age),_name(new char[strlen(name) + 1]())
    {
        strcpy(_name,name);
        cout << "Student(int,char *)" << "\n";
    }


    /* 拷贝构造函数
    拷贝构造函数，参数是源对象
    const:  加const的第一个用意：为了确保右操作数的数据成员不被改变
            加const的第二个用意：为了能够复制临时对象的内容，因为非const引用不能绑定临时变量（右值）
    引用&: 必须使用，防止对象赋值给对象从而二次调用拷贝构造函数，从而无限制创建对象
    注意：    深拷贝构造，避免浅拷贝
    */
    Student (const Student &s)
    :_age(s._age),_name(new char[strlen(s._name) + 1]())
    {
        strcpy(_name,s._name);
        cout << "Student(const Student &s)" << "\n";
    }


    /* 赋值运算符重载函数,
    第一个引用&：参数为引用，确保不会二次拷贝
    第二个引用&：返回值为引用，避免二次拷贝
    const：不会修改参数对象内容
    注意：避免自引用赋值，先判断是否是同一对象，在进行深拷贝
    */
    Student &operator=(const Student &s)
    {
        if(this != &s){
            delete [] _name;    // 释放内存

            _age = s._age;
            _name = new char[strlen(s._name) + 1]();
            strcpy(_name,s._name);
        }
        
        cout << "Student &operator=(const Student &s)" << "\n";
        return *this;
    }


    /*先判断堆空间是否有分配_name，有则释放,空指针*/
    ~Student()  // 析构函数
    {
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
        cout << "~Student()" << "\n";
    }

private:
    int _age;
    char *_name;
};


int main()
{
    Student s;
    Student s1(18,"Tom");
    Student s2(s1);
    Student s3 = s1;
    Student s4(20,"Jerry");
    s4 = s1; 
}