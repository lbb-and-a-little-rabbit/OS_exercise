#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int number = 0;
pthread_mutex_t mutex;

void *ca(void *arg) {
    for (int i=0; i<50; i++) {
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        //usleep(10);
        number = cur;
        printf("thread A, thread_id = %ld, number = %d\n",pthread_self(), number);
        pthread_mutex_unlock(&mutex);
        usleep(10);
    }
    pthread_exit(NULL);
}

void *cb(void *arg) {
    for (int i=0; i<50; i++) {
        pthread_mutex_lock(&mutex);
        int cur = number;
        cur++;
        //usleep(10);
        number = cur;
        printf("thread B, thread_id = %ld, number = %d\n",pthread_self(), number);
        pthread_mutex_unlock(&mutex);
        usleep(10);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t ida,idb;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&ida, NULL, ca, NULL);
    pthread_create(&idb, NULL, cb, NULL);
    pthread_join(ida, NULL);
    pthread_join(idb, NULL);
    pthread_mutex_destroy(&mutex);
    printf("number = %d\n",number);
    return 0;
}