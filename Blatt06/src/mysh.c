#include <stdio.h>
#include "list.h"
#include "list.c"
#include "parser.c"
#include <unistd.h>
#include <stdlib.h>

// Prozess forken
int newProcessPid = 1;
int exitCode = 0;
int processIDparent = getpid();


list_t *li;
list_t *list_init();


// Starten
newProcessPid = fork();
if(processIDparent == getpid()) 
{
    struct list_elem* pElement = list_append (li, newProcessPid);
}
if( newProcessPid == 0 )
{
    sleep(10);
    printf("%d %d \n", getpid(), getppid());
}

// Wieder Einfangen
if(processIDparent == getpid()) {
    struct list_elem* thisElem = li->first;
        while (thisElem != NULL)
        {        
            waitpid(thisElem->data, NULL, 0);
            exitCode = (int) (thisElem->data)%100;
            printf("Exit-Code: %d\n", exitCode);
            thisElem = thisElem->next;
        }
    }
}


// liste in array überführen
char* list_to_array(list_t* list) {

    int listSize = list->elementCount;

    if(listSize == 0) {
        printf("No element in list.\0");
        exit(-1);
    } else {
        char* cmdArray = ( char* ) malloc ( 1 * sizeof(char) );
    }
    
    for(int i = 0, i < listSize, i++) {        
        
        char* pElement = list->first->argument;
       // Wie finde ich raus wie viel char ein Element braucht?
        if(pElement != NULL) {
            for(int j = 0, j < sizeof(pElement), j++) 
            {
                
                cmdArray[i][j] = ( char* ) realloc ( i * sizeof(char) );
            }
        }

        // charArray groß mit charArray klein erweitern
        
    }



}



// Ausführung execve(file, argv, envp)
execve()

