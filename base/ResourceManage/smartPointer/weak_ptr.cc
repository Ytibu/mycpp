#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::weak_ptr;
using std::shared_ptr;

/**
 * weak_ptr：是对shared_ptr的弱引用，进行赋值或复制时，并不会导致引用计数加1，
 *          weak_ptr知道托管的对象是否存活，必须要提升为shared_ptr才能对资源进行访问，不能直接访问
 *      
 */

class Child;

class Parent
{
public:
    Parent() {cout << "Parent()" << endl;}
    ~Parent() {cout << "~Parent()" << endl;}
    weak_ptr<Child> spChild;
};

class Child
{
public:
    Child() {cout << "Child()" << endl;}
    ~Child() {cout << "~Child()" << endl;}
    weak_ptr<Parent> spParent;
};

void test(){
    shared_ptr<Parent> ParentPtr(new Parent());
    shared_ptr<Child> ChildPtr(new Child());
    cout << "spParent.use_count() = " << ParentPtr.use_count() << endl;
    cout << "spChild.use_count() = " << ChildPtr.use_count() << endl;

    ParentPtr->spChild = ChildPtr;
    ChildPtr->spParent = ParentPtr;
    cout << "spParent.use_count() = " << ParentPtr.use_count() << endl;
    cout << "spChild.use_count() = " << ChildPtr.use_count() << endl;
}


void test(int i){
    shared_ptr<int> sp(new int(10));
    //weak_ptr<int> wp(new int(20));    //error
    weak_ptr<int> wp;
    wp = sp;
    cout << "wp.use_count() = " << wp.use_count() << endl;
    cout << "sp.use_count() = " << sp.use_count() << endl;
}

int main(){

    test();
    //test(1);
}