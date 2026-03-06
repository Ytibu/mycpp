
## 库引入  
```
# Uubuntu
sudo apt install libmysqlclient-dev
```


## 头文件引入与编译  
```
#头文件引入
#include <mysql/mysql.h>
#编译链接
gcc -o myProject.c myPoroject -l mysqlclient
```

## 代码接口  

```
MYSQL * mysql_init(MYSQL *mysql);//为MySQL连接分配资源，参数一般填NULL
//数据结构MYSQL是操作资源的句柄
//多线程时，mysql_init可能线程不安全，因此推荐在mysql_init前加锁，推荐在mysql_real_connect后解锁，预防此函数也是线程不安全

void mysql_close(MYSQL *mysql);
//关闭MYSQL连接

MYSQL *mysql_real_connect(MYSQL *mysql,
    const char *host, const char *user, const char *passwd, const char *db,
    unsigned int port, const char *unix_socket, unsigned long client_flag
);//连接到MySQL服务端
//一般的参数
// host -> "localhost" user -> "root" passwd-> 密码 db->数据库名
// 其余参数选择默认 port -> 0 unix_socket -> NULL client_flag -> 0
// 如果出现报错，返回值为NULL，使用mysql_error函数可以获取报错原因

int mysql_query(MYSQL *mysql, const char *stmt_str);
// 执行SQL语句，stmt_str -> SQL语句的内容 不需要加分号

MYSQL_RES *mysql_store_result(MYSQL *mysql);
// 在mysql_query之后调用，假如执行的SQL语句会得到结果，需要使用该函数将结果存入数据结构MYSQL_RES当中

void mysql_free_result(MYSQL_RES *result);
// 释放数据结构MYSQL_RES占据的内存空间

my_ulonglong mysql_num_rows(MYSQL_RES *result);
// SQL语句结果的行数

unsigned int mysql_num_fields(MYSQL_RES *result);
// SQL语句结果的列数

MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
// 从结果当中取出一行
```


