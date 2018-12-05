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
char* buildingStringErweitern (char* oldStr, int oldStrLen);

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

                char* envPath = getenv("PATH"); // Returns NULL if no variable with the given name exists
                if(envPath == NULL)
                {
                    perror("There exists no PATH variable.");
                    exit(-4);
                }
                printf("PATH: %s\n", envPath);

                // Array für die einzelenen Paths in der PATH Variable (maximal 10 möglich)
                char** arrayPathElements = (char**) malloc(10 * sizeof(char*));

                int pathCounter = 0;
                int pathElementCounter = 0;
                int singlePathCounter = 0;
                char* charSinglePath = buildingStringErweitern(NULL, 0);
                while ('\0' != envPath[pathCounter])
                {
                    if (':' != envPath[pathCounter])
                    {
                        printf("x :\n");
                        charSinglePath[singlePathCounter] = envPath[pathCounter];
                        charSinglePath = buildingStringErweitern(charSinglePath, strlen(charSinglePath));
                        singlePathCounter++;
                    }
                    else 
                    {
                        printf("-> :\n");
                        arrayPathElements[pathElementCounter] = charSinglePath;
                        pathElementCounter++;
                        charSinglePath = buildingStringErweitern(NULL, 0);
                    }
                    pathCounter++;
                }

                for (int cnt = 0; cnt < pathElementCounter; cnt++)
                {
                    printf("pathArrayElement: %s\n", arrayPathElements[cnt]);
                }
                for(int argumente = 0; argumente < pathCounter; argumente++)
                {
                   //printf("Hier müssen die execve() aufrufe passieren.:.");
                   // execve(arrayPathElements[argumente], );
                }

                exit(1);
            }
        }

        if (getpid() == processIDparent)
        {
            struct list_elem* thisElem = prozessListe->first;
            while (thisElem != NULL)
            {
                printf("Wait on kid and I'm parent: %d\n", getpid());
                waitpid(thisElem->processID, NULL, 0);
                thisElem = thisElem->next;
            }
        }
    }
}
/*
                struct list_elem* this = listPathElements->first;
                for (int parsePath = 0; parsePath < strlen(envPath); parsePath++)
                {
                    if (env[parsePath] == ':')
                    {
                        struct list_elem* elem = list_append (listPathElements, charThisPathElement);
                        printf("elem write: %s\n", elem->argument);
                        printf("elem read: %s\n", this->argument);
                        for (int i = 0; i < sizeof(charThisPathElement); i++) charThisPathElement[i] = '\0';
                        pathElemCount = 0;
                        intAllPathElemCounter++;
                        elem = this->next;
                    }
                    else
                    {
                        charThisPathElement[pathElemCount] = env[parsePath];
                        pathElemCount++;
                    }
                }
*/                
                // struct list_elem* thisPathElem = listPathElements->first;
                // char* path = thisPathElem->argument;
/*                for (int eachPath = 0; eachPath < intAllPathElemCounter; eachPath++)
                {
                    printf("This is the path before strcat(): %s\n", thisPathElem->argument);
                    strcat(thisPathElem->argument, "/");
                    strcat(thisPathElem->argument, parseArray[0]);
                    printf("This is the path after strcat(): %s\n", thisPathElem->argument);
                    //char* args[] = {"", "-l", "/bin/", NULL}; // A list of arguments has to end with NULL
                    int result = execve(thisPathElem->argument, parseArray+1, NULL); // Returns -1 on error
                    if(result == -1) {
                        perror("execve failed.");
                    }
                    thisPathElem = thisPathElem->next;
                }
*/