#include <Cfun.h>

#define _NUM_ 10000000
pthread_mutex_t mutex;

/**
 * 互斥锁：
 *      int pthread_mutex_init (pthread_mutex_t *__mutex, const pthread_mutexattr_t *__mutexattr)
 *      int pthread_mutex_destroy (pthread_mutex_t *__mutex)
 *      int pthread_mutex_lock (pthread_mutex_t *__mutex)
 *      int pthread_mutex_trylock (pthread_mutex_t *__mutex)
 *      int pthread_mutex_unlock (pthread_mutex_t *__mutex)
 * 
 *      ！！！
 * 注意：无论是只读还是只写还是...只要访问资源--必须优先加锁；谁加锁，谁解锁；保证临界区足够小；谨防死锁
 */

void* thread_Func(void* arg){

    int *val = (int*)arg;
    for(int i = 0; i < _NUM_; ++i){
        pthread_mutex_lock(&mutex);
        *val += 1;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(){

    int val = 0;
    pthread_t tid;

    pthread_mutex_init(&mutex,NULL);
    pthread_create(&tid,NULL,thread_Func,&val);

    for(int i = 0; i < _NUM_; ++i){
        pthread_mutex_lock(&mutex);
        val += 1;
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(tid,NULL);
    
    printf("val = %d\n",val);

    pthread_mutex_destroy(&mutex);

}