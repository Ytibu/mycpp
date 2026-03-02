# ProcessPool 项目介绍（新手友好版）

这是一个基于 **Linux 多进程 + epoll + 文件描述符传递（SCM_RIGHTS）** 的小型文件传输项目。

你可以把它理解成：
- 一个主进程负责“接待客户端”和“任务调度”；
- 多个子进程负责“真正干活（发送文件）”；
- 客户端负责“连接并接收文件”。

---

## 1. 项目想解决什么问题？

如果只有单进程服务器，处理多个客户端时容易阻塞、吞吐有限。
这个项目通过“**预先创建进程池**”来提升并发处理能力：

1. 主进程只做调度，不做重活；
2. 子进程专门处理连接和传输；
3. 主进程把 `accept` 到的连接 fd 传给空闲子进程；
4. 子进程处理完后再通知主进程“我空闲了”。

---

## 2. 总体架构图

```text
            +------------------------+
            |        Client          |
            |      (client.c)        |
            +-----------+------------+
                        |
                      TCP
                        |
+------------------------------------------------+
|                Master Process                  |
|                 (server/main.c)                |
|                                                |
|  listen/accept + epoll + worker status         |
|  分发 netfd --> sendfd(SCM_RIGHTS)             |
+-----------+------------------+-----------------+
            |                  |
      socketpair          socketpair
            |                  |
   +--------v-------+   +------v--------+   ...
   | Worker Process |   | Worker Process |
   |   worker.c     |   |   worker.c     |
   | recvfd->trans  |   | recvfd->trans  |
   +----------------+   +---------------+
```

一句话：**主进程做“调度”，子进程做“执行”。**

---

## 3. 目录结构与职责

```text
ProcessPool/
├── client/
│   ├── client.c      # 客户端：连接服务器并接收文件
│   ├── demo.txt      # 客户端侧样例文件（运行后会生成/覆盖）
│   └── Makefile      # 客户端编译脚本
├── server/
│   ├── main.c        # 主进程入口：epoll事件循环 + 任务分发 + 优雅退出
│   ├── worker.c      # 进程池创建、子进程循环逻辑
│   ├── fdMessage.c   # sendmsg/recvmsg 实现 fd 传递（SCM_RIGHTS）
│   ├── tcpInit.c     # TCP监听初始化（socket/bind/listen）
│   ├── epoll.c       # epoll add/del 封装
│   ├── transFile.c   # 文件发送协议与发送实现（目前用 sendfile）
│   ├── head.h        # 公共头文件、宏、结构体、函数声明
│   ├── demo.txt      # 服务端要发送的文件
│   └── Makefile      # 服务端编译脚本
└── tests/
    ├── shareFd.c / shareFd1.c / worker.c / test.c
    ├── head.h
    └── Makefile      # fd 传递等机制验证样例
```

---

## 4. 服务端代码结构（按调用链看）

### 4.1 启动阶段

`server/main.c`：
1. 解析参数：`ip port workerNum`；
2. `makeWorker()` 创建子进程池（`worker.c`）；
3. `tcpInit()` 初始化监听 socket（`tcpInit.c`）；
4. 把监听 fd、各子进程通信 fd、退出管道 fd 全部加入 epoll。

### 4.2 运行阶段（事件循环）

`main.c` 的 epoll 处理三类事件：
- **新连接到来**：`accept` 得到 `netfd`；
- **子进程反馈可用**：把该 worker 状态标记回 `FREE`；
- **退出信号到来**：广播退出标志，回收子进程并清理资源。

### 4.3 任务分发（关键点）

- 主进程发现某个 worker 是 `FREE`，调用：
  - `sendfd(workerSock, netfd, 0)`（`fdMessage.c`）
- 本质是通过 Unix 域套接字 `socketpair` 把客户端连接 fd 传过去。

### 4.4 子进程工作流程

`workerLoop()`（`worker.c`）不断循环：
1. `recvfd()` 接收主进程发来的 `netfd` 和 `exitFlag`；
2. 如果 `exitFlag==1`，子进程退出；
3. 否则调用 `transFile(netFd)` 发送文件；
4. 发送完成后把自己的 pid 回传给主进程，表示空闲。

### 4.5 文件传输实现

`transFile.c` 里保留了多版本演进注释：
- 从“直接 send”到“小火车协议（length + data）”；
- 处理粘包/半包；
- 再到 `mmap`，最后使用 `sendfile()`。

当前启用的是：
- 先发送文件名；
- 再发送文件大小；
- 再用 `sendfile` 发送文件内容。

---

## 5. 一次完整请求的时序（新手重点）

1. 客户端连接服务器；
2. 主进程 `accept` 得到 `netfd`；
3. 主进程挑选一个空闲 worker；
4. 主进程用 `sendfd` 把 `netfd` 传给该 worker；
5. worker 执行 `transFile` 发文件；
6. worker 通知主进程“我空闲了”；
7. 主进程把该 worker 状态改回 `FREE`，等待下一次分发。

---

## 6. 快速上手（如何运行）

### 6.1 编译

```bash
# 编译服务端
cd server && make

# 编译客户端
cd ../client && make
```

### 6.2 启动服务端

```bash
cd ../server
./server.out 0.0.0.0 1234 5
```

参数说明：
- `0.0.0.0`：监听地址
- `1234`：监听端口
- `5`：进程池中 worker 数量

### 6.3 启动客户端

```bash
cd ../client
./client.o 127.0.0.1 1234
```

运行后客户端会接收服务端 `demo.txt`（同名文件可能被覆盖）。

### 6.4 退出服务端

主进程注册了 `SIGUSR1`，可在另一终端发送：

```bash
pkill -USR1 server.out
```

服务端会通知所有 worker 退出并回收资源。

---

## 7. 新手阅读建议（按顺序）

推荐阅读顺序：
1. `server/head.h`（先认结构体和函数）
2. `server/main.c`（看主流程）
3. `server/worker.c`（看子进程生命周期）
4. `server/fdMessage.c`（理解 fd 传递）
5. `server/transFile.c`（看传输协议演进）
6. `client/client.c`（对照接收端）

如果你是第一次接触“进程池 + fd 传递”，先跑通再调试：
- 先理解“谁负责 accept，谁负责 send”；
- 再理解“为什么要传递 fd，而不是子进程自己 accept”。

---

## 8. 你可以继续练习的方向

- 给任务分发加“负载均衡策略”（而不是遇到第一个空闲就分发）；
- 让客户端支持自定义保存文件名；
- 为传输协议增加校验（如 hash）；
- 让主进程支持更多控制信号（平滑重启等）；
- 把日志改成统一日志模块，便于排查问题。

这份项目很适合练习 Linux 网络编程中的核心能力：
**epoll、进程池、IPC、fd 传递、文件传输优化。**
