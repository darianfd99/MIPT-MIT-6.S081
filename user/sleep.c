//
// Created by darianfd99 on 12/1/23.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc <= 1){
        fprintf(2, "no arguments");
    }

    int sleepTime = atoi(argv[1]);
    int status = sleep(sleepTime);
    exit(status);
}

