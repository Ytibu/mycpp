#include <iostream>
#include <set>
using std::cout;
using std::set;
using std::pair;
/**
 * 关联式容器：set的使用
 * 特点：
 *      1. 集合中的存放的是key类型，key值是唯一的，不能重复
 *      2. 集合中的元素是无序的，不能通过索引访问元素
 *      3. 底层使用的是红黑树_Rb_tree，不支持修改元素内容
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

    set<std::string> a;                                         // (1) Default constructor
    set<std::string> b{"one", "two", "three", "five", "eight"}; // (2) Initializer list constructor
    set<std::string> c(b.begin(), b.end());                     // (3) Iterator constructor
    set<std::string> d(c);                                      // (4) Copy constructor
    set<std::string> e(std::move(b));                           // (5) Move constructor

    display(e);
}


/*容量Capacity*/
void test1()
{
    set<int> s{5, 3, 7, 6, 1, 2, 4, 8, 9, 0};

    cout << "s.size() = " << s.size() << "\n";
    cout << "s.empty() = " << s.empty() << "\n";
    cout << "s.max_size() = " << s.max_size() << "\n";
}


/*修改器Modifiers*/
void test2()
{
    set<int> s = {5, 3, 7, 6, 1, 2, 4, 8, 9, 0};

    
    pair<set<int>::iterator, bool> ret = s.insert(10);   //在容器中增加一个元素
    s.insert(s.begin(), 11);    //指定位置插入元素(如果正确使用，不正确则系统会调整)
    s.insert({12, 13}); //插入初始化列表中的元素(无返回值)
    set<int> s2 = {14, 15, 16};
    s.insert(s2.begin(), s2.end()); //插入迭代器范围的元素(无返回值)
    display(s);

    //emplace()和emplace_hint()都是插入元素，但是不调用拷贝构造，性能高
    pair<set<int>::iterator,bool> re = s.emplace(17);  //插入元素
    s.emplace_hint(s.begin(), -1);  //插入元素(返回实际插入位置的迭代器)
    display(s);

    s.erase(5); //删除指定的元素
    s.erase(s.begin()); //删除指定位置的元素，s.end()不是有效范围，不能指定s.end
    s.erase(s.begin(), s.end());    //删除指定区间的元素
    display(s);


    set<int> s3 {1, 2, 3, 4, 5};
    s.swap(s3); // 交换
    s.clear();  // 清空
}


/*查找Lookup*/
void test3()
{
    set<int> s = {5, 3, 7, 6, 1, 2, 4, 8, 9, 0};
    size_t count = s.count(5); // 统计元素个数，不存在返回0
    auto it = s.find(5);       // 查找元素，返回迭代器,不能存在返回s.end()迭代器

    set<int>::iterator it1 = s.lower_bound(5);    // 返回第一个not less(大于等于)指定元素的迭代器
    set<int>::iterator it2 = s.upper_bound(8);    // 返回第一个大于指定元素的迭代器
    // 返回指定元素的迭代器范围(在multiset中使用最佳)
    pair<set<int>::iterator, set<int>::iterator> ret = s.equal_range(5);
}

int main()
{

    test();
    test1();
    test2();
    test3();
}