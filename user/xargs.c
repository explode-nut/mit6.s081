#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
    char t;
    char q[1024];
    char *p = q;
    char *v[MAXARG];

    while(read(0, &t, sizeof(char))) {
        if (t == '\n') {
            for (int i = 1, j = 0; i < argc + 1; i++, j++) {
                if (i < argc) {
                    v[j] = argv[i];
                } else {
                    v[j] = q;
                }
            }
            int pid = fork();
            if (pid == 0) {
                exec(argv[1], v);
            }
            wait(0);
            memset(q, 0, 1024);
            p = q;
        } else {
            *p++ = t;
        }
    }
    exit(0);
}