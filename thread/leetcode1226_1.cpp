#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>
#include <functional>

#define N 5

using namespace std;

// 可能出现死锁

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
		sem_wait(&forks[left(philosopher)]);
        sem_wait(&forks[right(philosopher)]);
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        sem_post(&forks[left(philosopher)]);
        sem_post(&forks[right(philosopher)]);
    }
};