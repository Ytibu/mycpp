#include <string>
#include <iostream>

using std::string;
using std::cout;

/**
 * c++string库即string类的使用
 * c++string类具有高性能的特点
 */


void test(){
    string s1;  //创建一个空字符串
    const char *char1 = "hello world";
    string s2(char1);   //c风格字符串构造一个string类对象
    string s3(char1,5); //指定长度的c风格字符串构造一个string类对象
    string s4(s2);  //拷贝构造一个string类对象
    string s5(10,'a');  //创建一个指定长度的字符串，并填充指定的字符

    cout << s1 << "\n" << s2 << "\n" << s3 << "\n" << s4 << "\n" << s5 << "\n";
}

void test1(){
    string s1;
    string s2("hello world");
    cout << s1.size() << " " << s2.size() << "\n";  //获取字符串长度
    cout << s1.empty() << " " << s2.empty() << "\n";    //判断字符串是否为空
    cout << s1.length() << " " << s2.length() << "\n";  //获取字符串的长度
    cout << s1.capacity() << " " << s2.capacity() << "\n";  //获取字符串的容量，根据当前内存确定最大长度，后续分配内存后可以改变
    cout << s1.max_size() << " " << s2.max_size() << "\n";  //获取字符串的最大容量，系统预定的最大长度，系统决定了上线
    cout << s1.append(s2) << " " << s2.append(s1) << "\n";  //字符串拼接
    cout << s1.assign(s2) << " " << s2.assign(s1) << "\n";  //字符串赋值
    cout << s1.insert(0,s2) << " " << s2.insert(0,s1) << "\n";  //字符串插入
    cout << s1.erase(0,5) << " " << s2.erase(0,5) << "\n";  //字符串删除
    cout << s1.replace(0,5,s2) << " " << s2.replace(0,5,s1) << "\n";    //字符串替换
    cout << s1.find(s2) << " " << s2.find(s1) << "\n";  //字符串查找
    cout << s1.rfind(s2) << " " << s2.rfind(s1) << "\n";    //字符串反向查找
    cout << s1.substr(0,5) << " " << s2.substr(0,5) << "\n";    //字符串截取
    cout << s1.compare(s2) << " " << s2.compare(s1) << "\n";    //字符串比较
    cout << s1.at(0) << " " << s2.at(0) << "\n";    //字符串访问
    cout << s1.front() << " " << s2.front() << "\n";    //字符串访问
    cout << s1.back() << " " << s2.back() << "\n";  //字符串访问
    cout << s1.c_str() << " " << s2.c_str() << "\n";    //字符串转换成c风格字符串
    cout << s1.data() << " " << s2.data() << "\n";  //字符串转换成c风格字符串
}

void test2(){

}

int main(){
    test();
    test1();
    test2();
}