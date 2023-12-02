//
// Created by darianfd99 on 12/2/23.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if(argc < 2) {
        fprintf(2, "xargs requires at least one argument\n");
        exit(0);
    }

    int pid, n, i = 0;
    char buf, arg[1024]
    char *args[50];

    for(int i = 1; i < argc; ++i) args[i-1] = argv[i];

    args[argc-1] = arg; args[argc] = 0;
    while( (n = read(0, &buf, 1)) > 0 ) {
        if( buf == '\n' || buf == ' ') {
            arg[i] = 0;

            if((pid = fork()) < 0 ) {
                fprintf(2, "fork error...\n");
                exit(0);
            } else if (pid == 0) {
                exec(args[0], args);
            } else {
                wait(0);
                i = 0;
            }
        }
        else arg[i++] = buf;
    }
    if(n < 0) {
        fprintf(2, "read error...\n");
        exit(1);
    }
    exit(0);
}