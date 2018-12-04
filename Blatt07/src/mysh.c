#include "list.h"
#include <unistd.h>
#include <pthread.h>

// liste in array überführen
char** list_to_array(list_t* list) {

    int arraySize = list->elementCount + 1;

    if(arraySize == 0) 
    {
        printf("No element in list.\n");
        exit(-1);
    }

    char** cmdArray = (char**) malloc((arraySize) * sizeof(char*));

    struct list_elem* pElement = list->first;

    for (int arrayIndex = 0; arrayIndex < arraySize; arrayIndex++)
    {
        if (pElement != NULL)
        {
            cmdArray[arrayIndex] = pElement->argument;
            pElement = pElement->next;
        }
        else if (arrayIndex != arraySize - 1)
        {
            perror("Fehler: Liste nicht richtig in Array kopiert!");
        }
    }

    cmdArray[arraySize-1] = NULL;

    for (int arrayTest = 0; arrayTest < arraySize; arrayTest++)
    {
        printf("%i: %s\n", arrayTest, cmdArray[arrayTest]);
    }
   
    return cmdArray;
}

list_t* parser(char cmdLineInput[], char *envp[]);

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
            
            if (strcmp(consArg, "exit") == 0)
            {
                return 1;
            }

            elemCounter++;
            thisListElem = thisListElem->next;
        }

        char** parseArray = list_to_array(cmdLineGeparst);
        // printf("Erstes Element: %s\n Zweites Element: %s", *(parseArray), *(parseArray+1));
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
                /*
                    int test = execve(NULL, parseArray, envp);
                    if (test == -1)
                    {
                        exit (-1);
                    }
                */
                    break;
                default:
                    waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
                    break;
        }
    }
}
