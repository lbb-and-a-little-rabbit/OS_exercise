#include <stdio.h>
#include <unistd.h>

int main() {
    char *pathname = "./hello.out";
    char *args[] = {"./hello.out", "sfdsgdsgds", NULL};
    char *env[] = {NULL};
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed\n");
    }
    else if (pid == 0) {
        if (execve(pathname, args, env) == -1) {
            perror("exec failed\n");
        }
        printf("can't be printed\n");
    }
    else {
        printf("Parent, pid = %d\n", pid);
    }
    return 0;
}