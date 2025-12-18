#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;


/**
 * 测试TcpConnection
 * 此目录下的代码通过手动封装c库函数和linux系统接口实现了Server与client的通信
 * 缺点：无法实现与多个客户端进行通信，无法进行并发通信
 * 优点：代码量少，可读性高
 * 测试方法：
 * 1. 编译所有文件，生成可执行文件 a.out
 * 2. 运行 a.out
 * 3. 客户端与127.0.0.1 8888建立连接
 */

void test(){

    Acceptor acceptor("127.0.0.1",8888);    // 创建一个监听套接字
    acceptor.ready();   // 监听

    TcpConnection conn(acceptor.accept());  // 接受连接

    cout << conn.toString() << endl;    // 打印连接信息

    // 接收消息
    while (1)
    {
        cout << "waiting for message..." << endl;
        cout << "received: " << conn.receive() << endl; // 接收消息
        conn.send("this is server has receive\n");  // 发送消息
    }
    
}

int main(int argc, char *argv[]){
    test();
    return 0;
}