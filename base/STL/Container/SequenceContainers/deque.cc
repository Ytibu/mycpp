#include <iostream>
#include <deque>
using std::cout;
using std::endl;
using std::deque;

/**
 * 序列式容器deque的使用
 *      1.实现原理：利用中控器控制空间，分成几个片段，每个片段的元素存储在连续空间中，空间大小可变
 */


/*deque容器的创建*/
void test1(){
    deque<int> v1; //创建空对象
    deque<int> v2(v1);  //拷贝构造
    deque<int> v3(10,3);   //创建10个3的deque对象
    deque<int> v4(10); //创建10个0的deque对象（默认值）

    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    deque<int> v5(arr,arr+10);  //利用迭代器范围创建deque对象(左闭右开)
    deque<int> v6 = {1,2,3,4,5,6,7,8,9,10};    //利用参数化列表创建deque对象

}

/*元素遍历*/
void test2(){

    deque<int> v = {1,2,3,4,5,6,7,8,9,10};

    /*利用下标索引*/
    for(size_t i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }cout << "\n";

    /*利用迭代器*/
    for(deque<int>::iterator it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }cout << "\n";

    /*增强for循环，引用输出*/
    for(auto &item: v){
        cout << item << " ";
    }cout << "\n";

}

template<typename T>
void display(T &container){
    for(auto &item: container){
        cout << item << " ";
    }cout << "\n";
}


/*元素访问Element Access*/
void test4(){

    deque<int> v = {1,2,3,4,5,6,7,8,9,10};
    
    v.at(2) = 0;    //at()函数会会检查是否越界(访问位置没有数据)访问越界会抛出异常
    v[1] = 0;   //通过下标访问，没有访问越界检查
    display(v);

    v.front() = 0;  //访问第一个元素
    v.back() = 0;   //访问最后一个元素
    display(v);

}


/*容量Capacity*/
void test3(){

    deque<int> v = {1,2,3,4,5,6,7,8,9,10};
    cout << "empty: " << v.empty() << endl;
    cout << "size: " << v.size() << endl;
    cout << "max_size: " << v.max_size() << endl;
    v.shrink_to_fit();  // 释放多余空间(容量等于元素个数)

}



/*修改器Modifiers*/
void test5(){

    deque<int> v = {1,2,3,4,5,6,7,8,9,10};

    v.push_back(11);    //尾部添加元素
    v.pop_back();   //删除尾部元素
    display(v);

    v.push_front(0);    //头部添加元素
    v.pop_front();  //删除头部元素
    display(v);


    v.insert(v.begin(),-1);  //在指定位置插入元素
    display(v);
    deque<int> d = {11,12,13,14,15};
    v.insert(v.begin(),d.begin(),d.end());    //在指定位置插入迭代器范围的元素
    display(v);
    v.insert(v.end(),{11,12,13,14,15}); //利用参数化列表插入元素
    display(v);


    /*删除元素,注意迭代器的指向会随着容器的空间变化而改变*/
    deque<int> v2 = {1,2,3,4,5,6,7,8,9,10};
    auto it = v2.begin();
    v2.erase(it);    //删除指定位置的元素
    v2.erase(it,it+5);   //删除指定区间的元素
    display(v2);


    v.emplace_back(11); //效率高于push_back，不会调用拷贝构造函数（如果为对象）
    v.emplace_front(10);    //效率高于push_front
    v.emplace(v.begin(),12);
    display(v);

    
    v.resize(5);    //改变vector的元素个数为5,用默认值填充
    v.resize(10,1); //改变vector的元素个数为10,用指定值填充
    
    swap(v,v2); //交换两个deque
    v.clear();  //清空deque

}



// deque how to use it
int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
