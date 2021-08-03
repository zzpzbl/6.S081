#include "kernel/types.h"
#include "kernel/syscall.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main() 
{

    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    int pid = fork();
    
    if(pid < 0) {
        fprintf(2, "fork error\n");
        exit(1);
    }

    else if(pid > 0) {
        close(pipe1[0]);
        close(pipe2[1]);
        // 父进程 pipe1[1] 为写端
        write(pipe1[1], "ping",  strlen("ping"));
        // 关闭写端
        close(pipe1[1]);

        char buf[10];
        // 父进程 pipe2[1] 为读端
        read(pipe2[0], buf, 10);
        // printf("%s\n", buf);
        printf("%d: received %s\n", getpid(), buf);
        close(pipe2[0]);
    }
    else {
        close(pipe1[1]);
        close(pipe2[0]);

        char buf[10];
        read(pipe1[0], buf, 10);
        // printf("%s\n", buf);
        printf("%d: received %s\n", getpid(), buf);
        close(pipe1[0]);

        write(pipe2[1], "pong",  strlen("pong"));
        close(pipe2[1]);

    }

    exit(0);

}