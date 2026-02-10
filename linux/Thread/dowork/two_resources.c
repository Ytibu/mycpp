#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

typedef struct Resource_t
{
    int resource_num;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Resource;

void *Customer1(void *arg){
    Resource *resource = (Resource *)arg;
    while(1){
        pthread_mutex_lock(&resource->mutex);
        while(resource->resource_num < 1){
            printf("Customer1: 不存在资源1, 等待\n");
            pthread_cond_wait(&resource->cond, &resource->mutex);
        }

        --resource->resource_num;
        printf("Customer1: 消耗了一个资源，剩余: %d\n", resource->resource_num);
        pthread_cond_signal(&resource->cond);
        pthread_mutex_unlock(&resource->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *Customer2(void *arg){
    Resource *resource = (Resource *)arg;
    while(1){
        pthread_mutex_lock(&resource->mutex);
        while(resource->resource_num < 2){
            printf("Customer2: 不存在资源2, 等待\n");
            pthread_cond_wait(&resource->cond, &resource->mutex);
        }
        resource->resource_num-=2;
        printf("Customer2: 消耗了两个资源，剩余: %d\n", resource->resource_num);
        pthread_cond_signal(&resource->cond);
        pthread_mutex_unlock(&resource->mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

void *Service(void *arg){
    Resource *resource = (Resource *)arg;
    while(1){
        pthread_mutex_lock(&resource->mutex);
        while(resource->resource_num >= 3){
            printf("Service: 资源已产生，等待中...\n");
            printf("----------------------------------\n");
            pthread_cond_wait(&resource->cond, &resource->mutex);
        }

        ++resource->resource_num;
        printf("Service: 生产了一个资源，当前: %d\n", resource->resource_num);
        pthread_cond_broadcast(&resource->cond);

        pthread_mutex_unlock(&resource->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    Resource resource;
    resource.resource_num = 0;
    pthread_mutex_init(&resource.mutex, NULL);
    pthread_cond_init(&resource.cond, NULL);


    pthread_t customer1_pthread, customer2_pthread, service_pthread;

    pthread_create(&customer1_pthread, NULL, Customer1, (void *)&resource);
    pthread_create(&customer2_pthread, NULL, Customer2, (void *)&resource);
    pthread_create(&service_pthread, NULL, Service, (void *)&resource);

    pthread_join(customer1_pthread, NULL);
    pthread_join(customer2_pthread, NULL);
    pthread_join(service_pthread, NULL);

    pthread_cond_destroy(&resource.cond);
    pthread_mutex_destroy(&resource.mutex);
    return 0;
}