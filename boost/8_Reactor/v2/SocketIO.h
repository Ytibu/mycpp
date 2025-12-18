#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__ 


// SocketIO类：实现了socket的读写功能，数据读写核心功能类

class SocketIO {
public:
    SocketIO(int fd);
    ~SocketIO();
    int readn(char *buf, int len);  // 读取所有数据
    int readLine(char *buf, int len);   // 读取一行数据
    int writen(const char *buf, int len);   // 写入所有数据

private:
    int _fd;
};

#endif