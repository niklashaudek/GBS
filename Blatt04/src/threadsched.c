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
            if(atoi(optarg) <= 10)
            {
                iNparam = atoi(optarg);
            }
            else 
            {
                printf("Number of threads out of range.");
                exit(-1);
            }
            break;
        case 't':
            // time step
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    printf ("Parameter N is no integer.");
                    exit (-1);
                }
            }
            if(atoi(optarg) <= 100000)
            {
                iNparam = atoi(optarg);
            }
            else 
            {
                printf("TimneStamp out of range.");
                exit(-1);
            }
            break;
        case 'q':
            // time quantum
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    printf ("Parameter N is no integer.");
                    exit (-1);
                }
            }
            if(atoi(optarg)<= 30000)
            {
                iNparam = atoi(optarg);
            }
            else 
            {
                printf("Time Quantum out of range.");
                exit(-1);
            }
            break;
        case 'a':
            // algorithm
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (strcmp( *pChr, 'R') == 0 && strcmp(*pChr + 1, 'R') == 0) 
                {
                    iAlgorithm = 1; // Nummer 1 = Round Robin
                    break;
                }
                else if (strcmp( *pChr, 'P') == 0 && strcmp(*pChr + 1, 'R') == 0 && strcmp( *pChr, 'R') == 0) 
                {
                    iAlgorithm = 2; // Nummer 2 = Priority Round Robin
                    break;
                }
                else if (strcmp( *pChr, 'P') == 0 && strcmp(*pChr + 1, 'R') == 0 && strcmp( *pChr + 2, 'R') == 0) 
                {
                    iAlgorithm = 3; // Nummer 3 = Shortest Remaining Time Next
                    break;
                }
                else 
                {
                    printf("Algorithm could not be found.");
                    exit(-1);
                }
            }
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

    void    print_time_step ( int time , int thread_num) { 
        static int first_time = 1;
        int i;
        
        if (first_time) 
        {
            printf (" Time | 1 2 3 4 5 6 7 8 9 10\n"); 
            printf ("−−−−−−−+−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n " ); 
            first_time = 0;
        }
        printf ("%06d |", time); 
        
        if ( thread_num ) 
        {
            for (i = 1; i < thread_num; i++)  
            {  
                printf (" ");
            }
            printf (" %d\n" , thread_num); 
        } 
        else
        {
            printf ("\n");
        }
    }

    // now = time(0);
    // printf("Ende: %s", ctime(&now));

    return 0;
}