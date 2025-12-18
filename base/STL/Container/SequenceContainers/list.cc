#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::list;

/**
 * 序列式容器list的使用
 *      1.实现原理：数组，利用在栈空间三个指针操作堆空间的数据(begin,end,capacity)
 */



/*list容器的创建*/
void test1(){
    list<int> v1; //创建空对象
    list<int> v2(v1);   //拷贝构造
    list<int> v3(10,3);   //创建10个3的list对象
    list<int> v4(10); //创建10个0的list对象（默认值）

    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    list<int> v5(arr,arr+10);  //利用迭代器范围创建list对象(左闭右开)
    list<int> v6 = {1,2,3,4,5,6,7,8,9,10};    //利用参数化列表创建list对象

}


/*元素遍历*/
void test2(){

    list<int> v = {1,2,3,4,5,6,7,8,9,10};

    /*list不支持下标索引： list[index] */

    /*利用迭代器*/
    for(list<int>::iterator it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }cout << "\n";

    /*增强for循环，引用输出*/
    for(auto &item: v){
        cout << item << " ";
    }cout << "\n";

}

template<typename Container>
void display(Container &container){
    for(auto &item: container){
        cout << item << " ";
    }cout << "\n";
}


/*元素访问Element access*/
void test4(){
    list<int> v = {1,2,3,4,5,6,7,8,9,10};
    v.front() = 0 ;
    v.back() = 11;
}


/*容量Capacity*/
void test3(){
    list<int> v = {1,2,3,4,5,6,7,8,9,10};
    cout << "v.empty()："  << v.empty() << endl;
    cout << "v.size()：" << v.size() << endl;
    cout << "v.max_size()：" << v.max_size() << endl;
}



/*修改器Modifiers*/
void test5(){

    list<int> v = {1,2,3,4,5,6,7,8,9,10};
    display(v);
    v.push_back(11);    //尾部添加元素
    v.pop_back();   //删除尾部元素
    display(v);

    v.push_front(0);    //头部添加元素
    v.pop_front();  //删除头部元素
    display(v);

    v.insert(v.begin(),-1); //指定位置插入元素
    display(v);
    v.insert(v.end(),5,11); //指定位置插入指定数量的元素
    display(v);

    /*插入元素*/
    list<int> v1 = {11,12,13,14,15};
    v1.insert(v.begin(),v1.begin(),v1.end());    //指定位置插入指定区间的元素
    v1.insert(v.end(),{16,17,18,19,20});  //指定位置插入参数化列表元素


    /*修改元素*/
    v.erase(v.begin()); //删除第一个元素
    v.erase(v.begin(),v.end()); //删除指定区间的元素

    v.emplace(v.begin(),-1);
    v.emplace_front(-2);
    v.emplace_back(16);
    display(v);

    v.resize(5);    //改变vector的元素个数为5,用默认值填充
    v.resize(10,1); //改变vector的元素个数为10,用指定值填充
    
    swap(v,v1); //交换两个list对象

    v.clear();  //清空元素

}

struct CompareList{
    bool operator()(const int &lhs, const int &rhs) const{
        return lhs < rhs;
    }
};


/*list的一些操作函数Operations*/
void test6(){

    list<int> l = {1,2,3,4,5,6,7,8,9,10,1,1};

    l.sort();
    l.unique(); //元素去重(只会去除连续的重复元素，需要先排序，确保重复元素持续)
    display(l);

    l.reverse();    //元素顺序翻转
    display(l);

    l.sort();   //元素排序(默认由小到大)
    l.sort(CompareList());  //自定义排序方式
    l.sort(std::less());
    l.sort(std::greater());
    display(l);

    list<int> l2 = {9,12,20,18,16};
    //l.merge(l2);    
    //直接merge会进行简单的拼接，merge后排序，也只会是各自部分的排序，达不到总体排序
    //各自先排序，后merge
    l.sort();
    l2.sort();
    l.merge(l2);
    display(l);

    list<int> l3 = {11,12,13,14,15};
    //l.splice(l.begin(),l3); //将另一个list对象所有元素移动到指定位置之前
    l.splice(l.begin(),l3,--(l3.end()));    //将另一个list对象的一个元素移动到指定位置之前
    //l.splice(l.end(),l3,l3.begin(),l3.end());   //将另一个list对象迭代器范围的元素移动到指定位置之前 
    display(l);
}



// list how to use it
int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}
