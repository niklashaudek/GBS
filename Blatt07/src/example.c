#include <stdio.h> // For printf(...) and sprintf(...)
#include <fcntl.h> // For open(...)
#include <string.h> // For strlen(...), ...
#include <unistd.h> // For dup(...) and dup2(...)
#include <unistd.h> // For fork()
#include <sys/wait.h> // For wait(...)
#include <unistd.h> // For sleep(...)

void exampleDup();
void exampleDup2();
void examplePipe();

int main(int argC, char** argV) {
    // exampleDup();
    // exampleDup2();
    examplePipe();
}

/**
 * Example for duplicating file descriptors.
 **/
void exampleDup() {
    int newFd = dup(STDOUT_FILENO); // Create a copy of the STDOUT_FILENO file descriptor
    if(newFd == -1) {
        perror("dup failed.");
    }
    else {
        printf("New file descriptor: %i\n", newFd);
        char* someText = "Some text\n";
        write(newFd, someText, strlen(someText)); // Write to the copied file descriptor
        close(newFd);
    }
}

/**
 * Example for duplicating and overwriting file descriptors.
 **/
void exampleDup2() {
    int fd = open("file.txt", O_WRONLY | O_CREAT, 0644); // Create file if not existing with rights 0644
    if(fd <= 0) {
        perror("Failed to open file \"file.txt\"");
        return;
    }

    int result = dup2(fd, STDOUT_FILENO); // Close the STDOUT_FILENO file descriptor and recreate it as a copy of fd
    if(result == -1) {
        perror("dup2 failed.");
    }
    else {
        printf("File descriptor for STDOUT_FILENO has been overwritten\n!");
        close(fd);
    }
}

/**
 * Example usage of pipes as inter process communication method.
 **/
void examplePipe() {
    int fds[2];
    // Create a new pipe.
    // fds[0] is the read end
    // fds[1] is the write end
    pipe(fds);

    int newProcessPid = fork();

    switch(newProcessPid) {
        case -1:
            perror ("fork () failed");
            break;

        case 0: // Child:
        {
            char* someText = "Bidu Bidu Bidu...";
            write(fds[1], someText, strlen(someText));
            close(fds[1]); // Allways close pipe file descriptors again after use
        }
            break;

        default: // Parent:
            sleep(2);
            char buf[1024] = {0};
            read(fds[0], buf, sizeof(buf));
            printf("Pipe read: %s\n", buf);
            close(fds[0]); // Allways close pipe file descriptors again after use

            waitpid(newProcessPid, NULL, 0); // Make sure we wait on the child process to prevent it from getting a Zombie process
            break;
    }    
}