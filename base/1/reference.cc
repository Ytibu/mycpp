#include <iostream>
using std::cout;

/**
 * 引用的使用
 *      引用必须进行初始化，初始化之后这个绑定是永久的
 *      引用对象的值可以改变，引用的值修改后，引用指向的变量的值也会改变
 *      引用的地址就是被引用对象的地址
 * 引用是被显示的指针，但是编译器对引用进行了超级保护，会阻止任何形式的对引用直接的修改和访问
 * 引用本质上是间接寻址的被保护的指针，占据和指针一样的空间
 */


void test(){

    int num = 100;  //先定义一个变量
    int &ref = num; //后使用引用绑定变量
    cout << "num = " << num << " ref = " << ref << "\n";

    int num2 = 200;
    ref = num2; //此方法可以修改引用的值即ref引用num的值可以改变
    cout << "num = " << num << " ref = " << ref << "\n";
    cout << "num2 = " << num2 << " ref = " << ref << "\n";
    cout << "&num = " << &num << " &ref = " << &ref << "\n";
    cout << "&num2 = " << &num2 << " &ref = " << &ref << "\n";

}



/*直接交换数值，不改变实参的内容*/
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}
/*通过指针交换数值，改变实参的内容*/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
/*通过引用交换数值，改变实参的内容*/
void swap1(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}//swap(int a, int b)与swap(int &a, int &b)无法进行函数重载

/*引用作为函数参数*/
void test1() {
    int a = 10;
    int b = 20;
    int &ref1 = a;
    int &ref2 = b;

    cout << "swap(int a, int b) before: a = " << a << " b = " << b << "\n";
    swap(a, b);
    cout << "swap(int a, int b) after: a = " << a << " b = " << b << "\n";

    cout << "swap(int *a, int *b) before: a = " << a << " b = " << b << "\n";
    swap(&a, &b);
    cout << "swap(int *a, int *b) after: a = " << a << " b = " << b << "\n";

    cout << "swap1(int &a, int &b) before: a = " << a << " b = " << b << "\n";
    swap1(ref1, ref2);
    cout << "swap(int &a, int &b) after: a = " << a << " b = " << b << "\n";
}



int arr[5] = {1, 2, 3, 4, 5};
// !!!! 当变量的生存周期小于函数的生命周期，此用法问题极大
int &put(){
    int number = 3;
    return arr[number];
}
int &puts(){
// ！！！在函数内部开辟堆空间，需要在函数外注意堆空间的释放
    int *number = new int(10);
    return *number;
}
int puts2(){
    int *number = new int(10);
    int value = *number;    //返回的副本
    delete number; //释放堆空间
    number = nullptr;
    return value;   //实际返回的是一个临时对象(堆空间的副本位于栈上)
}
/*引用作为函数返回值*/
void test2(){
    int &number = put();  //如果返回的值域在函数内部，函数返回后，变量number就失效了
    cout << "number = " << number << "\n";
    int &number2 = puts();  //接受堆空间的引用
    cout << "number2 = " << number2 << "\n";

    //int &number3 = puts2();   //无法直接接收一个返回的临时对象
    const int &number3 = puts2();   //const可以延长临时对象的生命周期
    cout << "number3 = " << number3 << "\n";

    int *ptr = &number2;    //获取引用的指针
    delete ptr; //释放堆空间
    ptr = nullptr;  //将指针置空
}


int main() {
    test();
    test1();
    test2();
}