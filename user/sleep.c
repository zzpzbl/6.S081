#include "user.h"
#include "kernel/syscall.h"
#include "kernel/types.h"

int
main(int argc, char *argv[]) 
{
    if(argc < 2) {
        fprintf(2, "参数缺失\n");
        exit(1);
    }

    if (argv > 3) {
        fprintf(2, "参数过多\n");
        exit(1);
    }

    int ticks = atoi(argv[1]);

    sleep(ticks);

    exit(0);


}


