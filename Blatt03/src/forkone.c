#include <stdio.h>

static void* thread_func(void *arg) {
    char *s = (char *) arg;
    printf("Thread TID=%d says %s\n", pthread_self, s); 
    pthread_exit((void *)strlen(s));
    } 


int main(int argc, char 8 9
}

char 
argv[]) {
pthread_t thread; void int ret = pthread_create(&thread, NULL, thread_func,
*
res;
if (ret != 0)
fprintf(stderr, "Error: Cannot start thread\n"); Wait for thread
*
/
/
* ret = pthread_join(thread, &res); if (ret != 0)
fprintf(stderr, "Error: Cannot join thread\n");
printf("Thread returned %ld\n",(long)res);
exit(EXIT_SUCCESS);


