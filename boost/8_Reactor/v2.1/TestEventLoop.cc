#include <iostream>

#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

using std::cout;
using std::endl;


void onNewConnection(const TcpConnectionPtr &conn)
{
    cout << conn->toString() << " has connected" << endl; 
}

void onMessage(const TcpConnectionPtr &conn)
{
    cout << conn->receive() << endl; 
}

void onClose(const TcpConnectionPtr &conn)
{
    cout << conn->toString() << " has closed" << endl; 
}

void test(){

    Acceptor acceptor("127.0.0.1",8888);
    acceptor.ready();

    EventLoop loop(acceptor);

    loop.setNewConnectionCallback(std::move(onNewConnection));
    loop.setMessageCallback(std::move(onMessage));
    loop.setCloseCallback(std::move(onClose));

    loop.loop();
}

int main()
{ 
    test();
    return 0;
}