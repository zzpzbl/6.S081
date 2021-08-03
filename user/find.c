#include "kernel/types.h"
#include "kernel/syscall.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void find(char * path, char * src) 
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return ;
    }

    if (fstat(fd, &st)  < 0 || T_DIR != st.type) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return ;
    }

    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ =  '/';
        if (de.inum == 0) 
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (stat(buf, &st) < 0) {
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        switch (st.type)
        {
        case T_FILE:
            if (strcmp(src, de.name) == 0) {
                printf("%s\n", buf);
            }
            break;
        case T_DIR:
            if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0) {
                find(buf, src);
            }
            break;
        default:
            break;
        }
    }
    close(fd);
}

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(2, "missing argvs\n");
        exit(1);
    }

    find(argv[1], argv[2]);

    exit(0);
}