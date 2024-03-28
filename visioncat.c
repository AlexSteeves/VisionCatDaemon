#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>

#define EXT_SUCCESS 0
#define EXT_ERR_TOO_FEW_ARGS 1
#define EXT_ERR_INIT_INOTIFY 2

int IeventQueue = 1;
int main(int argc, char** argv){

    char *basePath = NULL;
    char *token = NULL;

    if(argc < 2){
        fprintf(stderr, "Usage: visioncat Path\n");
        exit(EXT_ERR_TOO_FEW_ARGS);
    }

    //Dynamic memory allocation
    //Malloc allocated an amount of memory on the heap
    //Strings in C are terminated with a null character
    basePath = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));

    strcpy(basePath, argv[1]);


    token = strtok(basePath, "\\");
    while(token != NULL){
        basePath = token;
        token = strtok(NULL, "\\");
    }

    IeventQueue = inotify_init();
    if(IeventQueue == -1){
        fprintf(stderr, "Error initialising inotify intance!\n");
        exit(EXT_ERR_INIT_INOTIFY);
    }
    //Run the Daemon forever
    while(true){
        a = read(basePath);

    }

    printf("%s\n", basePath);


    exit(EXIT_SUCCESS);
}

