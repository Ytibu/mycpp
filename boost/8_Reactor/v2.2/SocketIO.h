#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__ 


// SocketIO类：实现了socket的读写功能，数据读写核心功能类

class SocketIO {
public:
    SocketIO(int fd);
    ~SocketIO();
    int readn(char *buf, int len);
    int readLine(char *buf, int len);
    int writen(const char *buf, int len);

private:
    int _fd;
};

#endif