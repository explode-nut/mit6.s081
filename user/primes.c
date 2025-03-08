#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int is_prime(int n) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int
main(int argc, char *argv[])
{
    int number;
    int p[2];

    for (number = 2; number <= 35; number++) {
        if (is_prime(number)) {
            pipe(p);
            write(p[1], &number, sizeof(int));
            int pid = fork();
            if (pid == 0) {
                int prime_number;
                close(p[1]);
                while (read(p[0], &prime_number, sizeof(int))) {
                    printf("prime %d\n", prime_number);
                }
                close(p[0]);
                exit(0);
            }
            close(p[0]);
            close(p[1]);
            wait(0);
        }
    }
    exit(0);
}