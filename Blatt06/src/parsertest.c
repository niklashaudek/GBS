#include "list.h"

list_t* parser(char cmdLineInput[], char *envp[]);


int main (int argc, char *argv[] , char *envp[] )
{
    while (1)
    {
        printf("$ ");

        char cmdLineInput[1024] = {0};
        fgets(cmdLineInput, 1024, stdin);

        list_t* li = parser(cmdLineInput, envp);

        struct list_elem* thisListElem = li->first;
        int elemCounter = 1;
        while (NULL != thisListElem)
        {
            char* consArg = thisListElem->argument;
            char* empty = "";
            
            if (strcmp(empty, consArg) != 0)
            {
                printf("%i:%s\n", elemCounter, consArg);
            }
            
            if (strcmp(consArg, "exit") == 0)
            {
                return 1;
            }

            elemCounter++;
            thisListElem = thisListElem->next;
        }

    }
}