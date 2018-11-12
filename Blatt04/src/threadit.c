#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "list.h"
#include <math.h>
#include <pthread.h>

static void* thread_func (void *arg) // Thread Routine
{     
    int *iTest = (int*) arg;
    for(int i = 1; i <= *iTest; i++ ){
    printf("%10u\t%d\t%ld\n", (unsigned int) pthread_self(), getpid(), (long) i); // Ausgabe vom Sheet nicht ändern
    }
    pthread_exit((void*) iTest);
    return arg;
}

int main(int argc, char *argv[]) {
    
    //int exitCode = 0;
    int newProcessId = 1;
    int processIDparent = getpid();

    list_t *li;

    int opt = 0;
    int iKparam = 10; // default
    int iNparam = 1;  // default
    int iRparam = 0;  // default

    while ((opt = getopt (argc, argv, "-k:-n:-r")) != -1) // diese Funktion verändert sich nicht
    {
        switch (opt)
        {
        case 'k':
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    printf ("Parameter K is no integer.");
                    exit (-1);
                }
            }
            iKparam = atoi(optarg);
            break;
        case 'n':
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    printf ("Parameter N is no integer.");
                    exit (-2);
                }
            }
            iNparam = atoi(optarg);
            break;
        case 'r':
            iRparam = 1;
            break;
        default:
            printf ("Error!");
            exit (-3);
        }
    }

    if( optind != argc )
    {
        printf ("Invalid Parameter!");
        exit (-4);
    }

        pthread_t threadStore[4];


    // Berechnung der random variable
    double upper = (double) iKparam * 1.5;
    double lower = (double) iKparam / 2;
    if(iRparam == 1){
        iKparam = (rand() % (int) (upper - lower + 1.0)) + lower; 
    }

    if (( li = list_init()) == NULL)
    {
        printf ("Cannot allocate memory" );
        exit(-5);
    }

    // Zeit Ausgabe
    time_t now;
	now = time(0);
	printf("Start: %s", ctime(&now));

    /*
    int iNumber = pthread_create(&mainThread, NULL, thread_func, &iKparam); // wie übergeben wir am Besten?
    if(iNumber != 0)
    {
        perror("Beim Erstellen des Threads ist ein Fehler aufgetreten.");
        exit(-1);
    }
    */
    
    for(int nIndex = 0; nIndex < iNparam; nIndex++){
        int threadNum = pthread_create(&threadStore[nIndex], NULL, thread_func, &iKparam);
        if(threadNum != 0)
        {
            perror("Thread creation went wrong.");
        }
        list_append(li, pthread_self());
        if(nIndex > 0)
        {
            pthread_join(threadStore[nIndex-1], NULL);
        }
    }
    
    /*
    for (int nIndex = 0; nIndex < iNparam; nIndex++)
    {
        if (getpid() == processIDparent)
        {
            newProcessPid = fork();
            if (newProcessPid > 0)
            {
                struct list_elem* pElement = list_append (li, newProcessPid);
            }
            if( newProcessPid == 0 )
            {
                for (int i = 1; i <= iKparam; i++)
                {
                    sleep(1);
                    printf("%d %d %d\n", getpid(), getppid(), i);
                }
            }
        }
    }
    */

    /* Exit Code wird nicht mehr gebraucht
    if (getpid() == processIDparent)
    {
        struct list_elem* thisElem = li->first;
        while (thisElem != NULL)
        {        
            waitpid(thisElem->data, NULL, 0);
            exitCode = (int) (thisElem->data+iKparam)%100;
            printf("Exit-Code: %d\n", exitCode);
            thisElem = thisElem->next;
        }
    }
    */

    if (getpid() == processIDparent)
    {
        now = time(0);
        printf("Ende: %s", ctime(&now));
    }

    exit(0);
}