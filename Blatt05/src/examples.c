#include <stdio.h> // For printf(...) and sprintf(...)
#include <pthread.h> // For thread stuff
#include <fcntl.h> // For open(...)
#include <unistd.h> // For close(...) and write(...)
#include <stdlib.h> // For malloc(...)

void examplePthreadNoMutex();
void examplePthreadMutex();
void exampleFileWrite();
void example_sprintf();

void* exampleThreadMethodNoMutex(void* data);
void* exampleThreadMethodMutex(void* data);

/**
 * To compile: gcc examples.c -o examples -pthread
 **/
int main(int argC, char** argV) {
    // examplePthreadNoMutex();
    // examplePthreadMutex();

    exampleFileWrite();
    // example_sprintf();
}

/**
 * Entrypoint for threads created in examplePthreadNoMutex().
 **/
void* exampleThreadMethodNoMutex(void* data) {
    int* i = (int*) data;

    while(1) {
        if(*i >= 10000000) { // Run while i is lower than 10 million
            break;
        }
        int j = *i; // Slip up incrementing i into two steps, because i++ would be a atomic operation in C.
        *i = j + 1;
    }
    printf("i is %i\n", *i);
    return NULL;
}

/**
 * An example for creating 10 threads working on the same critical area, NOT protected by a mutex.
 **/
void examplePthreadNoMutex() {
    // Allocate space for 10 threads:
    pthread_t threads[10];
    int i = 0;

    // Start all threads:
    for (int e = 0; e < 10; e++) {
        int result = pthread_create(threads + e, NULL, &exampleThreadMethodNoMutex, &i); // Same as &threads[e]
        if(result) {
            perror("pthread_create(...) failed");
            return;
        }
        printf("Started thread %i\n", e);
    }

    // Join all threads:
    for (int e = 0; e < 10; e++) {
        int result = pthread_join(threads[e], NULL);
        if(result) {
            perror("pthread_join(...) failed");
            return;
        }
        printf("Joined thread %i\n", e);
    }

    printf("i: %i\n", i);
}

struct Container {
    int i;
    pthread_mutex_t mutex;
};

/**
 * Entrypoint for threads created in exampleThreadMethodMutex().
 **/
void* exampleThreadMethodMutex(void* data) {
    struct Container* cont = (struct Container*) data;

    while(1) {
        pthread_mutex_lock(&cont->mutex); // Let only one thread at the time increment i:
        if(cont->i >= 10000000) { // Run while i is lower than 10 million
            pthread_mutex_unlock(&cont->mutex);
            break;
        }
        int j = cont->i;
        cont->i = j + 1;
        pthread_mutex_unlock(&cont->mutex);
    }
    printf("i is %i\n", cont->i);
    return NULL;
}

/**
 * An example for creating 10 threads working on the same critical area, protected by a mutex.
 **/
void examplePthreadMutex() {
    // Allocate space for 10 threads:
    pthread_t threads[10];

    // Create a Container struct that holds our int and mutex, because pthread_create(...) accepts only one argument:
    struct Container* cont = malloc(sizeof(struct Container));
    cont->i = 0;
    pthread_mutex_init(&cont->mutex, NULL);

    // Start all threads:
    for (int e = 0; e < 10; e++) {
        int result = pthread_create(threads + e, NULL, &exampleThreadMethodMutex, cont); // Same as &threads[e]
        if(result) {
            perror("pthread_create(...) failed");
            return;
        }
        printf("Started thread %i\n", e);
    }

    // Join all threads:
    for (int e = 0; e < 10; e++) {
        int result = pthread_join(threads[e], NULL);
        if(result) {
            perror("pthread_join(...) failed");
            return;
        }
        printf("Joined thread %i\n", e);
    }

    // Once done destroy mutex again:
    pthread_mutex_destroy(&cont->mutex);

    printf("i: %i\n", cont->i);
}

/**
 * An example that opens the file "file.txt" and writes "Hallo 42\n" into it.
 **/
void exampleFileWrite() {
    int fd = open("file.txt", O_WRONLY | O_CREAT); // Open the file in write only and create it if it does not exist.
    if(fd <= 0) { // On success open(...) returns a file descriptor greater than zero.
        perror("Failed to open file \"file.txt\"");
        return;
    }
    char* text = "Hallo 42\n";
    write(fd, text, 9); // Write text into file.
    close(fd); // Close file again and free the file descriptor.
}

/**
 * Example for the use of sprintf(...).
 * Instead of printing to a file descriptor (stdout, stdin, ...) we print the result into a given string.
 **/
void example_sprintf() {
    char* text = "Hallo world!";
    char s[12 + 1 + 1]; // Allocate memory for 14 chars (12 for "Hello world", 1 for \n, 1 for \0)
    sprintf(s, "%s\n", text);

    printf("%s", s);
}