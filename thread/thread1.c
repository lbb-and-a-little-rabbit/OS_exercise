#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

struct Test {
    int a;
    int b;
};

void *callback(void *arg) {
    for (int i=0; i<5; i++){
        printf("sub i = %d\n", i);
    }
    printf("sub %ld\n", pthread_self());
    struct Test *t = (struct Test *)malloc(sizeof(struct Test));
    t->a = 1;
    t->b = 2;
    pthread_exit(t); 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    for (int i=0; i<5; i++) {
        printf("main i = %d\n", i);
    }
    printf("main %ld\n", pthread_self());
    void *ptr;
    pthread_join(tid, &ptr);
    printf("a = %d, b = %d\n", ((struct Test *)ptr)->a, ((struct Test *)ptr)->b);
    free(ptr);
    return 0;
}