#include <Cfun.h>

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
    //sleep(1);
}

int main(){

    test();
}