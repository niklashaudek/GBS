#include "list.h"
//#include <unistd.h>

// liste in array überführen
char** list_to_array(list_t* list) {

    int arraySize = (list->größe) + 1;

    if(arraySize == 0) 
    {
        printf("No element in list.\n");
        exit(-1);
    }

    char** cmdArray = (char**) malloc((arraySize) * sizeof(char*));

    struct list_elem* pElement = list->first;

    for (int arrayIndex = 0; arrayIndex < arraySize; arrayIndex++)
    {
        if (NULL != pElement)
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
    while (1)
    {
        printf("$ ");

        char cmdLineInput[1024] = {0};
        fgets(cmdLineInput, 1024, stdin);

        list_t* cmdLineGeparst = parser(cmdLineInput, envp);

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

        list_t* prozessListe = list_init();
        if (( prozessListe = list_init()) == NULL)
        {
            printf ("Cannot allocate memory for prozessListe" );
            exit(-1);
        }

        int newProcessPid = 1;
        int processIDparent = getpid();

        if (getpid() == processIDparent)
        {
            newProcessPid = fork();
            if (newProcessPid > 0)
            {
                struct list_elem* pElement = list_append_processID (prozessListe, newProcessPid);
            }
            if( newProcessPid == 0 )
            {
                // irgendwas
            }
        }
/*
        switch(newProcessPid) {
                case -1:
                    perror ("fork () failed");
                    break;

                case 0:
                
                    int test = execve(NULL, parseArray, envp);
                    if (test == -1)
                    {
                        exit (-1);
                    }
                
                    break;
                default:
                    waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
                    break;
        }
*/
    }
}
