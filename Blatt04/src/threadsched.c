#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
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

    list_t *li;

    if (( li = list_init()) == NULL)
    {
        printf ("Cannot allocate memory" );
        exit(-5);
    }

    int opt = 0;
    int iNparam = 10; // default

    int iAlgorithm = 0; // default

    while ((opt = getopt (argc, argv, "-n:-t:-q:-a")) != -1) // diese Funktion verändert sich nicht
    {
        switch (opt)
        {
        case 'n':
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    printf ("Parameter N is no integer.");
                    exit (-1);
                }
            }
            iNparam = atoi(optarg);
            break;
        case 't':
            // time step
            break;
        case 'q':
            // time quantum
            break;
        case 'a':
            // algorithm
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



    // hier kommt der wichtigste Teil:
    // das korrekte Einlesen aus der STDIN

    // die länge des char arrays sollte so angepasst werden, dass der die Eingabe auf ihm platz findet (zum beispiel durch eine Rechnung oder so)
    // int arrayLength = ;
    char str[1000] = {0};
    gets(str);
    int iStringIterator = 0;
    /*
    int lengthCounter = 0;
    while (str[iStringIterator] != '\0')
    {
        lengthCounter++;
    }
    iStringIterator = 0;
    */
    int threadNumber = 1;
    
    while (1)
    {
        while (str[iStringIterator] != '\n')
        {
            // Prio
            char dummyPrioArray[5] = {0};
            int dummycharPrioArrayIterator = 0;
            while (str[iStringIterator] != ' ')
            {
                dummyPrioArray[dummycharPrioArrayIterator] = str[iStringIterator];
                dummycharPrioArrayIterator++;
                iStringIterator++;
            }
            int thisPrio = atoi(dummyPrioArray);
            // mit thisPrio was machen!!
            iStringIterator++;

            // Startzeit
            char dummyStarttimeArray[10] = {0};
            int dummyStarttimeArrayIterator = 0;
            while (str[iStringIterator] != ' ')
            {
                dummyStarttimeArray[dummyStarttimeArrayIterator] = str[iStringIterator];
                dummyStarttimeArrayIterator++;
                iStringIterator++;
            }
            int thisStarttime = atoi(dummyStarttimeArray);
            // mit thisStarttime was machen!!
            iStringIterator++;

            // Laufzeit
            char dummyLaufzeitArray[10] = {0};
            int dummyLaufzeitArrayIterator = 0;
            while (str[iStringIterator] != '\n')
                {
                    dummyLaufzeitArray[dummyLaufzeitArrayIterator] = str[iStringIterator];
                    dummyLaufzeitArrayIterator++;
                    iStringIterator++;
                }
            int thisLaufzeit = atoi(dummyLaufzeitArray);
            // mit thisLaufzeit was machen!!
            iStringIterator++;


            // Thread mit allen Attributen irgendwie in einer Liste speichern


            threadNumber++;
            if (threadNumber > iNparam) {
                break;
            }
        }
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