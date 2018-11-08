#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

static void* set_time(void *arg) {
    
    time_t now;
	now = time(0);
	printf("Start: %s", ctime(&now)); // fertig, Datum funktioniert, nichts ändern
    
    //while schleife und sleep mit jeweils einer Sekunde Abstand fehlen noch
    
    pid_t pid = getpid(); // process id
    printf("%d %d\n", pid, pid -1);
    void *t;
    return t;
    } 


int main(int argc, char *argv[]) {
    
    int newProcessPid = fork();
    // hier muss Eingabe auf Integer geprüft werden
    // if ()
    // int k = (int*) argv[1];
    int k = 10;

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
                printf("Exit-Code: &d\n", (((int) getpid())+k)%100);
                waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
                printf("Child %i terminated.\n", newProcessPid);
                break;
        }

    

    // Diese Lösung ist mit Threads, aber wir sollen doch die Prozesse forken, das ist ein Unterschied


    /*
    pthread_t thread;
    void *res; 

    int ret = pthread_create(&thread, NULL, set_time, "hello world");

    if (ret != 0) fprintf(stderr, "Error: Cannot start thread\n"); 
//Wait for thread
    ret = pthread_join(thread, &res); 
    
    if (ret != 0) fprintf(stderr, "Error: Cannot join thread\n");

    printf("Thread returned %ld\n",(long)res);
    //Threads beenden sich mit Ende der main automatisch
    */

}

