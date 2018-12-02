#include <stdio.h>
#include "list.h"
#include "list.c"
#include "parser.c"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// liste in array überführen
char* list_to_array(list_t* list) {

    int listSize = list->elementCount;

    if(listSize == 0) 
    {
        printf("No element in list.\n");
        exit(-1);
    }
    char* cmdArray  = ( char* ) malloc ((listSize + 1) * sizeof(char));

    // for(int iCounter = 0; iCounter < listSize; iCounter++) {        
    int listCounter = 1;

    char* pElement = list->first->argument;
    if(pElement != NULL) {
            cmdArray = pElement;
    }
        
    while(pElement->next != NULL) {
            pElement = pElement->next;
            cmdArray[listCounter] = pElement;
            listCounter++;
    }

    cmdArray[listSize] = NULL;


        
       // Wie finde ich raus wie viel char ein Element braucht?
        /*
        if(pElement != NULL) {
            for(int iNumber = 0; iNumber < sizeof(pElement); iNumber++) 
            {
                cmdArray[iCounter] = pElement;
                //cmdArray[i][j] = ( char* ) realloc ( iCounter * sizeof(char) );
            }
        }
        */
        // charArray groß mit charArray klein erweitern
    
}

// Prozess forken
// int newProcessPid = 1;

int main(int argc, char **argv) {

int exitCode = 0;
int processIDparent = NULL; // hier darf man noch kein getPid aufrufen


list_t *li;
list_t *list_init();


// Starten
int newProcessPid = fork();
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
if(processIDparent == getpid()) 
{
    struct list_elem* thisElem = li->first;
    while (thisElem != NULL)
    {        
        waitpid(thisElem->argument, NULL, 0);
        exitCode = (int) (thisElem->argument)%100;
        printf("Exit-Code: %d\n", exitCode);
        thisElem = thisElem->next;
    }
}






// Ausführung execve(file, argv, envp)
//execve();
}
