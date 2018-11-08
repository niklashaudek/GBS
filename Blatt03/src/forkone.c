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
    pthread_t thread;
    void *res; 

    int ret = pthread_create(&thread, NULL, set_time, "hello world");

    if (ret != 0) fprintf(stderr, "Error: Cannot start thread\n"); 
//Wait for thread
    ret = pthread_join(thread, &res); 
    
    if (ret != 0) fprintf(stderr, "Error: Cannot join thread\n");

    printf("Thread returned %ld\n",(long)res);
    //Threads beenden sich mit Ende der main automatisch
}

