#include <unistd.h>
#include <stdio.h>

int main() {
    int x = 42;
    int ret = fork();
    if(ret < 0){
        //fork失败
        fprintf(stderr, "Fork failed\n");
    }
    else if (ret == 0){
        //子进程
        printf("Child process id: %d, and the value of x is %d \n", ret, x);
    }else{
        //父进程
        printf("Parent process id: %d, and the value of x is %d \n", ret, x);
    }
        
    return 0; 
}