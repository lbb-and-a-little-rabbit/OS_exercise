#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct {
    int n;
    sem_t semf;
    sem_t semb;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    sem_init(&obj->semf, 0, 1);
    sem_init(&obj->semb, 0, 0);
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->semf);
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        sem_post(&obj->semb);
    }
}

void bar(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        sem_wait(&obj->semb);
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        sem_post(&obj->semf);
    }
}

void fooBarFree(FooBar* obj) {
    sem_destroy(&obj->semf);
    sem_destroy(&obj->semf);
    free(obj);
}