#define __MYREDIS_H__
#ifdef __MYREDIS_H__
#include <hiredis/hiredis.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


class MyRedis{
public:
    MyRedis();
    ~MyRedis();
    bool connect(const string &host, int port);
    void set(string key, string value);
    string get(string key);
private:
    redisContext *_pConnect;
    redisReply *_pReply;
};
#endif