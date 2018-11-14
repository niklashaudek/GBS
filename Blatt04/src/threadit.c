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

static void* thread_func (void* data) // Thread Routine
{
    int* threadKvalue = (int*) data;
    for(int i = 1; i <= *threadKvalue; i++ )
    {
        printf("%10u\t%d\t%ld\n", (unsigned int) pthread_self(), getpid(), (long) i); // Ausgabe vom Sheet nicht ändern
        sleep(1);
    }
    // long unsigned threadId = pthread_self();
    // printf("Meine ThreadID ist: %lu\n", threadId);
    pthread_exit((void*) threadKvalue);
    return data;
}

int main(int argc, char *argv[]) {
    
    //int exitCode = 0;
    int newProcessId = 1;
    int threadIDparent = (int) pthread_self();

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

    pthread_t threadStore[iNparam];


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

    
    for(int nIndex = 0; nIndex < iNparam; nIndex++){
        pthread_t my_thread;
        int threadNum = pthread_create(&my_thread, NULL, &thread_func, &iKparam);
        if(threadNum) {
            perror("pthread_create(...) failed");
            return -1;
        }
        list_append(li, my_thread);
    }

    void* sResult = NULL;
    for(int nIndex = 0; nIndex < iNparam; nIndex++)
    {
        pthread_t thisThreadID = 0;
        struct list_elem* threadElem = li->first;
        if (nIndex == 0)
        {
            thisThreadID = threadElem->data;
        }
        else
        {
            for (int listIDX = 0; listIDX < nIndex; listIDX++)
            {
                threadElem = threadElem->next;
            }
            thisThreadID = threadElem->data;
        }
        int result = pthread_join(thisThreadID, &sResult);
        if(result) {
            perror("pthread_join(...) failed");
            return -1;
        }
    }

    now = time(0);
    printf("Ende: %s", ctime(&now));

    return 0;
}