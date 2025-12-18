#include <iostream>
#include <map>
#include <string>
#include <utility>
using std::cout;
using std::make_pair;
using std::map;
using std::pair;
using std::string;

/**关联式容器：map
 *      map是一种关联式容器，它将键值对存储在树形结构中，键值对中的键必须唯一，默认键升序排列
 *
 */


map<int, string> number{
    {1, "one"},
    {2, "two"},
    {3, "three"},
    pair<int, string>(4, "four"),
    pair<int, string>(5, "five"),
    pair<int, string>(6, "six"),
    make_pair(7, "seven"),
    make_pair(8, "eight"),
    make_pair(9, "nine"),
};


template <typename Container>
void display(const Container &c)
{
    for (auto &elem : c)
        cout << elem.first << ": " << elem.second << " ";
    cout << "\n";
}


void test()
{

    display(number);
}


/*元素访问Element access*/
void test1()
{
    number[8] = "eight1";   // 无越界检查
    number.at(9) = "nine1"; // 越界检查
    display(number);
}


/*容量Capacity*/
void test2()
{
    cout << "size: " << number.size() << "\n";
    cout << "empty: " << number.empty() << "\n";
    cout << "max_size: " << number.max_size() << "\n";
}


/*修改器Modifiers*/
void test3()
{
    /*insert插入*/
    pair<map<int, string>::iterator, bool> ret = number.insert({10, "ten"});

    /*erase删除*/
    number.erase(10);                           // 删除指定key的元素
    number.erase(number.begin());               // 删除指定迭代器的元素
    number.erase(number.begin(), number.end()); // 删除指定区间的元素
}


/*查找Lookup*/
void test4()
{
    auto it = number.find(5);     // 查找元素，返回迭代器，不存在返回end()
    size_t it1 = number.count(1); // 查找元素个数,不存在返回0
}

int main()
{
    test();
    test1();
    test2();
    test3();
    test4();
}