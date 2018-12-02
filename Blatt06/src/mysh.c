#include <stdio.h>
#include "list.h"
#include "list.c"
#include "parser.c"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// liste in array überführen
char** list_to_array(list_t* list) {

    int listSize = list->elementCount;

    if(listSize == 0) 
    {
        printf("No element in list.\n");
        exit(-1);
    }
    char** cmdArray  = (char**) malloc((listSize + 1) * sizeof(char*));

    int arrayCounter = 0;

    struct list_elem* pElement = list->first;
    char* pElementArgument = pElement->argument;
        
    while (pElement != NULL)
    {
        * (cmdArray + arrayCounter) = pElementArgument;
        arrayCounter++;
        pElement = pElement->next;
        pElementArgument = pElement->argument;
    }

    printf("arrayCounter: %i und listSize: %i\n", arrayCounter, listSize);
    * (cmdArray + arrayCounter) = NULL;
   
    return cmdArray;

}



int main(int argc, char **argv, char *envp[])
{
    list_t* cmdLineGeparst = list_init();
    if (( cmdLineGeparst = list_init()) == NULL)
    {
        printf ("Cannot allocate memory.\n");
        exit(-5);
    }

    while (1)
    {
        printf("$ ");

        char cmdLineInput[1024] = {0};
        fgets(cmdLineInput, 1024, stdin);

        cmdLineGeparst = parser(cmdLineInput, envp);

        struct list_elem* thisListElem = cmdLineGeparst->first;
        int elemCounter = 1;
        while (NULL != thisListElem)
        {
            char* consArg = thisListElem->argument;
            char* empty = "";
            /*
            if (strcmp(empty, consArg) != 0)
            {
                printf("%i:%s\n", elemCounter, consArg);
            }
            */
            
            if (strcmp(consArg, "exit") == 0)
            {
                return 1;
            }

            elemCounter++;
            thisListElem = thisListElem->next;
        }
    }
    
    char** parseArray = list_to_array(cmdLineGeparst);
    printf("Erstes Element: %s\n Zweites Element: %s", *(parseArray), *(parseArray+1));

    int newProcessPid = fork();
    /*
    if(processIDparent == getpid()) 
    {
        struct list_elem* pElement = list_append_processID (li, newProcessPid);
    }
    */

    switch(newProcessPid) {
            case -1:
                perror ("fork () failed");
                break;

            case 0:
                for (int i = 1; i <= 10; i++)
                {
                    sleep(1);
                    printf("%d %d %d\n", getpid(), getppid(), i);
                }
                break;
            default:
                waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
                break;
        }


    if( newProcessPid == 0 )
    {
        sleep(10);
        printf("%d %d \n", getpid(), getppid());
    }

    // Wieder Einfangen
    /*
    if(processIDparent == getpid()) 
    {
        struct list_elem* thisElem = li->first;
        while (thisElem != NULL)
        {        
            waitpid(thisElem->argument, NULL, 0);
            //exitCode = (int) (thisElem->argument)%100;
            // printf("Exit-Code: %d\n", exitCode);
            thisElem = thisElem->next;
        }
    }
    */





    // Ausführung execve(file, argv, envp)
    //execve();
    }
