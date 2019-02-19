#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
int main(int argc,char *argv[]){
        if (argc>2){
                printf("Invalid number of arguments");
                exit(0);
        }
        execlp("xterm","xterm","-e","./parmax",argv[1],NULL);
        exit (0);
//or even return(0) works
}
