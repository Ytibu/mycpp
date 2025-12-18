#include <iostream>
#include <queue>
#include <vector>
using std::priority_queue;
using std::cout;
using std::vector;

/*构造函数*/
void test(){
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    priority_queue<int> pq(v.begin(), v.end());
    priority_queue<int> pq1(pq);
    priority_queue<int> pq2(std::less<int>(),v);
}

/*元素访问，容量*/
void test1(){
    vector<int> v = {5,3,7,8,4,1,2,6,9,10};
    priority_queue<int> pq(v.begin(), v.end());
    
    cout << "pq.top(): " << pq.top() << "\n";   //返回队列中优先级最高的元素

    cout << "pq.size(): " << pq.size() << "\n"; //返回队列中元素个数
    cout << "pq.empty(): " << pq.empty() << "\n";   //判断是否为空
}

/*修改器*/
void test2(){ 
    vector<int> v = {5,3,7,8,4,1,2,6,9,10};
    priority_queue<int> pq(v.begin(), v.end());

    pq.pop();   //弹出队列中优先级最高元素
    cout << "pq.top(): " << pq.top() << "\n";

    pq.push(11);    //向队列中添加元素并排序
    cout << "pq.top(): " << pq.top() << "\n";
}

int main(){
    test();
    test1();
    test2();
    return 0;
}