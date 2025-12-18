#include <iostream>
#include <functional>
#include <vector>

using std::function;
using std::vector;
using std::string;


vector<function<void(const std::string &)>> f;

void test(){
    
    int num = 100;
    string name = "cPlusPlus";

    f.push_back([&](const string &value){
        std::cout << "num: " << num 
                << " name: " << name 
                << " value: " << value << std::endl;
    });

    f[0]("test");

    for(auto &func: f){
        func("test");
    }
    
}

/*离开函数作用域，无法访问内容*/
void test2(){
    f[0]("test");

    for(auto &func: f){
        func("test");
    }
}

int main(){

    test();
    //test2();

}