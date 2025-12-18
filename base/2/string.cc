#include <iostream>
#include <cstring>
using std::cout;

int main() {
    char s[] = "12345"; //带有终止符的字符串
    char str1[] = {'1', '2', '3', '4', '5'};    //不带有终止符的字符串，会持续输出
    char s1[] = "12345";
    char str2[] = {'1', '2', '3', '4', '5','\0'};   //带有终止符的字符串，遇到\0终止符停止输出
    char s2[] = "12345";

    const char* str3 = "12345";
    char* str4 = new char[5]();
    strcpy(str4, str3);
    char* str5 = new char[5]{"abcd"};
    


    cout << s << '\n';
    cout << str1 << '\n';
    cout << str2<< '\n';
    cout << str3 << '\n';
    cout << str4 << '\n';
    cout << str5 << '\n';

    return 0;
}