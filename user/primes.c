#include "kernel/types.h"
#include "kernel/syscall.h"
#include "kernel/stat.h"
#include "user/user.h"

void solve(int * p1,  int * p2) 
{
    if (fork() == 0) {
        int num[1];
        if(read(p1[0] ,num, sizeof(num)) != sizeof(num)) {
	        close(p1[0]);
            close(p2[0]);
            close(p2[1]);	  
	        exit(0);
        }
        int prime  = num[0];
        printf("prime %d\n", prime);
        while (read(p1[0], num, sizeof(num)) == sizeof(num)) {
            if (num[0] % prime != 0) {
                write(p2[1], num, sizeof(num));
            }
        }
        close(p1[0]);
        close(p2[1]);
        pipe(p1);
        solve(p2, p1);
        exit(0);
    } else {
        close(p1[0]);
        close(p2[1]);
        close(p2[0]);
        wait(0);
        exit(0);
    }
}

int 
main()
{
    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);

    int i[1];

    for (i[0] = 2; i[0] <= 35; ++i[0]) {
        write(p1[1], i, sizeof(i));
    }

    close(p1[1]);
    solve(p1, p2);

    exit(0);
}