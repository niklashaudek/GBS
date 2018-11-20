#define _GNU_SOURCE

#include <stdio.h> // For printf(...) and sprintf(...)
#include <pthread.h> // For thread stuff
#include <stdlib.h> // For malloc(...)

void thread_func (char* string) {
    printf("Hello, my name is %s!\n", string);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    const char* names[5] = { "up", "you", "give", "gonna", "never" };

}