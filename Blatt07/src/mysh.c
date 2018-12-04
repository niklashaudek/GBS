#include "list.h"
#include <unistd.h>

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
                printf("kid: %d | parent: %d\n", getpid(), getppid());

                // hier muss die Aufgabe implementiert werden

                char* envName = "PATH";
                char* env = getenv(envName); // Returns NULL if no variable with the given name exists

                if (env) {
                    printf("PATH: %s\n", env);
                }
                else {
                    printf("PATH: NULL\n");
                }

                list_t* pathElements = list_init();
                if ( pathElements == NULL)
                {
                    printf ("Cannot allocate memory for prozessListe" );
                    exit(-1);
                }

                char thisPathElement[50] = {0};
                int allPathElemCounter = 0;
                int pathElemCount = 0;
                for (int parsePath = 0; parsePath < strlen(env); parsePath++)
                {
                    if (env[parsePath] == ':')
                    {
                        struct list_elem* elem = list_append (pathElements, thisPathElement);
                        printf("elem: %s\n", elem->argument);
                        for (int i = 0; i < sizeof(thisPathElement); i++) thisPathElement[i] = '\0';
                        pathElemCount = 0;
                        allPathElemCounter++;
                    }
                    else
                    {
                        thisPathElement[pathElemCount] = env[parsePath];
                        pathElemCount++;
                    }
                }
                
                struct list_elem* thisPathElem = pathElements->first;
                for (int eachPath = 0; eachPath < allPathElemCounter; eachPath++)
                {
                    char* path = thisPathElem->argument;
                    char* args[] = {"ls", "-l", "/bin/", NULL}; // A list of arguments has to end with NULL
                    int result = execve(path, args, NULL); // Returns -1 on error
                    if(result == -1) {
                        perror("execve failed.");
                    }
                    thisPathElem = thisPathElem->next;
                }



                exit(1);
            }
        }

        if (getpid() == processIDparent)
        {
            struct list_elem* thisElem = prozessListe->first;
            while (thisElem != NULL)
            {
                printf("wait on kid and I'm parent: %d\n", getpid());
                waitpid(thisElem->processID, NULL, 0);
                thisElem = thisElem->next;
            }
        }

    }
}
