#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <list.h>
#include <list.c>

int main(int argc, char *argv[]) {
    
    // von forkone übernommen
    if (argc < 2)
    {
        perror ("Missing parameter K.");
        exit (-1);
    }

/*
    for (int idx = 0; idx < strlen(argv[1]); idx++)
    {
        if (isdigit(argv[1][idx]) == 0)
        {
            perror ("Parameter K is no integer.");
            exit (-2);
        }
    }
*/
    // Was wird hier gemacht?
       extern char *optarg;
       extern int optind, opterr, optopt;
       int iN = 1; // default
       int iK = 10; // default
       int iR = -1; // default
       int opt = 0; // gibt -1 aus wenn kein Argument mehr vorhanden ist

    while((opt = getopt(argc, argv, "nkr:")) != -1){
        switch(opt){
        case 'n': iN = atoi(optarg); // müssen wir hier prüfen ob die Eingabe sinnvoll war ?

        case 'k': iK = atoi(optarg);

        case 'r': iR = 0;

        default: perror("Something went wrong"); break;
    }
    }

    printf("%i, %i, %i", iN, iK, iR); // Test
   
   /* 
   // von forkone
   for( char* pChr = argv[1]; *pChr != 0; pChr++ )
    {
        if (isdigit(*pChr) == 0)
        {
            perror ("Parameter K is no integer.");
            exit (-2);
        }
    }
    */

    
   int iRand = 0;
    if(iR == 0){
        double iPlaceholder = 1.5 * (double) iK;
        iRand = (rand () % ((((int) iPlaceholder * iK) + 1) - (iK/2))) + (iK/2); // wie machen wir *1.5?
        iK = iRand;
    }

    // Liste erstellen
    list_t list;
    list.first = NULL;
    list.last = NULL;


    time_t now;
	now = time(0);
	printf("Start: %s", ctime(&now));
    
    int k = atoi(argv[1]);

/*
    // Consti
    // Bestimmen wie viele Kindprozesse es gibt: Eingabe in der Console als drittes arg?
    int n = atoi(argv[2]);

    // Liste erstellen
    struct list = *list_init();

    // N Prozesse starten und in Liste speichern
    for(int i = 0; i < n; i++) {
        int newProcessPid = fork();
        *list_insert(list, newProcessPid);
    }
    
    int exitCode = (int) (newProcessPid+k)%100; // hier wird schon der Exit-Code berechnet
*/

    // int k = atoi(argv[1]); k wird bei getopt geparst

    // von forkone
    int newProcessPid = fork();
    
    int exitCode = (int) (newProcessPid + iK) % 100; // hier wird schon der Exit-Code berechnet

    switch(newProcessPid) {
            case -1:
                perror ("fork () failed");
                break;

            case 0:
                // for (int i = 1; i <= k; i++) - change from k to iK
                for (int i = 1; i <= iK; i++)
                {
                    sleep(1);
                    printf("%d %d %d\n", getpid(), getppid(), i);
                }
                break;
            default:
                // printf("vor wait\n");
                waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
                printf("Exit-Code: %d\n", exitCode); 
                now = time(0);
	            printf("Ende: %s", ctime(&now));
                break;
        }
}
