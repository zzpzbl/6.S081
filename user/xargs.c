#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
// #include "user/sh.c"

#define ARG_MAX_LENGTH 128

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(2, "missing argvs\n");
        exit(1);
    }
    char buf[ARG_MAX_LENGTH];
    // 接收命令之后的参数
    char * args[MAXARG];
    int args_cnt = 0;
    for (; args_cnt < argc - 1; ++args_cnt) {
        args[args_cnt] = argv[args_cnt + 1];
    }

    int index = 0;
    int start = args_cnt;

    while (read(0, buf + index, sizeof(char)) == sizeof(char)) {
        if (*(buf + index) == '\n') {
            *(buf + index) = '\0';
            args[args_cnt] = malloc(ARG_MAX_LENGTH);
            memmove(args[args_cnt++], buf, index);
            args[args_cnt++] = 0;
            index = 0;
            if (fork() == 0) {
                exec(args[0], args);
            } else {
                wait(0);
                args_cnt = start;
            }
        } else if (*(buf + index) == ' ') {
            *(buf + index) = '\0';
            args[args_cnt] = malloc(ARG_MAX_LENGTH);
            memmove(args[args_cnt++], buf, index);
            index = 0; 
        } else {
            index++;
        }
    }

    exit(0);
}