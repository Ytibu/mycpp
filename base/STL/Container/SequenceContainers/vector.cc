#include <iostream>
#include <vector>
using std::cout;
using std::vector;

/**
 * 序列式容器vector的使用
 *      1.实现原理：动态数组，利用在栈空间三个指针操作堆空间的数据(begin,end,capacity)
 *      2.空间内存：start指针固定，finish指针可变，endofStorage指针可变(通过finish和endofStorage来改变实际空间)
 *      3.容器特点：相当于一个单向开口的队列,头部增加元素的时间复杂度：O(1)，空间复杂度：O(n)
 *      4.开辟空间：容量不足以容纳新的元素时，会自动扩容，会放弃旧有空间，开辟新的地址作为新空间
 */


/*Vector容器的创建Constructs*/
void test1(){
    vector<int> v1; //创建空对象
    vector<int> v2(v1); //拷贝构造
    vector<int> v3(10,3);   //创建10个3的vector对象
    vector<int> v4(10); //创建10个0的vector对象（默认值）


    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> v5(arr,arr+10);  //利用迭代器范围创建vector对象(左闭右开)
    vector<int> v6 = {1,2,3,4,5,6,7,8,9,10};    //利用参数化列表创建vector对象

}

/*元素遍历*/
void test2(){

    vector<int> v = {1,2,3,4,5,6,7,8,9,10};

    /*利用下标索引*/
    for(size_t i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }cout << "\n";

    /*利用迭代器*/
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }cout << "\n";

    /*增强for循环，引用输出*/
    for(auto &item: v){
        cout << item << " ";
    }cout << "\n";

}

template<typename Container>
void display(Container &v){
    for(auto &item: v){
        cout << item << " ";
    }cout << "\n";
}


/*元素访问ElementAccess*/
void test4(){

    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    
    v.at(2) = 0;    //at()函数会会检查是否越界(访问位置没有数据)访问越界会抛出异常
    v[1] = 0;   //通过下标访问，没有访问越界检查
    display(v);

    v.front() = 0;  //访问第一个元素
    v.back() = 0;   //访问最后一个元素
    display(v);
    
    data(v);    //指向底层元素存储的指针。对于非空容器，返回的指针与首元素地址比较相等
}


/*容量Capacity*/
void test3(){
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    cout << "empty: " << v.empty() << "\n";
    cout << "size: " << v.size() << "\n";
    cout << "capacity: " << v.capacity() << "\n";
    cout << "max_size: " << v.max_size() << "\n";
    
    v.resize(20);   //改变vector的容量为20
    v.shrink_to_fit();  //将容器的容量缩小为当前元素个数（容器不存在空余空间）
}



/*修改器Modifiers*/
void test5(){

    vector<int> v1 = {1,2,3,4,5,6,7,8,9,10};

    /*插入元素：v.insert()*/
    auto it = v1.begin();
    v1.insert(it,0);  //指定位置插入元素
    //v.insert(it,2,0);    //指定位置插入2个元素0
    vector<int> v = {-3,-2,-1};
    v1.insert(it,v.begin(),v.end());   //指定位置插入，迭代器范围元素
    v1.insert(it,{-7,-6,-5,-4});    //指定位置插入，参数化列表元素
    display(v1);


    vector<int> v2 = {1,2,3,4,5,6,7,8,9,10};

    /*删除元素v.erase()*/
    auto it2 = v2.begin();
    v2.erase(it2);  //删除指定位置元素
    v2.erase(it2,it2+3);   //删除指定范围元素（左闭右开）
    display(v2);


    display(v);
    v.push_back(11);    //尾部添加元素
    v.pop_back();   //删除尾部元素
    display(v);
    /*vector无法进行直接的头部操作：push_front()，pop_front()*/

    v.emplace(v.begin(),12);    //不会调用拷贝构造(元素为对象)
    v.emplace_back(11); //效率高于push_back，不会调用拷贝构造函数（如果为对象）
    display(v);


    v.resize(5);    //改变vector的元素个数为5,用默认值填充
    v.resize(10,1); //改变vector的元素个数为10,用指定值填充
    display(v);

    swap(v1,v2); //交换两个vector对象
    v.clear();  //删除所有元素
    
}

// vector how to use it
int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
