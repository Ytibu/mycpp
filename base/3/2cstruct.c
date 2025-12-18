#include <stdio.h>


/**
 * c语言中的结构体特点：
 * 不可以定义成员函数(可以定义函数指针，这是指针)
 * 默认访问权限都是public，不可以也没有其他访问权限
 * 单纯的结构体，不存在c++类的所有内容
 */

/*定义结构体必须写struct*/
struct student
{
    char name[20];
    int age;
    float height;
};

/*定义时可以不用写struct*/
typedef struct{
    char name[20];
    int age;
    float height;
}teacher;

void test(){
    struct student s1;
    s1.age = 18;
    s1.height = 1.8;
    printf("name:%s, age:%d, height:%f\n", s1.name, s1.age, s1.height);

    teacher t1;
    t1.age = 18;
    t1.height = 1.8;
    printf("name:%s, age:%d, height:%f\n", t1.name, t1.age, t1.height);
}

int main()
{ 
    test();
}