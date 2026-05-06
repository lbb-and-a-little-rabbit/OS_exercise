#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int n;
    bool isfoo;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    obj->isfoo = true;
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->mutex);
        while(!obj->isfoo) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        obj->isfoo = false;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->mutex);
        while(obj->isfoo) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        obj->isfoo = true;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
}

void fooBarFree(FooBar* obj) {
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->cond);
    free(obj);
}