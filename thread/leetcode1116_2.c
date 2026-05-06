#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct {
    int n;
    int cur;
    sem_t sem0;
    sem_t sem1;
    sem_t sem2;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->cur = 1;
    sem_init(&obj->sem0, 0, 1);
    sem_init(&obj->sem1, 0, 0);
    sem_init(&obj->sem2, 0, 0);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void printNumber(int x);

void zero(ZeroEvenOdd* obj) {
    while (true) {
        sem_wait(&obj->sem0);
        if (obj->cur <= obj->n) {
            printNumber(0);
            if (obj->cur % 2 == 0) 
                sem_post(&obj->sem2);
            else
                sem_post(&obj->sem1);
        }
        else {
            sem_post(&obj->sem1);
            sem_post(&obj->sem2);
            return;
        }
    }
}

void even(ZeroEvenOdd* obj) {
    while (true) {
        sem_wait(&obj->sem2);
        if (obj->cur <= obj->n) {
            printNumber(obj->cur);
            obj->cur++;
            sem_post(&obj->sem0);
        }
        else break;
    }
}

void odd(ZeroEvenOdd* obj) {
    while (true) {
        sem_wait(&obj->sem1);
        if (obj->cur <= obj->n) {
            printNumber(obj->cur);
            obj->cur++;
            sem_post(&obj->sem0);
        }
        else break;
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    sem_destroy(&obj->sem0);
    sem_destroy(&obj->sem1);
    sem_destroy(&obj->sem2);
    free(obj);
}