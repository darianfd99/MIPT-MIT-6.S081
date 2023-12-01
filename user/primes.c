//
// Created by darianfd99 on 12/1/23.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

__attribute__((noreturn))
int primes(int p[2]){
    close(p[1]);
    int p1[2];
    pipe(p1);

    int printedNumber;
    if (read(p[0], &printedNumber, sizeof(int)) == 0){
        exit(0);
    }
    fprintf(0, "prime %d\n", printedNumber);

    int pid;
    if ( (pid = fork()) < 0){
        fprintf(2, "fork error\n");
        exit(1);
    }else if (pid == 0){
        close(p[0]);
        primes(p1);
        exit(0);
    }

    close(p1[0]);
    int number;
    while(read(p[0], &number, sizeof(int)) == sizeof(int)){
        if(number % printedNumber == 0){
            continue;
        }
        int wroteN = write(p1[1], &number, sizeof(int));
        if (wroteN != sizeof(int)){
            fprintf(2, "error trying to send number to the pipe\n");
            exit(1);
        }
    }
    close(p[0]);
    close(p1[1]);
    wait(0);
    exit(0);
}

int main(int argc, char* argv[]){
    int p[2];
    pipe(p);

    int pid;
    if ((pid = fork()) < 0){
        fprintf(2, "fork error\n");
        exit(1);
    }else if(pid == 0){
        primes(p);
        exit(0);
    }

    close(p[0]);
    for(int i = 2; i <= 35; ++i){
        int wroteN = write(p[1], &i, sizeof(int));
        if (wroteN != sizeof(int)){
            fprintf(2, "error trying to send number to the pipe\n");
            exit(1);
        }
    }
    close(p[1]);
    wait(0);
    exit(0);
}