#include <iostream>
#include <string>
#include <cstring>
using std::cout;
using std::string;


/*对象创建函数*/
void test(){
    string s1;    //默认构造函数：创建一个空字符串
    const char *p = "hello world";
    string s2(p);   //将C风格字符串p转换成string对象
    string s3(p,5); //将C风格字符串p的前5个字符转换成string对象
    string s4(s2);  //拷贝构造函数创建一个字符串
    char ch = 'a';
    string s5(4,ch);    //创建一个字符串对象，使用4个字符ch
    auto begin = s2.begin();
    auto end = s2.end();
    string s6(begin,end);

    cout << s1 << "\n";
    cout << s2 << "\n";
    cout << s3 << "\n";
    cout << s4 << "\n";
    cout << s5 << "\n";
    cout << s6 << "\n";

    cout << "\n";
}

/*字符串拼接函数*/
void test1(){
    string s1("hello");
    string s2("world");
    string s3 = s1 + s2;
    string s4 = s1 + ' ' + s2;
    string s5 = s1 + " world";

    cout << s1 << "\n";
    cout << s2 << "\n";
    cout << s3 << "\n";
    cout << s4 << "\n";
    cout << s5 << "\n";

    cout << "\n";
}

/*常用操作*/
void test2(){

    string str("hello world");
    cout << "输出字符串：" << str << "\n";
    cout << "字符串内容：" << str.data() << "\n";
    cout << "字符串为空：" << str.empty() << "\n";
    cout << "字符串长度：" << str.size() << "\n";
    cout << "字符串容量：" << str.capacity() << "\n";

    cout << "转为C字符串：" << str.c_str() << "\n";
    cout << "字符串首字符：" << str.front() << "\n";
    cout << "末尾添加字符串：" << str.append(" abc") << "\n";
    cout << "字符串插入：" << str.insert(0, "abc ") << "\n";
    cout << "字符串比较：" << str.compare("hello") << "\n";

    cout << "\n";

}
void test3(){

    string str("hello world");
    for(size_t i=0; i<str.size(); i++){
        cout << str[i];
    }
    cout << "\n";


    for(auto &ch : str){
        cout << ch;
    }
    cout << "\n";

    auto iter = str.begin();
    while(iter != str.end()){
        cout << *iter;
        ++iter;
    }cout << "\n";

}

int main(){
    test();
    test1();
    test2();
    test3();
}