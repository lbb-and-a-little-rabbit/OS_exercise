#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int n;
    int cur;
    bool iszero;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->cur = 1;
    obj->iszero = true;
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void printNumber(int x);

void zero(ZeroEvenOdd* obj) {
    for (int i=0; i<obj->n; i++){
        pthread_mutex_lock(&obj->mutex);
        while (!obj->iszero) {
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        printNumber(0);
        obj->iszero = false;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
}

void even(ZeroEvenOdd* obj) {
    while (true) {
        pthread_mutex_lock(&obj->mutex);
        while (obj->iszero || obj->cur % 2 == 1 || obj->cur > obj->n) {
            if (obj->cur > obj->n) {
                pthread_mutex_unlock(&obj->mutex);
                return;
            }
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        printNumber(obj->cur);
        obj->iszero = true;
        obj->cur++;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
}

void odd(ZeroEvenOdd* obj) {
    while (true) {
        pthread_mutex_lock(&obj->mutex);
        while (obj->iszero || obj->cur % 2 == 0 || obj->cur > obj->n) {
            if (obj->cur > obj->n) {
                pthread_mutex_unlock(&obj->mutex);
                return;
            }
            pthread_cond_wait(&obj->cond, &obj->mutex);
        }
        printNumber(obj->cur);
        obj->iszero = true;
        obj->cur++;
        pthread_cond_broadcast(&obj->cond);
        pthread_mutex_unlock(&obj->mutex);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj) {
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->cond);
    free(obj);
}