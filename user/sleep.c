#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
pow(int base, int exp) {
    int res = 1;
    while (exp-- != 0) {
        res *= base;
    }
    return res;
}

int
main(int argc, char *argv[])
{
    int i;
    if (argc <= 1) {
        fprintf(2, "usage: sleep seconds...\n");
        exit(1);
    }

    int n = argc - 1;
    int second = 0;
    for (i = 1; i < argc; i++) {
        second += (atoi(argv[i]) * pow(10, n--));
    }
    sleep(second);
    exit(0);
}