#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>


/**
 * pthread_create()
 *  int pthread_create (
 *      pthread_t *__newthread, //新线程的线程id
 *      const pthread_attr_t *__attr,   //线程属性，一般传入NULL，表示默认属性
 *      void *(*__start_routine) (void *),  //线程函数入口地址
 * 	    void *__arg //传递给线程函数的参数
 *  );
 * 
 * 
 */

void *routine(void *arg){
    printf("this is a child thread\n");
    return NULL;
}

void test(){

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, routine, NULL);
    if(ret!=0){
        fprintf(stderr,"%s:%s","pthread_create",strerror(ret));
    }
    printf("this is a main thread\n");
    sleep(1);
}

int main(){

    test();
}