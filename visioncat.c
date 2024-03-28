#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>



#include<windows.h>





#define EXT_SUCCESS 0
#define EXT_ERR_TOO_FEW_ARGS 1


int IeventQueue = 1;


int main(int argc, char** argv){

  
    //Check if there are enough arguments
    if(argc < 2){
        fprintf(stderr, "Usage: visioncat Path\n");
        exit(EXT_ERR_TOO_FEW_ARGS);
    }

    //Dynamic memory allocation
    //Malloc allocated an amount of memory on the heap
    //Strings in C are terminated with a null character
    char* directoryToWatch = argv[1];

    HANDLE hDirectory = FindFirstChangeNotificationA(
        directoryToWatch, 
        FALSE, 
        FILE_NOTIFY_CHANGE_LAST_WRITE);

    if(hDirectory == INVALID_HANDLE_VALUE){
        fprintf(stderr, "Error: FindFirstChangeNotification failed.\n");
        exit(EXIT_FAILURE);
    }


    int numberOfChanges = 0;
    //Run the Daemon forever
    while(true){
    printf("Waiting for changes in %s\n", directoryToWatch);
    DWORD waitStatus = WaitForSingleObject(hDirectory, INFINITE);


    switch(waitStatus){
        case WAIT_OBJECT_0:
            numberOfChanges++;
            printf("Change detected in %s. This is the %dth change.\n", directoryToWatch, numberOfChanges);
            

            if(FindNextChangeNotification(hDirectory) == FALSE){
                fprintf(stderr, "Error: FindNextChangeNotification failed.\n");
                exit(EXIT_FAILURE);
            }
            break;

            default:
                fprintf(stderr, "Error: Unhandled wait status.\n");
                exit(EXIT_FAILURE);
                break;
        }
    }

    //Close the handle
    FindCloseChangeNotification(hDirectory);

    return EXT_SUCCESS;
}

