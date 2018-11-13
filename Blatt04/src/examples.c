#include <stdio.h> // For printf(...)
#include <pthread.h> // For thread stuff
#include <unistd.h> // For sleep(...)
#include <string.h> // For strcat(...)

void exampleThreadCreate();
void exampleThreadCreateShare();
void exampleThreadCancel();
void* exampleThreadBomb(void* data);
void exampleFileWrite();
void exampleFileRead();

void* exampleThreadMethod(void* data);

/**
 * Starts a fork bomb: https://de.wikipedia.org/wiki/Forkbomb
 * 
 * MAKE SURE YOU SAVE ALL YOUR WORK BEFORE YOU RUN THIS!
 * USE AT YOUR OWN RISK!
 * 
 **/
void forkBomb();

/**
 * To compile: gcc examples.c -o examples -pthread
 **/
int main(int argC, char** argV) {
    exampleThreadCreate();
    // exampleThreadCreateShare();
    // exampleThreadCancel();
    // exampleThreadBomb(NULL);
    
    // exampleFileWrite();
    // exampleFileRead();

    // Read method description first!!
    // forkBomb();
}

void* exampleThreadMethod(void* data) {
    char* s = (char*) data;
    printf("Hi, I'm thread %lu\n", pthread_self());
    sleep(2);
    strcat(s, " World!");
    printf("I (%lu) have done my work\n", pthread_self());
    return s;
}

/**
 * Creates a new thread and joins it.
 **/
void exampleThreadCreate() {
    printf("Hi, I'm the master thread %lu\n", pthread_self());

    pthread_t my_thread; // pthread_t is a synonym for "unsigned long"
    char s[] = "Hello";

    // Create new thread with entrypoint "&exampleThreadMethod" (address of "exampleThreadMethod"):
    int result = pthread_create(&my_thread, NULL, &exampleThreadMethod, s);
    if(result) {
        perror("pthread_create(...) failed");
        return;
    }
    printf("Thread %lu started\n", my_thread);

    void* sResult = NULL;
    // Allways join a thread to free the reserved memory again!
    // Wait for the created thread to finish and get return value:
    result = pthread_join(my_thread, &sResult);
    if(result) {
        perror("pthread_join(...) failed");
        return;
    }

    // Print return value:
    printf("Thread returned: %s\n", (char*)sResult);
}

void exampleThreadCreateShare() {
    printf("Hi, I'm the master thread %lu\n", pthread_self());

    pthread_t my_thread; // pthread_t is a synonym for "unsigned long"
    char s[] = "Hello";

    // Create new thread with entrypoint "&exampleThreadMethod" (address of "exampleThreadMethod"):
    int result = pthread_create(&my_thread, NULL, &exampleThreadMethod, s);
    if(result) {
        perror("pthread_create(...) failed");
        return;
    }
    printf("Thread %lu started\n", my_thread);

    result = pthread_join(my_thread, NULL);
    if(result) {
        perror("pthread_join(...) failed");
        return;
    }

    // Because threads share the same address space s contains now "Hello World":
    printf("Thread set s to: %s\n", s);
}

/**
 * An example of how to cancel a running thread.
 **/
void exampleThreadCancel() {
    printf("Hi, I'm the master thread %lu\n", pthread_self());

    pthread_t my_thread;
    char s[] = "Hello";

    int result = pthread_create(&my_thread, NULL, &exampleThreadMethod, s);
    if(result) {
        perror("pthread_create(...) failed");
        return;
    }
    printf("Thread %lu started\n", my_thread);

    // Cancel the thread before he is able to finish his tasks.
    // Canceled threads don't have to get joined with pthread_join(...)
    result = pthread_cancel(my_thread);
    if(result) {
        perror("pthread_cancel(...) failed");
        return;
    }

    printf("Thread set s to: %s\n", s);
}

/**
 * An example for a "Thread Bomb".
 * Creates threads until it reaches the thread limit for a single process on your system.
 * Use "Ctrl + C" to stop it again.
 **/
void* exampleThreadBomb(void* data) {
    pthread_t my_thread;
    int result;
    while(1) {
        result = pthread_create(&my_thread, NULL, exampleThreadBomb, NULL);
        if(result) {
            perror("pthread_create(...) failed");
        }
    }
}

/**
 * Example for writing to a file with a specific format.
 * Same as printf(...) but with file descriptor.
 **/
void exampleFileWrite() {
    FILE * fp;
    fp = fopen ("file.txt", "w+");
    fprintf(fp, "Hallo %i\n", 42);
    fclose(fp);
}

/**
 * Example for reading from a file descriptor in a specific format.
 **/
void exampleFileRead() {
    int i = 0;

    FILE* fp;
    fp = fopen ("file.txt", "r");
    fscanf(fp, "Hallo %i\n", &i); // Note: it will ignore "Hello " and reads only the int
    fclose(fp);

    printf("Read: i=%i\n", i);
}

/**
 * Starts a fork bomb: https://de.wikipedia.org/wiki/Forkbomb
 * 
 * MAKE SURE YOU SAVE ALL YOUR WORK BEFORE YOU RUN THIS!
 * USE AT YOUR OWN RISK!
 * 
 **/
void forkBomb() {
    while(1) {
        fork();
    }
}