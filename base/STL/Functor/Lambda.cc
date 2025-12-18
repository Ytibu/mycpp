#include <iostream>
using std::cout;

/**
 * lambda表达式
 */

void test(){

    //[]参数捕获列表
    //()函数的参数列表
    //{}函数体本身
    []()->void{cout<<"hello world"<<std::endl;}();
    [](int a, int b)->int{
        return a + b;
    }(1, 2);

    int a = 100;
    [a](){cout << a << std::endl;}();

    [a]()mutable{   //mutable 修饰捕获的变量，可修改，但是捕获的是拷贝的值
        ++a;
        cout << a << std::endl;
    }();

    cout << a << std::endl;

    [&a](){   //&a 捕获a的引用
        ++a;
        cout << a << std::endl;
    }();

    cout << a << std::endl;

}

void test1(){

    [](const std::string &name){
        cout << "hello " << name << std::endl;
    }("world");

    auto f = [](const std::string &name){
        cout << "hello " << name << std::endl;
    };
    f("world");

    typedef void (*funcc)(const std::string &);
    using func = void(const std::string &);

    funcc f1 = [](const std::string &name){
        cout << "hello " << name << std::endl;
    };
    f1("world");

}

void test2(){
	int num = 10;
	std::string name = "world";
	int age = 18;

	[num, name](const std::string &value){
		cout << "num: " << num << " name " << name << " value: " << value << std::endl;
	}("hello");

	[&num, &name](const std::string &value){
		name = "wuhan";
		cout << "++num: " << ++num << " name to wuhan: " << name << " value: " << value << std::endl;
	}("hello");

	[&num, &name, age](const std::string &value){
		name = "wuhan";
		cout << "++num: " << ++num << " name to wuhan: " << name << " age: " << age << " value: " << value << std::endl;
	}("hello");

	[=, &age](const std::string &value){//age引用传递，=表示其他变量值传递
		age = 23;
		cout << "num: " << num << " name: " << name << " age: " << age << " value: " << value << std::endl;
	}("hello");

	[&,age](const std::string &value){//age值传递，&表示其他变量引用传递
		name = "wuhan1";
		cout << "num: " << num << " name: " << name << " age: " << age << " value: " << value << std::endl;
	}("hello");

	cout << "num: " << num << " name: " << name << " age: " << age << std::endl;

}

int main(){
    test();
    test1();
	test2();
    return 0;
}