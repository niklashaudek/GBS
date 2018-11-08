#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#define EXIT_SUCCESS 0

static void* thread_func(void *arg) {
    
    time_t now;
	now = time(0);
	printf("%s\n", ctime(&now)); // unsicher aus dem Internet
    void *t;
    return t;
    } 


int main(int argc, char *argv[]) {
    pthread_t thread;
    void *res; 
    int ret = pthread_create(&thread, NULL, thread_func, "hello world");

    if (ret != 0) fprintf(stderr, "Error: Cannot start thread\n"); 
//Wait for thread
    ret = pthread_join(thread, &res); 
    if (ret != 0) fprintf(stderr, "Error: Cannot join thread\n");

    printf("Thread returned %ld\n",(long)res);
    //Threads beenden sich mit Ende der main automatisch
}

