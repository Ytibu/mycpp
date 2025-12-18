#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <memory>

using std::cout;
using std::vector;
using std::ostream_iterator;


/**
 * 算法，定义于<algorithm>
 * 分类：   
 *      非修改序列操作：Non-modifying sequence operations
 *      修改序列操作：Modifying sequence operations
 *      分区操作：Partitioning operations
 *      排序操作：Sorting operations
 *      二分搜索操作：Binary search operations (on sorted ranges)
 *      集合操作：Set operations (on sorted ranges)
 *      合并操作：Merging operations(Other operations on sorted ranges)
 *      堆操作：Heap operations
 *      最值操作：Minimum/maximum operations
 *      比较操作：Comparison operations
 *      排列操作：Permutation operations
 *      数值操作：Numeric operations
 *      memory操作：Operations on uninitialized memory
 */


void func(int &value){
    cout << value << " ";
}

struct Number{
    Number(int number):number_(number){}

    void print(){
        cout << number_ << " ";
    }
    int number_;
};


void test(){

    vector<int> v{1,2,3,4,5,6,7,8,9,10};

    std::for_each(v.begin(),v.end(),func);  //遍历进行函数对象的调用，函数对象内定义的操作
    cout << "\n";

    std::for_each(v.begin(),v.end(),[](int &value){cout << value << " ";});
    cout << "\n";

}

void test1(){

    vector<int> vec{1,2,3,4,5,6,7,8,9,10};
    
    //remove_if()为了实现通用性，会将容器中所有不满足lambda表达式的元素移动到容器的末尾，并返回指向末尾的迭代器
    auto it = std::remove_if(vec.begin(),vec.end(),[](int &value){return value > 5;});  
    vec.erase(it,vec.end());
    //返回的迭代器是满足条件的元素的起始点，将此起始点到末尾的元素全部删除，利用erase()删除迭代器范围的元素

    std::for_each(vec.begin(),vec.end(),[](int &value){cout << value << " ";});
    cout << "\n";

}

/*传递成员函数*/
void test2(){
    vector<Number> vec;
    for(int i = 0; i < 10; ++i){
        vec.push_back(Number(i));
    }

    std::for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print));
    cout << "\n";
}

int main(){
    
    test();
    test1();
    test2();
    return 0;
}