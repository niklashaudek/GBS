#include <stdio.h> // For printf(...)
#include <unistd.h> // For fork()
#include <sys/wait.h> // For wait(...)
#include <unistd.h> // For sleep(...)

void exampleFork();
void exampleForkMulti();
void exampleZombie();
void exampleOrphan();

struct Test {
    int i;
};

#define T struct Test

/**
 * Starts a fork bomb: https://de.wikipedia.org/wiki/Forkbomb
 * 
 * MAKE SURE YOU SAVE ALL YOUR WORK BEFORE YOU RUN THIS!
 * USE AT YOUR OWN RISK!
 * 
 **/
void forkBomb();

int main(int argC, char** argV) {
    // exampleFork();
    // exampleForkMulti();
    // exampleZombie();
    // exampleOrphan();

    // Read method description first!!
    // forkBomb();
}

/**
 * A simple example for creating a child process and waiting for it.
 **/
void exampleFork() {
    int newProcessPid = fork();

    switch(newProcessPid) {
        case -1:
            perror ("fork () failed");
            break;

        case 0:
            printf("I'm your child! pid: %i, ppid: %i\n", getpid(), getppid());
            sleep(20);
            printf("Child finished.\n");
            break;

        default:
            printf("I am your father! pid: %i, ppid: %i\n", getpid(), getppid());
            waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
            printf("Child %i terminated.\n", newProcessPid);
            break;
    }
}

/**
 * How often will this method print "Hello world!\n"?
 * => 16 times
 **/
void exampleForkMulti() {
    // 1 process
    fork(); // 2 processes
    fork(); // 4 processes
    fork(); // 8 processes
    fork(); // 16 processes

    printf("Hello world!\n");
}

/** 
 * Example for creating a zombie process.
 * Command to list all Zombie processes for linux: ps aux | grep 'Z'
 **/
void exampleZombie() {
    int newProcessPid = fork();

    switch(newProcessPid) {
        case -1:
            perror ("fork () failed");
            break;

        case 0:
            printf("I'm your child! pid: %i, ppid: %i\n", getpid(), getppid());
            printf("Child finished.\n");
            break;

        default:
            printf("I am your father! pid: %i, ppid: %i\n", getpid(), getppid());
            sleep(20);
            waitpid(newProcessPid, NULL, 0);
            break;
    }
}

/**
 * Example for creating an orphan process.
 */
void exampleOrphan() {
    int newProcessPid = fork();

    switch(newProcessPid) {
        case -1:
            perror ("fork () failed");
            break;

        case 0:
            printf("I'm your child! pid: %i, ppid: %i\n", getpid(), getppid());
            sleep(2);
            printf("Child new pid: %i, ppid: %i\n", getpid(), getppid());
            sleep(20);
            printf("Child finished.\n");
            break;

        default: // Father terminates before the child
            printf("I am your father! pid: %i, ppid: %i\n", getpid(), getppid());
            printf("Father terminated\n");
            break;
    }
}