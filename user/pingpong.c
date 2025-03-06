#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    int pid = fork();
    
    if (pid == 0) {
        int child_pid;
        close(p[1]);
        read(p[0], &child_pid, sizeof(int));
        close(p[0]);
        printf("%d: received ping\n", child_pid);
    } else {
        close(p[0]);
        write(p[1], &pid, sizeof(int));
        wait(0);
        printf("%d: received pong\n", getpid());
    }

    exit(0);
}