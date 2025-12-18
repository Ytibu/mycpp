#include <iostream>
#include <set>
using std::cout;
using std::multiset;

/** 关联式容器：multiset
 *      与set的区别是multiset允许有重复元素
 */



/*元素遍历*/
template <typename Container>
void display(Container &container)
{
    for (auto &element : container){
        cout << element << " ";
    }cout << "\n";
}


/*构造函数Constructor*/
void test()
{
    multiset<std::string> a;                                         // (1) Default constructor
    multiset<std::string> b{"one", "two", "three", "five", "eight"}; // (2) Initializer list constructor
    multiset<std::string> c(b.begin(), b.end());                     // (3) Iterator constructor
    multiset<std::string> d(c);                                      // (4) Copy constructor
    multiset<std::string> e(std::move(b));                           // (5) Move constructor

    display(e);
}


/*容量Capacity*/
void test1()
{
    multiset<int> s{5, 3, 7, 6, 1, 2, 4, 8, 9, 0};

    cout << "s.size() = " << s.size() << "\n";
    cout << "s.empty() = " << s.empty() << "\n";
    cout << "s.max_size() = " << s.max_size() << "\n";
}


/*修改器Modifiers*/
void test2()
{
    multiset<int> s = {5, 3, 7, 6, 1, 2, 4, 8, 9, 0};
    s.insert(10);   // 插入一个元素
    s.insert(s.begin(), 11);    //在迭代器指向的位置插入(实际根据系统调整)
    s.insert({12, 13, 14}); //插入初始化列表
    multiset<int> s2 = {15, 16, 17, 18, 19, 20};
    s.insert(s2.begin(), s2.end()); //插入迭代器指向区间

    s.erase(11);    // 删除值为11的元素
    s.erase(s.begin()); // 删除第一个元素
    s.erase(s.begin(), s.end());    // 删除区间迭代器指向区间的元素
    display(s);

    s.emplace(11,12);
    s.emplace_hint(s.begin(), 12,13);


    multiset<int> s2;
    s.swap(s2); // 交换
    s.clear();  // 清空
}


/*查找Lookup*/
void test3()
{
    multiset<int> s = {5, 3, 7, 6, 1, 2, 4, 8, 9, 0};
    size_t count = s.count(5); // 统计元素个数，不存在返回0
    auto it = s.find(5);       // 查找元素，返回迭代器,不能存在返回s.end()迭代器

    auto it1 = s.lower_bound(5);    // 返回第一个not less指定元素的迭代器
    cout << *it1 << "\n";
    auto it2 = s.upper_bound(5);    // 返回第一个大于指定元素的迭代器
    cout << *it2 << "\n";
    std::pair<multiset<int>::iterator,multiset<int>::iterator> 
    ret = s.equal_range(5); // 返回值为5的迭代器范围(左：大于等于5；右：第一个大于5的迭代器；左闭右开)
    for(auto it = ret.first; it != ret.second; ++it)
    {
        cout << *it << " ";
    }cout << "\n";

}

int main()
{
    test();
    test1();
    test2();
    test3();
}