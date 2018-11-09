#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// static void* set_time(void *arg) {
    
//     time_t now;
// 	    now = time(0);
// 	    printf("Start: %s", ctime(&now)); // fertig, Datum funktioniert, nichts ändern
//     //while schleife und sleep mit jeweils einer Sekunde Abstand fehlen noch
//     pid_t pid = getpid(); // process id
//     printf("%d %d\n", pid, pid -1);
//     void *t;
//     return t;
//     } 


int main(int argc, char *argv[]) {
    
    time_t now;
	now = time(0);
	printf("Start: %s", ctime(&now));
    
    int newProcessPid = fork();

    // hier muss Eingabe auf Integer geprüft werden
    // if ()
    // int k = (int*) argv[1];
    
    int k = 10;

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
                waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
                printf("Exit-Code: %d\n", exitCode);
                now = time(0);
	            printf("Ende: %s", ctime(&now));
                break;
        }
}
