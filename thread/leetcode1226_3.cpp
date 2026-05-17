#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>
#include <functional>
#include <unistd.h>

#define N 5

using namespace std;

// 并行1

class DiningPhilosophers {
public:
    sem_t forks[N];

    DiningPhilosophers() {
        for (int i = 0; i < N; i++) {
            sem_init(&forks[i], 0, 1);
        }
    }

    int left(int i) {
        return i;
    }

    int right(int i) {
        return (i + 1) % N;
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        while (1) {
            sem_wait(&forks[left(philosopher)]);
            if (sem_trywait(&forks[right(philosopher)]) < 0) {
                sem_post(&forks[left(philosopher)]);
                usleep(rand() % 10 + 1);
            }
            else break;
        }
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        sem_post(&forks[left(philosopher)]);
        sem_post(&forks[right(philosopher)]);
    }
};