#include "MyRedis.h"
#include <memory>


using std::unique_ptr;
using std::cerr;

void test()
{
    unique_ptr<MyRedis> pRedis(new MyRedis());
    if( !pRedis->connect("127.0.0.1", 6379)){
        cerr << "connect redis failed" << endl;
        return ;
    }
    pRedis->set("name", "zhangsan");
    cout << "Get the name is " << pRedis->get("name") << endl; 
}

int main(int argc, char *argv[]){
    test();
    return 0;
}