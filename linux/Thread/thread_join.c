#include <Cfun.h>

void *thread_Func(){
    printf("thread_Func\n");
    pthread_exit((void *)123);
}

int main(){

    pthread_t thread;
    pthread_create(&thread, NULL, thread_Func, NULL);
    void *ret;
    pthread_join(thread, ret);
    printf("ret = %ld\n", (long)ret);
    
}