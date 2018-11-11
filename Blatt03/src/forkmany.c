#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "list.h"

int main(int argc, char *argv[]) {

    int opt = 0;
    int iKparam = 10; // default
    int iNparam = 1;  // default
    int iRparam = 0;  // default

    opterr = 0; // wofür?

    while ((opt = getopt (argc, argv, "-k:-n:-r")) != -1)
    {
        switch (opt)
        {
        case 'k':
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    perror ("Parameter K is no integer.");
                    exit (-2);
                }
            }
            iKparam = atoi(optarg);
            break;
        case 'n':
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    perror ("Parameter N is no integer.");
                    exit (-3);
                }
            }
            iNparam = atoi(optarg);
            break;
        case 'r':
            iRparam = 1;
            break;
        default:
            abort();
        } // wofür?
    }


    // Bis hier her funktiert alles

/*
    int iRandom = (double) iKparam;
    if(iRparam == 1){ // muss noch gestestet werden oder vereinfacht 
        double iPlaceholder = 1.5 * iRandom;
        iRandom = (rand () % ((iPlaceholder + 1) - (iKparam/2)) + (iKparam/2); // wie machen wir *1.5?
        iKparam = iRandom;
    }
*/

    time_t now;
	now = time(0);
	printf("Start: %s", ctime(&now));


    // Kindprozesse erzeugen und in Liste speichern
    int newProcessPid = 0;
    list_t *li;
    li->first = NULL;
    li->last = NULL;
    for (int nIndex = 0; nIndex < (sqrt(iNparam)); nIndex++)
    {
        if (newProcessPid == 0)
        {
            newProcessPid = fork();
        }
        if (( li = list_init()) == NULL)
        {
            perror ("Cannot allocate memory " );
            exit(1);
        }

        list_append (li, &newProcessPid);
    }



    // int exitCode = (int) (newProcessPid + iKparam) % 100; // hier wird schon der Exit-Code berechnet

    switch(newProcessPid) {
            case -1:
                perror ("fork () failed");
                break;
            case 0:
                for (int i = 1; i <= iKparam; i++)
                // for (int i = 1; i <= k; i++) - change from k to iK
                for (int i = 1; i <= iKparam; i++)
                {
                    sleep(1);
                    printf("%d %d %d\n", getpid(), getppid(), i);
                }
                break;
            default:
                // printf("vor wait\n");
                waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
                // printf("Exit-Code: %d\n", exitCode); 
                now = time(0);
	            printf("Ende: %s", ctime(&now));
                break;
        }
}