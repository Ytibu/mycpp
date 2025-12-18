#include <iostream>
using std::cout;
using std::endl;

class Singleton {
public:
    static Singleton &getInstance(int data, int data2){
        static Singleton instance(data, data2);
        return instance;
    }
    void print(){
        cout << "m_data: " << m_data << endl;
        cout << "m_data2: " << m_data2 << endl;
    }
private:
    Singleton(int data, int data2)
        : m_data(data), m_data2(data2)
    {
        cout << "Singleton()" << endl;
    }
    ~Singleton(){
        cout << "~Singleton()" << endl;
    }
    Singleton(const Singleton&) = delete;
    Singleton &operator=(const Singleton&) = delete;

private:
    int m_data;
    int m_data2;
};


int main(){
    /* 即使初始化，根据判断局部静态区已经存在了一个实例，
    所以不会重新创建，只会返回已经创建的实例引用 
    因此(1,1)的print调用的是局部静态区存在的(100,200)的引用的print调用
    */
    Singleton::getInstance(100,200).print();
    Singleton::getInstance(1,1).print();    

    cout << "&Singleton::getInstance(100,200) = " << &Singleton::getInstance(100,200) << endl;


}