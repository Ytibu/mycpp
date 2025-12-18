#include <iostream>
using std::cout;

/**
 * 指针各种形式
 */

/*数组指针*/
void test1(){
    int arr[5] = {1,2,3,4,5};   //int数组
    int (*p)[5] = &arr; //数组指针,p解引用后指向一个包含5个int元素的数组
    for (size_t i = 0; i < 5; i++)
    {
        //(*p)[i]表示p指向的数组的第i个元素,arr[i]表示数组的第i个元素
        cout << "pointer ->" << (*p)[i] << " array ->" << arr[i] << "\n";
    }
    
}

/*指针数组*/
void test2(){
    int arr[5] = {1,2,3};   //数组
    int *p1 = &arr[0];  //每个指针指向数组中的元素
    int *p2 = &arr[1];
    int *p3 = &arr[2];
    int *p[3] = {p1,p2,p3}; //指针数组：每个元素都是一个指向数组元素的指针
    for (size_t i = 0; i < 3; i++)
    {
        // *p[i]表示指针数组的第i个元素的解引用，即指针数组的第i个元素所指向的元素
        //arr[i]表示int数组的第i个元素
        cout << "pointer ->" << *p[i] << " array ->" << arr[i] << "\n";
    }
}



int add(int a,int b){
    return a+b;
}/*函数指针*/
void test3(){
    int (*p)(int,int) = &add;
    cout << "add(1,2)=" << (*p)(1,2) << "\n";

    int (*p2)(int,int) = add;
    cout << "add(1,2)=" << p2(1,2) << "\n";

}

int Number = 100;
int *print(){
    int *p = &Number;
    return p;   //返回值为指针类型
}/*指针函数*/
void test4(){
    int num = 100;
    int *p = print();   //函数返回值为指针类型
    //输出p解引用后的值(返回值为指针类型，解引用即指针指向数据的数值)
    cout << "print(100)=" << *p << "\n";
}

int main()
{ 
    test1();
    test2();
    test3();
    test4();
}