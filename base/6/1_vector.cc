#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 动态数组：vector的底层实现原理
 *  1. vector底层实现原理：数组 + 容量 + 大小
 *  2. vector扩展方式：@1开辟新空间，@2拷贝到新空间，@3释放旧空间，@4将新数据加入末尾
 *  3. vector存储方式：对象本身存储在栈上，数据存储在堆上，通过对象访问堆上的数据，利用三个指针操作堆上的数据
 */

 /*迭代输出方式*/
void test(){

    vector<int> v = {1,2,3,4,5};

    /*迭代器指针解引用*/
    for(auto it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }cout << endl;

    /*引用*/
    for(auto &e: v){
        cout << e << " ";
    }cout << endl;

    /*下标访问*/
    for(size_t i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }cout << endl;

}


void printVector(vector<int> &v){
    for(auto &e: v){
        cout << e << " ";
    }cout << endl;
}

/*容量函数*/
void test1(){

    vector<int> v(10);  //创建一个容量为10的vector
    v = {1,2,3,4,5};
    v.reserve(7);  //重新指定容量为7(capacity==7)

    cout << "v.empty() = " << v.empty() << endl;    //是否为空
    cout << "v.size() = " << v.size() << endl;  //元素个数
    cout << "v.capacity() = " << v.capacity() << endl;  //容量

    v.shrink_to_fit();  //根据真实的元素个数，释放多余空间(结果size==capacity)

    printVector(v);
    
}

/*修改函数*/
void test2(){

    vector<int> v = {1,2,3,4,5};
    printVector(v);

    v.pop_back();   //删除末尾元素
    printVector(v);

    v.push_back(5); //末尾添加元素
    printVector(v);

    cout << "firtst = " << v.front() << endl;   //获取第一个元素
    cout << "last = " << v.back() << endl;  //获取最后一个元素

    v.clear();  //清空

    printVector(v);

}

int main(){

    test();
    test1();
    test2();

}