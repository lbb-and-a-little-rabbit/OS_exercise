#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int n;
    int cur;
    sem_t s0,s3,s5,s35;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n) {
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->cur = 1;
    sem_init(&obj->s0, 0, 1);
    sem_init(&obj->s3, 0, 0);
    sem_init(&obj->s5, 0, 0);
    sem_init(&obj->s35, 0, 0);
    return obj;
}

// Don't change the following declarations
void printNumber(int a);
void printFizz();
void printBuzz();
void printFizzBuzz();

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj) {
    while (true) {
        sem_wait(&obj->s3);
        if (obj->cur <= obj->n) {
            printFizz();
            obj->cur++;
            if (obj->cur%3 ==0 && obj->cur%5 == 0) {
                sem_post(&obj->s35);
            }
            else if (obj->cur % 3 == 0) {
                sem_post(&obj->s3);
            }
            else if (obj->cur % 5 == 0) {
                sem_post(&obj->s5);
            }
            else {
                sem_post(&obj->s0);
            }
        }
        else {
            sem_post(&obj->s35);
            sem_post(&obj->s0);
            sem_post(&obj->s5);
            return;
        }
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj) {
    while (true) {
        sem_wait(&obj->s5);
        if (obj->cur <= obj->n) {
            printBuzz();
            obj->cur++;
            if (obj->cur%3 ==0 && obj->cur%5 == 0) {
                sem_post(&obj->s35);
            }
            else if (obj->cur % 3 == 0) {
                sem_post(&obj->s3);
            }
            else if (obj->cur % 5 == 0) {
                sem_post(&obj->s5);
            }
            else {
                sem_post(&obj->s0);
            }
        }
        else {
            sem_post(&obj->s35);
            sem_post(&obj->s3);
            sem_post(&obj->s0);
            return;
        }
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj) {
    while (true) {
        sem_wait(&obj->s35);
        if (obj->cur <= obj->n) {
            printFizzBuzz();
            obj->cur++;
            if (obj->cur%3 ==0 && obj->cur%5 == 0) {
                sem_post(&obj->s35);
            }
            else if (obj->cur % 3 == 0) {
                sem_post(&obj->s3);
            }
            else if (obj->cur % 5 == 0) {
                sem_post(&obj->s5);
            }
            else {
                sem_post(&obj->s0);
            }
        }
        else {
            sem_post(&obj->s3);
            sem_post(&obj->s0);
            sem_post(&obj->s5);
            return;
        }
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj) {
    while (true) {
        sem_wait(&obj->s0);
        if (obj->cur <= obj->n) {
            printNumber(obj->cur);
            obj->cur++;
            if (obj->cur%3 ==0 && obj->cur%5 == 0) {
                sem_post(&obj->s35);
            }
            else if (obj->cur % 3 == 0) {
                sem_post(&obj->s3);
            }
            else if (obj->cur % 5 == 0) {
                sem_post(&obj->s5);
            }
            else {
                sem_post(&obj->s0);
            }
        }
        else {
            sem_post(&obj->s35);
            sem_post(&obj->s3);
            sem_post(&obj->s5);
            return;
        }
    }
}

void fizzBuzzFree(FizzBuzz* obj) {
    sem_destroy(&obj->s0);
    sem_destroy(&obj->s3);
    sem_destroy(&obj->s5);
    sem_destroy(&obj->s35);
    free(obj);
}