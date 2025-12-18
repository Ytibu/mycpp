#include "EchoServer.h"
#include "TcpConnection.h"
#include <iostream>
#include <functional>
using std::cout;
using std::endl;



MyTask::MyTask(const string &msg, const TcpConnectionPtr &conn)
: _msg(msg), _conn(conn)
{

}
void MyTask::process()
{
    _conn->sendInLoop(_msg);
}

EchoServer::EchoServer(size_t threadNum, size_t queSize, const string &ip, unsigned short port)
: _pool(threadNum, queSize)
,_server(ip, port)
{

}
EchoServer::~EchoServer()
{

}
void EchoServer::start()
{
    _pool.start();
    using namespace std::placeholders;
    _server.setAllCallback(std::bind(&EchoServer::onNewConnection, this, _1),
                            std::bind(&EchoServer::onMessage, this, _1),
                            std::bind(&EchoServer::onClose, this, _1));
    _server.start();
}
void EchoServer::stop()
{
    _pool.stop();
    _server.stop();
}

void EchoServer::onNewConnection(const TcpConnectionPtr &conn)
{
    cout << conn->toString() << " has connected" << endl;
}
void EchoServer::onMessage(const TcpConnectionPtr &conn)
{
    string msg = conn->receive();
    cout << msg << endl;
    MyTask task(msg, conn);
    _pool.addTask(std::bind(&MyTask::process, task));
}
void EchoServer::onClose(const TcpConnectionPtr &conn)
{
    cout << conn->toString() << " has closed" << endl;
}