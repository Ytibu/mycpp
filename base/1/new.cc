#include <iostream>
using std::cout;


/**
 * 堆空间的内存分配释放：
 *      new/delete与malloc/free的使用区别
 *      new[]/delete[]与new/delete的使用区别
 * valalgrind泄漏检测工具的使用
 *      valgrind --tool=memcheck ./程序名
 */


/*堆空间申请空间*/
void test(){
    int *p = (int *)malloc(sizeof(int));    //malloc申请空间时无法直接初始化
    *p = 10;
    cout << *p << "\n";
    free(p);

    int *p1 = new int;  //此表达方式不会初始化，会使用系统的脏数据
    cout << *p1 << "\n";

    int *p2 = new int();  //初始化使用默认值(即为0)，会使用0
    cout << *p2 << "\n";

    int *p3 = new int(10);  //初始化使用指定的值，会使用指定的值
    cout << *p3 << "\n";

    delete p1;  //必须进行释放否则可能会泄漏内存
    delete p2;
    delete p3;

    //预防释放空间的指针变成野指针，使用空指针可以避免野指针
    p = nullptr;
    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;
}

/*堆空间申请数组空间:new [] / delete []*/
void test1(){

    int *p = new int[3](); //初始化使用默认值(即为0)申请一个int数组空间
    for(int i = 0; i < 3; i++){
        cout << p[i] << " ";
    }cout << "\n";


    int *p1 = new int[3]{1,2,3};    //初始化使用指定的值，使用初始化列表直接初始化数组
    for(int i = 0; i < 3; i++){
        cout << p1[i] << " ";
    }cout << "\n";

    //int *p2 = new int[3](10);
    int *p2 = new int[3]{10,10,10};
    //申请数组空间时只能使用以上两种方法，不能在()内添加指定的初始化值，必须使用初始化列表
    for(int i = 0; i < 3; i++){
        cout << p2[i] << " ";
    }cout << "\n";
    

    delete[] p; //使用数组空间的申请方式，就得使用数组空间的释放方式
    delete[] p1;    //释放数组空间

    p = nullptr;    //野指针的避免
    p1 = nullptr;
    
}

int main(){
    test();
    test1();
}
