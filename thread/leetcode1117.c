#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    // User defined data may be declared here.
    sem_t hsem;
    sem_t osem;
    pthread_mutex_t mutex;
    int hcnt;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    
    // Initialize user defined data here.
    sem_init(&obj->hsem, 0, 0);
    sem_init(&obj->osem, 0, 1);
    pthread_mutex_init(&obj->mutex, NULL);
    obj->hcnt = 0;
    
    return obj;
}

void hydrogen(H2O* obj) {
    sem_wait(&obj->hsem);
    pthread_mutex_lock(&obj->mutex);
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();
    obj->hcnt++;
    if (obj->hcnt == 2) {
        obj->hcnt = 0;
        sem_post(&obj->osem);
    }
    pthread_mutex_unlock(&obj->mutex);
}

void oxygen(H2O* obj) {
    sem_wait(&obj->osem);
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
    pthread_mutex_lock(&obj->mutex);
    sem_post(&obj->hsem);
    sem_post(&obj->hsem);
    pthread_mutex_unlock(&obj->mutex);
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here.
    sem_destroy(&obj->hsem);
    sem_destroy(&obj->osem);
    pthread_mutex_destroy(&obj->mutex);
    free(obj);
}   