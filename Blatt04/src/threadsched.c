#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
#include <math.h>
#include <pthread.h>


void print_time_step (int time , int thread_num) { 
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

int main(int argc, char *argv[]) {

    list_t* li;

    if (( li = list_init()) == NULL)
    {
        printf ("Cannot allocate memory" );
        exit(-5);
    }

    int opt = 0;
    int iNparam = 10; // default
    int iTparam = 0; // default
    int iQparam = 0; // default
    int iAlgorithm = 0; // default

    while ((opt = getopt (argc, argv, "-n:-t:-q:-a:")) != -1) // diese Funktion verändert sich nicht
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
            if(atoi(optarg) <= 10 && atoi(optarg) > 0)
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
                iTparam = atoi(optarg);
            }
            else 
            {
                printf("TimneStep out of range.");
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
                iQparam = atoi(optarg);
            }
            else 
            {
                printf("Time Quantum out of range.");
                exit(-1);
            }
            break;
        case 'a':
            // algorithm
            // char* pChr = optarg;
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (*pChr == 'R' && *(pChr+1) == 'R') 
                {
                    iAlgorithm = 1; // Nummer 1 = Round Robin
                    break;
                }
                else if (*pChr == 'P' && *(pChr+1) == 'R' && *(pChr+2) == 'R') 
                {
                    iAlgorithm = 2; // Nummer 2 = Priority Round Robin
                    break;
                }
                else if (*pChr == 'S' && *(pChr+1) == 'R' && *(pChr+2) == 'T' && *(pChr+3) == 'N') 
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

    int thisThreadNumber = 1;
    
    for (int inputLine = 1; inputLine <= iNparam; inputLine++)
    {
        int iStringIterator = 0;
        char commandLineInput[100] = {0};
        gets(commandLineInput);

        // Prio
        char dummyPrioArray[5] = {0};
        int dummycharPrioArrayIterator = 0;
        while (commandLineInput[iStringIterator] != ' ')
        {
            dummyPrioArray[dummycharPrioArrayIterator] = commandLineInput[iStringIterator];
            dummycharPrioArrayIterator++;
            iStringIterator++;
        }
        int thisPrio = atoi(dummyPrioArray);
        iStringIterator++;

        // Startzeit
        char dummyStarttimeArray[10] = {0};
        int dummyStarttimeArrayIterator = 0;
        while (commandLineInput[iStringIterator] != ' ')
        {
            dummyStarttimeArray[dummyStarttimeArrayIterator] = commandLineInput[iStringIterator];
            dummyStarttimeArrayIterator++;
            iStringIterator++;
        }
        int thisStarttime = atoi(dummyStarttimeArray);
        iStringIterator++;

        // Laufzeit
        char dummyLaufzeitArray[10] = {0};
        int dummyLaufzeitArrayIterator = 0;
        while (commandLineInput[iStringIterator] != '\0')
            {
                dummyLaufzeitArray[dummyLaufzeitArrayIterator] = commandLineInput[iStringIterator];
                dummyLaufzeitArrayIterator++;
                iStringIterator++;
            }
        int thisLaufzeit = atoi(dummyLaufzeitArray);
        iStringIterator++;


        // Thread mit allen Attributen irgendwie in einer Liste speichern
        struct list_elem* thisThread = list_append_thread(li, thisThreadNumber, thisPrio, thisStarttime, thisLaufzeit);


        thisThreadNumber++;
        if (thisThreadNumber > iNparam) {
            break;
        }
    }




    // Hier kommt nun die Ausgabe bzw. die Implementierung der Algorithmen

    // Round Robin
    if (iAlgorithm == 1)
    {
        int time = 0;
        struct list_elem* currentThread = li->first;
        while(iNparam > 0){
            for (int iCounter = 1; iNparam >= iCounter; iCounter++) // Liste noch nicht leer
            {
                if(currentThread->iThreadStarttime <= time){ // Thread schon Vorhanden?
                    int iTimeQuantLeft = iQparam;
                    while(currentThread->iThreadLaufzeit > 0 && iTimeQuantLeft >= iTparam) // Thread noch nicht abgeschlossen & Quantum noch nicht abgelaufen
                    {
                        print_time_step(time, currentThread->iThreadNumber); // Ausgabe führende Nullen
                        time += iTparam; // Zeit läuft weiter
                        currentThread->iThreadLaufzeit -= iTparam; // Laufzeit nimmt ab
                    }    
                }
                if(currentThread->iThreadLaufzeit == 0) // Thread entfernen falls fertig
                {   
                    if(iCounter == iNparam)
                    {
                        struct list_elem* deleteable = currentThread;
                        currentThread = li->first;
                        list_remove_thread(li, deleteable);
                        iNparam -= 1;
                    }
                    else
                    {
                        struct list_elem* deleteable = currentThread;
                        currentThread = currentThread->next;
                        list_remove_thread(li, deleteable);
                        iNparam -= 1;
                    }
                }
                else // Zeiger weiter setzen
                {
                    if(iCounter == iNparam)// Ende der Liste?
                    {
                            struct list_elem* deleteable = currentThread;
                            currentThread = li->first;
                            list_remove_thread(li, deleteable);
                            iNparam -= 1;
                    }
                    else
                    {
                            struct list_elem* deleteable = currentThread;
                            currentThread = currentThread->next;
                            list_remove_thread(li, deleteable);
                            iNparam -= 1;
                    } 
                }
            }
        }
    }

    // Priority Round Robin
    else if (iAlgorithm == 2)
    {
        int time = 0;
        struct list_elem* currentThread = li->first;
        for(int currentPrio = 1; currentPrio <= 10; currentPrio++) // Prioritäten von 1 - 10 durchgehen
        {   
            for(int iCounter = 1; iCounter <= iNparam; iCounter++) // Listenelemente von 1 bis iNparam durchgehen
            {
                if(currentThread->iThreadPrio == currentPrio) // Thread hat entsprechende Prio
                {
                    while(currentThread->iThreadLaufzeit > 0)
                    {
                        int iTimeQuantLeft = iQparam;
                    
                        while(currentThread->iThreadLaufzeit > 0 && iTimeQuantLeft >= iTparam) // Thread noch nicht abgeschlossen & Quantum noch nicht abgelaufen
                            {
                                print_time_step(time, currentThread->iThreadNumber); // Ausgabe
                                time += iTparam; // Zeit läuft weiter
                                currentThread->iThreadLaufzeit -= iTparam; // Laufzeit nimmt ab
                            }
                    }
                    if(currentThread->iThreadLaufzeit == 0) // Thread entfernen falls fertig
                    {
                        if(iCounter == iNparam)// Nächstes Listenelement prüfen
                        {
                            struct list_elem* deleteable = currentThread;
                            currentThread = li->first;
                            list_remove_thread(li, deleteable);
                            iNparam -= 1;
                        }
                        else
                        {
                            struct list_elem* deleteable = currentThread;
                            currentThread = currentThread->next;
                            list_remove_thread(li, deleteable);
                            iNparam -= 1;
                        } 
                    }
                    else // Zeiger weiter setzen
                    {
                        if(iCounter == iNparam)// Nächstes Listenelement prüfen
                        {
                            struct list_elem* deleteable = currentThread;
                            currentThread = li->first;
                            list_remove_thread(li, deleteable);
                            iNparam -= 1;
                        }
                        else
                        {
                            struct list_elem* deleteable = currentThread;
                            currentThread = currentThread->next;
                            list_remove_thread(li, deleteable);
                            iNparam -= 1;
                        } 
                    }
                }
            }
            currentThread = li->first;
        }
    }

    // Shortest Remaining Time Next
    else if (iAlgorithm == 3)
    {
        
    }









    return 0;
}