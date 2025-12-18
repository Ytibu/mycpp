#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::ostream_iterator;
using std::istream_iterator;
using std::copy;

/**
 * 流迭代器：输出流迭代器 ostream_iterator，输入流迭代器 istream_iterator 
 *      可以实现流输出和流输入操作
 */

void test()
{
    vector<int> vec{1, 2, 3, 4, 5};
    ostream_iterator<int> osi(cout, "\n");

    copy(vec.begin(), vec.end(), osi);  // 输出
}

void test1()
{
    vector<int> vec;
    istream_iterator<int> isi(cin);

    copy(isi, istream_iterator<int>(), vec.begin());
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

}

int main()
{
    test(); 
    test1();
}