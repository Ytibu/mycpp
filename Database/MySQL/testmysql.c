#include <stdio.h>

#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "dingjr"
#define MYSQL_PASSWD "123450"
#define MYSQL_DB "testdb"
#define MYSQL_PORT 3306
#define MYSQL_UNIX_SOCKET NULL
#define MYSQL_CLIENT_FLAG 0


int main(int argc, char *argv[])
{
    MYSQL *my = mysql_init(NULL);
    MYSQL *conn_ret =  mysql_real_connect(my, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD, MYSQL_DB, 0, NULL, 0);
    if(conn_ret == NULL){
        fprintf(stderr, "mysql_real_connect() failed: %d\n", mysql_errno(my));
        return -1;
    }

    char sql[4096] = "SELECT * FROM pet";
    if(mysql_query(my, sql)){
        fprintf(stderr, "mysql_query() failed: %d\n", mysql_errno(my));
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(my);
    if(res == NULL){
        fprintf(stderr, "mysql_store_result() failed: %d\n", mysql_errno(my));
        return -1;
    }
    printf("total rows: %lu, total col: %d\n", mysql_num_rows(res), mysql_num_fields(res));

    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i = 0; i < mysql_num_fields(res); ++i){
            printf("%-8s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_close(my);

    return 0;
}
