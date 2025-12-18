#include <iostream>
using namespace std;



/**
 * c++中的结构体等效于类
 * c++的struct可以和class互相继承
 * struct继承struct和class是默认权限为public
 * class继承struct和class是默认权限为private
 * 初次之外其他一样
 */


struct student{
public:
    char name[20];
protected:
    float height;
private:
    int age;
};


/*定义时可以不用写struct*/
typedef struct{
public:
    char name[20];
protected:
    float height;
private:
    int age;
}teacher;


//公共继承：父类权限继承给子类
struct students : public student{
    char sex;
    float height = height;
};

//私有继承：父类成员继承给子类时为私有的
struct teacers : private teacher{
    char sex;
};



void test(){
    student s;
    s.name[20] = 'jack\0';
    //s.height = 1.7;
    //s.age = 18;
    students s1;
    s1.name[20] = 'tom\0';
    s1.sex = 'm';
    //s1.height = 1.8;
    //s1.age = 19;
    teacher t;
    t.name[20] = 'lucy\0';
    //t.age = 18;
    //t.height = 1.6;
    teacers t1;
    //t1.name[20] = 'lili\0';
    t1.sex = 'f';
    //t1.age = 18;
    //t1.height = 1.5;

}

int main(){
    test();
    return 0;
}