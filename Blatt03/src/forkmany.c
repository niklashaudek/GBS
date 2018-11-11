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

    for( char* pChr = argv[1]; *pChr != 0; pChr++ )
    {
        if (isdigit(*pChr) == 0)
        {
            perror ("Parameter K is no integer.");
            exit (-2);
        }
    }

    time_t now;
	now = time(0);
	printf("Start: %s", ctime(&now));
    
    int k = atoi(argv[1]);

    // Bestimmen wie viele Kindprozesse es gibt: Eingabe in der Console als zweites drittes arg?
    int n = atoi(argv[2]);

    // List erstellen
    struct list = *list_init();

    // N Prozesse starten und in Liste speichern
    for(int i = 0; i < n; i++) {
        int newProcessPid = fork();
        *list_insert(list, newProcessPid);
    }
    
    int exitCode = (int) (newProcessPid+k)%100; // hier wird schon der Exit-Code berechnet


    switch(newProcessPid) {
            case -1:
                perror ("fork () failed");
                break;

            case 0:
                for (int i = 1; i <= k; i++)
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