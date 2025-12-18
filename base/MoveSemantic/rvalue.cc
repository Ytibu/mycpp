#include <iostream>
#include "String.cc"
using std::cout;

/**
 * const左值引用：绑定左值，绑定右值
 * 右值引用：绑定右值，不能绑定左值
 * 左值引用：绑定左值，不能绑定右值
 */


void test1() {
	int a = 1, b = 2;
	&a;  
	&b;
	//&(a + b);//error，右值,匿名变量
	//&10;//右值
	//&String("hello");//匿名对象
    
    String("hello").print();
    
    //非const引用尝试绑定
	int & r1 = a;
	//int & r2 = 1;//非const引用不能绑定右值
    
    //const引用尝试绑定
    //conts引用可以绑定右值
	const int & r3 = 1;
	const int & r4 = a;
    
	String s1("hello");
	String s2("wangdao");
	&s1;
	&s2;

    //右值引用
    //只能绑定右值，不能绑定左值
    /* int && ref = a; */
    int && ref2 = 1;
}

int &&func(){
	return 1;
}

/*右值引用的性质*/
void test1(void){

	/*匿名的右值引用，等同于右值*/
	//&func();

	/*有名的右值引用，等同于左值*/
	int && ref = func();
}
int main(void){
    test1();
    return 0;
}