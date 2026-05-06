#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    // User defined data may be declared here.
    int number;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*)malloc(sizeof(Foo));
    
    // Initialize user defined data here.
    obj->number = 1;
    pthread_mutex_init(&obj->mutex,NULL);
    pthread_cond_init(&obj->cond, NULL);
    
    return obj;
}

void first(Foo* obj) {
    
    pthread_mutex_lock(&obj->mutex);
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    obj->number++;
    pthread_cond_broadcast(&obj->cond);
    pthread_mutex_unlock(&obj->mutex);
}

void second(Foo* obj) {
    pthread_mutex_lock(&obj->mutex);
    while(obj->number != 2) {
        pthread_cond_wait(&obj->cond, &obj->mutex);
    }
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    obj->number++;
    pthread_cond_broadcast(&obj->cond);
    pthread_mutex_unlock(&obj->mutex);
}

void third(Foo* obj) {
    pthread_mutex_lock(&obj->mutex);
    while(obj->number != 3) {
        pthread_cond_wait(&obj->cond, &obj->mutex);
    }
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
    pthread_mutex_unlock(&obj->mutex);
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->cond);
    free(obj);
}