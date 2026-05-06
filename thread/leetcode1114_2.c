#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct {
    // User defined data may be declared here.
    sem_t sem1,sem2,sem3;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    
    // Initialize user defined data here.
    sem_init(&obj->sem1, 0, 1);
    sem_init(&obj->sem2, 0, 0);
    sem_init(&obj->sem3, 0, 0);
    return obj;
}

void first(Foo* obj) {
    sem_wait(&obj->sem1);
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    sem_post(&obj->sem2);
}

void second(Foo* obj) {
    sem_wait(&obj->sem2);
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    sem_post(&obj->sem3);
}

void third(Foo* obj) {
    sem_wait(&obj->sem3);
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
}

void fooFree(Foo* obj) {
    // User defined data may be cleanesem_init(&obj->sem1, 0, 1);d up here.
    sem_destroy(&obj->sem1);
    sem_destroy(&obj->sem2);
    sem_destroy(&obj->sem3);
    free(obj);
}