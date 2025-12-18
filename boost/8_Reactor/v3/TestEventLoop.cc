#include <iostream>

#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include "TcpServer.h"
#include "ThreadPool.h"

using std::cout;
using std::endl;


// 利用线程池 并发的处理业务逻辑(Reactor + ThreadPool)


ThreadPool *gPool;  // 全局变量
class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &conn)
        : _msg(msg), _conn(conn)
    {
    }

    void process()
    {
        cout << _msg << endl;

        // 业务逻辑处理：decode,compute,encode

        // 将处理后数据发送给Reactor,Reactor将数据发送给客户端

        _conn->sendInLoop(_msg);
    }

private:
    string _msg;
    TcpConnectionPtr _conn;
};


void onNewConnection(const TcpConnectionPtr &conn)
{
    string msg = conn->toString();
    cout << msg << " has connected" << endl;

    MyTask task(msg, conn);

    gPool->addTask(std::bind(&MyTask::process, task));
}

void onMessage(const TcpConnectionPtr &conn)
{
    cout << conn->receive() << endl;
}

void onClose(const TcpConnectionPtr &conn)
{
    cout << conn->toString() << " has closed" << endl;
}


void test()
{
    ThreadPool threadPool(4,10);
    threadPool.start();
    gPool = &threadPool;

    TcpServer server("127.0.0.1", 8888);

    server.setAllCallback(std::move(onNewConnection)
                        , std::move(onMessage)
                        ,std::move(onClose));

    server.start();
}
int main(int argc, char *argv[])
{
    test();
    return 0;
}