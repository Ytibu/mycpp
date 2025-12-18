#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__ 


// SocketIO类：实现了socket的读写功能，数据读写核心功能类

class SocketIO {
public:
    SocketIO(int fd);   // 根据传入文件描述符创建SocketIO对象
    ~SocketIO();    // 关闭文件描述符
    int readn(char *buf, int len);  // 从文件描述符中读取数据
    int readLine(char *buf, int len);   // 读取一行数据
    int writen(const char *buf, int len);   // 向文件描述符中写入数据

private:
    int _fd;
};

#endif