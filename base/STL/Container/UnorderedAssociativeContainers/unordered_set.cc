#include <unordered_set>
#include <iostream>
#include <cmath>
using std::cout;
using std::unordered_set;

/**
 * 无序关联式容器：unordered_set
 * 底层实现：哈希表
 * 特点：
 *      Key值无序，Key值唯一
 */


template<typename Container>
void display(Container const &c) {
    for (auto const &elem : c) {
        cout << elem << " ";
    }cout << "\n";
} 


void test() {
    unordered_set<int> s1 {3,4,5,8,3,4,9,8,1,2};
    display(s1);
}


/*容量*/
void test1(){
    unordered_set<int> s1 {3,4,5,8,3,4,9,8,1,2};
    cout << "s1.size() = " << s1.size() << "\n";
    cout << "s1.empty() = " << s1.empty() << "\n";
    cout << "s1.max_size() = " << s1.max_size() << "\n";
}

/*修改器*/
void test2(){

}

/*查找*/
void test3(){
    unordered_set<int> s1 {3,4,5,8,3,4,9,8,1,2};
    auto ret = s1.find(3);
    auto ret1 = s1.count(3);
}

int main() {
    test(); 
    test1();
    test2();
    test3();
}