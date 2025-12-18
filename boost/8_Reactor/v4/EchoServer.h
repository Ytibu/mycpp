#ifndef __ECHO_SERVER_H__
#define __ECHO_SERVER_H__ 

#include "ThreadPool.h"
#include "TcpServer.h"
class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &conn);
    void process();

private:
    string _msg;
    TcpConnectionPtr _conn;
};

class EchoServer {
public:
    EchoServer(size_t threadNum, size_t queSize, const string &ip, unsigned short port);
    ~EchoServer();
    void start();
    void stop();

    void onNewConnection(const TcpConnectionPtr  &conn);
    void onMessage(const TcpConnectionPtr  &conn);
    void onClose(const TcpConnectionPtr  &conn);
private:
    ThreadPool _pool;
    TcpServer _server;
};

#endif