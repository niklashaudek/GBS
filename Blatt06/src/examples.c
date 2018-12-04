#include <stdio.h> // For printf(...) and sprintf(...)
#include <stdlib.h> // For malloc(...) and realloc(...)
#include <string.h> // For strcmp(...), ...
#include <unistd.h> // For execve(...)

void exampleExecve();
void exampleGetenv();
void exampleRealloc();
void exampleStrncmp();
void exampleStrcpy();
void exampleStrdup();
void exampleStrchr();

int main(int argC, char** argV) {
    // exampleExecve();
    exampleGetenv();
    // exampleRealloc();
    // exampleStrncmp();
    // exampleStrcpy();
    // exampleStrdup();
    // exampleStrchr();
}

/**
 * Executes the ls command and lists all files and folders in "/bin/".
 **/
void exampleExecve() {
    char* path = "/bin/ls";
    char* args[] = {"", "-l", "/bin/", NULL}; // A list of arguments has to end with NULL
    int result = execve(path, args, NULL); // Returns -1 on error
    if(result == -1) {
        perror("execve failed.");
    }
}

/**
 * Example for reading the value of an environment variable.
 **/
void exampleGetenv() {
    char* envName = "PATH";
    char* env = getenv(envName); // Returns NULL if no variable with the given name exists
    if (env) {
        printf("PATH: %s\n", env);
    }
    else {
        printf("PATH: NULL\n");
    }
}

/**
 * Example for using realloc(...) and strcat(...).
 **/
void exampleRealloc() {
    // Allocate space for 5 chars and \0:
    char* s = (char*) malloc(6);
    s[0] = 'H';
    s[1] = 'e';
    s[2] = 'l';
    s[3] = 'l';
    s[4] = 'o';
    s[5] = '\0';

    // Increase the allocated memory:
    s = realloc(s, 13);
    strcat(s, " World");

    printf("%s\n", s);
    free(s);
}

/**
 * Example for using strncmp(...).
 **/
void exampleStrncmp() {
    char* s1 = "Hello1";
    char* s2 = "Hello1";
    char* s3 = "Hello2";

    printf("s1 and s2: %i\n", strncmp(s1, s2, 5)); // Equal return 0
    printf("s2 and s3: %i\n", strncmp(s2, s3, 6)); // Not equal return not 0
}

/**
 * Example for using strcpy(...).
 **/
void exampleStrcpy() {
    char* s = "Hello World";
    char* s1 = (char*) malloc(sizeof(s));
    strcpy(s1, s);

    printf("%s\n", s1);
    free(s1);
}

/**
 * Example for using strdup(...).
 **/
void exampleStrdup() {
    char* s = "Hello World";
    char* s1 = NULL;
    s1 = strdup(s);
    printf("%s\n", s1);
    free(s1);
}

/**
 * Example for using strchr(...).
 **/
void exampleStrchr() {
    char* s = "Hello World";
    char* s1 = strchr(s, 'W');
    printf("%s\n", s1);
}