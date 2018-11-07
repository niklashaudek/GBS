#include <stdio.h>
#include <pthread.h>
#define EXIT_SUCCESS 0

static void* thread_func(void *arg) {
    
    time_t now; 
	now = time(0);
	printf("%s\n", ctime(&now)); // unsicher aus dem Internet
    int count = scanf("%i", &count);
    char *s = (char *) arg;
    printf("Thread TID=%d says %s\n", pthread_self, s); 
    pthread_exit((void *)strlen(s));
    } 


int main(int argc, char argv[]) {
    pthread_t thread; 
    void *res; 
    int ret = pthread_create(&thread, NULL, thread_func, "hello world");

if (ret != 0) fprintf(stderr, "Error: Cannot start thread\n"); 
//Wait for thread
ret = pthread_join(thread, &res); 
if (ret != 0) fprintf(stderr, "Error: Cannot join thread\n");

printf("Thread returned %ld\n",(long)res);

exit(EXIT_SUCCESS);
}

