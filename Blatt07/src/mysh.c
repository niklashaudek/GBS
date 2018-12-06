#include "list.h"
#include <unistd.h>
#include <fcntl.h> // For open(...)

// liste in array überführen
char** list_to_array(list_t* list) {

    int arraySize = list->size;
    arraySize++;

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
   
    return cmdArray;
}

// Funktionen nennen, damit sie unten verwendet werden können
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

        // Das hier sind Testausgaben

        /*
        printf("Array nach Parse:\n");
        for (int arrayTest = 0; arrayTest <= cmdLineGeparst->size; arrayTest++)
        {
            printf("%i: %s\n", arrayTest, parseArray[arrayTest]);
        }
        */


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
                list_append_processID (prozessListe, newProcessPid);
            }
            if( newProcessPid == 0 )
            {
                // das ist für den Fall in dem das Kommando schon einen Slash enthält,
                // und wir daher den PATH nicht mehr evaluieren müssen
                if ('/' == parseArray[0][0])
                {
                    char* command = parseArray[0];
                    parseArray[0] = "";
                    int result = execve(command, parseArray, NULL); // Returns -1 on error
                    if(result == -1)
                    {
                        perror("execve failed.");
                    }
                    exit(1);
                }

                char* envPath = getenv("PATH"); // Returns NULL if no variable with the given name exists
                if(envPath == NULL)
                {
                    perror("There exists no PATH variable.");
                    exit(-4);
                }
                // printf("PATH: %s\n", envPath);

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
                        charSinglePath[singlePathCounter] = envPath[pathCounter];
                        charSinglePath = buildingStringErweitern(charSinglePath, strlen(charSinglePath));
                        singlePathCounter++;
                    }
                    else 
                    {
                        charSinglePath[singlePathCounter] = '/';
                        charSinglePath = buildingStringErweitern(charSinglePath, strlen(charSinglePath));
                        singlePathCounter++;
                        int x = 0;
                        while('\0' != parseArray[0][x])
                        {
                            charSinglePath[singlePathCounter] = parseArray[0][x];
                            charSinglePath = buildingStringErweitern(charSinglePath, strlen(charSinglePath));
                            singlePathCounter++;
                            x++;
                        }
                        arrayPathElements[pathElementCounter] = charSinglePath;
                        charSinglePath = buildingStringErweitern(NULL, 0);
                        pathElementCounter++;
                        singlePathCounter = 0;
                    }
                    pathCounter++;
                }
                arrayPathElements[pathElementCounter] = charSinglePath;

                // erstes Element aus parseArray löschen, weil unser Tutor das auch so gemacht hat
                parseArray[0] = "";


                // Das hier sind Testausgaben

                /*
                printf("Array ohne leading Command:\n");
                for (int arrayTest = 0; arrayTest <= cmdLineGeparst->size; arrayTest++)
                {
                    printf("%i: %s\n", arrayTest, parseArray[arrayTest]);
                }
                
                for (int cnt = 0; cnt < pathElementCounter; cnt++)
                {
                    printf("pathArrayElement: %s\n", arrayPathElements[cnt]);
                }
                */


                // hier kommt nun die Behandlung von < oder >
                int idx = 0;
                for (int argCounter = 0; argCounter < cmdLineGeparst->size; argCounter++)
                {
                    if ('<' == parseArray[argCounter][idx]) // lesen aus Datei
                    {
                        while('\0' != parseArray[argCounter][idx])
                        {
                            parseArray[argCounter][idx] = parseArray[argCounter][idx+2];
                            idx++;
                        }
                        close(0); // close STDIN
                        int fd = open(parseArray[argCounter], O_WRONLY | O_CREAT, 0644); // Create file if not existing with rights 0644
                        if(fd <= 0) {
                            perror("Failed to open file \"FILE POINTER\"");
                            return;
                        }
                        idx = 0;
                    }
                    else if ('>' == parseArray[argCounter][idx]) // schreiben in Datei
                    {
                        while('\0' != parseArray[argCounter][idx])
                        {
                            parseArray[argCounter][idx] = parseArray[argCounter][idx+2];
                            idx++;
                        }
                        close(1); // close STDOUT
                        int fd = open(parseArray[argCounter], O_RDONLY | O_CREAT, 0644); // Create file if not existing with rights 0644
                        if(fd <= 0) {
                            perror("Failed to open file \"FILE POINTER\"");
                            return;
                        }
                        idx = 0;
                    }
                }


                for (int argument = 0; argument < pathElementCounter; argument++)
                {
                    int result = execve(arrayPathElements[argument], parseArray, NULL); // Returns -1 on error
                    if(result == -1)
                    {
                        perror("execve failed.");
                    }
                }

                exit(1);
            }
        }

        if (getpid() == processIDparent)
        {
            struct list_elem* thisElem = prozessListe->first;
            while (thisElem != NULL)
            {
                // printf("Wait on kid and I'm parent: %d\n", getpid());
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