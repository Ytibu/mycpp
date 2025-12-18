#include <iostream>
using std::cout;
using std::endl;

/**
 * public: 谁都可以访问,子类可以继承，类外可以访问，子类外可以访问
 * private: 仅自己可以访问()，友元可以访问，
 * protected: 仅自己和子类可以访问，友元可以访问
*/

class MyClass {
public:
    int a;
    int b;
    MyClass() { cout << "Constructor called" << endl; }
    ~MyClass() { cout << "Destructor called" << endl; }
    void print() { cout << "print() called" << endl; }
private:
    int a1;
    int b1;
    void print1() { cout << "print1() called" << endl; }
protected:
    int a2;
    int b2;
    void print2() { cout << "print2() called" << endl; }
};

class MySubClass1 : private MyClass {
public:
    int a;
    int b;
    MySubClass1() { cout << "Constructor1 called" << endl; }
    ~MySubClass1() { cout << "Destructor1 called" << endl; }
    void print() { cout << "print() called" << endl; }
// private:
    int a1;
    int b1;
    void print1() { cout << "print1() called" << endl; }
public:
    int a2;
    int b2;
    void print2() { cout << "print2() called" << endl; }
};

class MySubClass2 : protected MyClass {
public:
    int a;
    int b;
    MySubClass2() { cout << "Constructor1 called" << endl; }
    ~MySubClass2() { cout << "Destructor1 called" << endl; }
    void print() { cout << "print() called" << endl; }
private:
    int a1;
    int b1;
    void print1() { cout << "print1() called" << endl; }
public:
    int a2;
    int b2;
    void print2() { cout << "print2() called" << endl; }
};


void test(){
    MyClass a;
    MySubClass1 b;
    MySubClass2 c;
    a.print();
    //a.print1();
    //a.print2();

    b.print();
    //b.print1();
    b.print2();

    c.print();
    //c.print1();
    c.print2();

    
}
int main() {
  test();
  return 0;
}