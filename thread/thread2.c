#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *callback(void *arg) {
    for (int i=0; i<5; i++){
        printf("sub i = %d\n", i);
    }
    printf("sub %ld\n", pthread_self());
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    printf("main %ld\n", pthread_self());
    pthread_detach(tid);

    pthread_exit(NULL);
    return 0;
}