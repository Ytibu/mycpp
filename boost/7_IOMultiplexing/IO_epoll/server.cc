#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;


//利用epoll实现服务器


void test() {
    
    // 创建服务器socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("socket");
        return;
    }


    //地址复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));


    // 绑定地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 , sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t server_len = sizeof(server_addr);

    if(::bind(listenfd, (struct sockaddr *)&server_addr, server_len) < 0) {
        perror("bind");
        close(listenfd);
        return;
    }


    if(::listen(listenfd, 128) < 0) {
        perror("listen");
        close(listenfd);
        return;
    }

    cout << "Server Start" << endl;


    //创建epoll实例
    int efd = ::epoll_create1(0);

    //添加监听,监听文件描述符，进行读写监听
    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLOUT;

    if(::epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &ev) < 0) {
        perror("epoll_ctl");
        close(listenfd);
        return;
    }

    struct epoll_event *evtList = 
        (struct epoll_event *)malloc(sizeof(struct epoll_event) * 1024);

    
    while (1){
        
        //Reactor： 事件分离器
        int nready = ::epoll_wait(efd, evtList, 1024, 3000);
        if(nready < 0 && errno == EINTR)
            continue;
        else if(nready < 0) {
            perror("epoll_wait");
            break;
        }else if(nready == 0)
            //timeout
            cout << "timeout" << endl;
        else 
        {
            for(int idx = 0; idx < nready; ++idx) 
            { 
                //EPOLLIN: 读事件
                if((evtList[idx].events & EPOLLIN) && (evtList[idx].data.fd == listenfd))
                {
                    #if 0
                    //accept
                    struct sockaddr_in cliaddr;
                    socklen_t clilen = sizeof(cliaddr);
                    #endif

                    int peerfd = ::accept(listenfd, nullptr, nullptr);  //默认监听所有地址

                    //将新连接添加到epoll监听实例中
                    struct epoll_event evt;
                    evt.data.fd = peerfd;
                    evt.events = EPOLLIN | EPOLLET | EPOLLERR;
                    if (::epoll_ctl(efd, EPOLL_CTL_ADD, peerfd, &evt) < 0) 
                    {
                        perror("epoll_ctl");
                        return;
                    }
                }
                else
                {
                    char buff[128] = {0};
                    if(evtList[idx].events & EPOLLIN){
                        int ret = ::read(evtList[idx].data.fd, buff, sizeof(buff));
                        if(ret > 0){
                            printf("read %d bytes from fd %d\n", ret, evtList[idx].data.fd);
                            ::write(evtList[idx].data.fd, buff, ret);   //将读到的数据回写
                            cout << "write " << ret << " bytes to fd " << evtList[idx].data.fd << endl;
                        }else if(ret == 0){

                            //从epoll中删除监听实例
                            struct epoll_event evt;
                            evt.data.fd = evtList[idx].data.fd; //将文件描述符赋给epoll_event结构体的data成员
                            //删除监听实例
                            if((::epoll_ctl(efd, EPOLL_CTL_DEL, evt.data.fd, &evt)) < 0){
                                perror("epoll_ctl");
                            }
                        }
                    }
                }
            }
        }
    }
    

}


int main(int argc, char *argv[])
{
    test();
}