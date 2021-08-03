#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) 
{
    if(argc < 2) {
        fprintf(2, "参数缺失\n");
        exit(1);
    }

    if (argc > 3) {
        fprintf(2, "参数过多\n");
        exit(1);
    }

    int ticks = atoi(argv[1]);

    sleep(ticks);

    exit(0);


}


