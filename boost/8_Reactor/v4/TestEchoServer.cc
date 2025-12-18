#include <iostream>
#include "EchoServer.h"

using std::cout;
using std::endl;


// 利用线程池 并发的处理业务逻辑(Reactor + ThreadPool)

int main(int argc, char *argv[])
{
    EchoServer server(4, 10, "127.0.0.1", 8888);
    server.start();
    return 0;
}