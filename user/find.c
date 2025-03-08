#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *filename) {
    char buf[DIRSIZ+1];
    char *p;
    struct dirent de;
    struct stat st;
    int fd;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    
    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type) {
        case T_FILE:
            if (strlen(path) < strlen(filename)) {
                close(fd);
                break;
            }
            strcpy(buf, path);
            p = buf + strlen(buf);
            while (*p != '/') {
                p--;
            }
            p++;
            if (!strcmp(p, filename)) {
                printf("%s\n", path);
            }
            close(fd);
            break;
        case T_DIR:
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            while (read(fd, &de, sizeof(de)) == sizeof(de)) {
                if(de.inum == 0)
                    continue;
                if (!strcmp(de.name, ".")) {
                    continue;
                }
                if (!strcmp(de.name, "..")) {
                    continue;
                }
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                find(buf, filename);
            }
            close(fd);
            break;
    }
}

int
main(int argc, char *argv[])
{
    if (argc <= 2) {
        fprintf(2, "usage: find args...\n");
        exit(1);
    }

    char *path = argv[1];
    char *filename = argv[2];
    find(path, filename);

    exit(0);
}