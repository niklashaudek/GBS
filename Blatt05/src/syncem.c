#include <stdio.h>
// #include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
#include <pthread.h>
#include <fcntl.h> // For open(...)
#include<errno.h>

struct Container {
    int i;
    pthread_mutex_t mutex;
};

// ohne option l und f
static void* thread_func (void* data) // Thread Routine
{
    struct Container* cont = (struct Container*) data;

    pthread_mutex_lock(&cont->mutex);

    int kValue = cont->i;

    char* textFile = NULL;
    FILE* fd = NULL;
    char* mode = "r"; // we will read from the file
    switch (kValue)
    {
        // fopen() oder open()?
        case 0: fd = fopen("O.txt", mode); break; // !!!! ACHTUNG: irgenwie scheint es nur mit O anstatt 0(null) zu funktionieren!!!!
        case 1: fd = fopen("1.txt", mode); break;
        case 2: fd = fopen("2.txt", mode); break;
        case 3: fd = fopen("3.txt", mode); break;
        default: printf ("No such file found!\n"); exit (-7);
    }

    if (fd == NULL)
    {
        printf ("Error opening file number %d.\n", kValue);
        exit (-7);
    }

    printf("Thread for file %i is running!\n", kValue);

    int runningNumberI = 0;
    char fileInput[64] = {0};
    
    while (1)
    {
        printf("[%02d] %03d\t", kValue, runningNumberI);
        if (fgets(fileInput, 64, fd) != NULL)
        {
            printf("%s", fileInput);
        }
        printf("\n");
        if (fileInput[63] == '\0') // ?
        {
            break;
        }
        runningNumberI++;
    }

    fclose(fd); // Close file again and free the file descriptor.

    pthread_exit(data);
    // cont->kValue++;
    
    pthread_mutex_unlock(&cont->mutex);

    return data;
}

// option l
static void* thread_func_opL (void* data) // Thread Routine Option l
{
    struct Container* cont = (struct Container*) data;

    pthread_mutex_lock(&cont->mutex);

    int kValue = cont->i;

    char* textFile = NULL;
    int fd = 0;
    //FILE* fd = NULL;
    // char* mode = "r"; // we will read from the file
    
    switch (kValue)
    {
        // fopen() oder open()?
        case 0: printf("Try to open file 0:\n"); fd = open("0.txt", O_WRONLY); break; // !!!! ACHTUNG: irgenwie scheint es nur mit O(buchstabe) anstatt 0(zahl) zu funktionieren!!!!
        case 1: printf("Try to open file 1:\n"); fd = open("1.txt", O_WRONLY); break;
        case 2: printf("Try to open file 2:\n"); fd = open("2.txt", O_WRONLY); break;
        case 3: printf("Try to open file 3:\n"); fd = open("3.txt", O_WRONLY); break;
        default: printf ("No such file found!\n"); exit (-7);
    }

    if (fd <= 0)
    {
        printf("Error in -l\n");
        printf("Error Number: %d\n", errno);
        printf ("Error opening file number %d.\n", kValue);
        exit (-7);
    }


    printf("Thread for file %i is running!\n", kValue);

    int runningNumberI = 0;
    char fileInput[64] = {0};
    
    while (1)
    {
        printf("[%02d] %03d\t", kValue, runningNumberI);
        if (gets(fileInput) != NULL)
        {
            printf("%s", fileInput);
        }
        printf("\n");
        if (fileInput[63] == '\0') // ?
        {
            break;
        }
        runningNumberI++;
    }

    close(fd); // Close file again and free the file descriptor.

    pthread_exit(data);
    cont->i++;
    
    pthread_mutex_unlock(&cont->mutex);

    return data;
}

// option f
static void* thread_func_opF (void* data) // Thread Routine Option f
{
    struct Container* cont = (struct Container*) data;

    pthread_mutex_lock(&cont->mutex);

    int kValue = cont->i;

    char* textFile = NULL;
    FILE* fd = NULL;
    char* mode = "r"; // we will read from the file
    switch (kValue)
    {
        // fopen() oder open()?
        case 0: fd = fopen("O.txt", mode); break; // !!!! ACHTUNG: irgenwie scheint es nur mit O anstatt 0(null) zu funktionieren!!!!
        case 1: fd = fopen("1.txt", mode); break;
        case 2: fd = fopen("2.txt", mode); break;
        case 3: fd = fopen("3.txt", mode); break;
        default: printf ("No such file found!\n"); exit (-7);
    }

    if (fd == NULL)
    {
        printf ("Error opening file number %d.\n", kValue);
        exit (-7);
    }

    printf("Thread for file %i is running!\n", kValue);

    int runningNumberI = 0;
    char fileInput[64] = {0};
    
    while (1)
    {
        printf("[%02d] %03d\t", kValue, runningNumberI);
        if (fgets(fileInput, 64, fd) != NULL)
        {
            printf("%s", fileInput);
        }
        printf("\n");
        if (fileInput[63] == '\0') // ?
        {
            break;
        }
        runningNumberI++;
    }

    fclose(fd); // Close file again and free the file descriptor.

    pthread_exit(data);
    // cont->kValue++;
    
    // pthread_mutex_unlock(&cont->mutex);

    return data;
}

int main(int argc, char *argv[]) {

    list_t *li = list_init();
    list_t *threadList = list_init();
    if (( li = list_init()) == NULL)
    {
        printf ("Cannot allocate memory\n");
        exit(-5);
    }
    if (( threadList = list_init()) == NULL)
    {
        printf ("Cannot allocate memory\n");
        exit(-5);
    }

    int opt = 0;
    int iNparam = 1;  // default
    int option = 0; //default

    while ((opt = getopt (argc, argv, "-n:-l-f")) != -1) // diese Funktion verändert sich nicht
    {
        switch (opt)
        {
        case 'n':
            for( char* pChr = optarg; *pChr != 0; pChr++ )
            {
                if (isdigit(*pChr) == 0)
                {
                    printf ("Parameter N is no integer.\n");
                    exit (-1);
                }
            }
            iNparam = atoi(optarg);
            if (iNparam > 10)
            {
                printf ("Parameter N should be at maximum 10.\n");
                exit (-2);
            }
            break;
        case 'l':
            if(option == 0)
                option = 1;
            else 
            {
                printf("Only one option can be selected.\n");
                exit(-3);
            }
            break;
        case 'f':
            if(option == 0)
                option = 2;
            else 
            {
                printf("Only one option can be selected.\n");
                exit(-4);
            }
            break;
        default:
            printf ("You have to put in Parameter N.\n");
            exit (-3);
        }
    }

    if( optind != argc )
    {
        printf ("Invalid Parameter!\n");
        exit (-4);
    }

    struct Container* cont = malloc(sizeof(struct Container));
    cont->i = 1;
    pthread_mutex_init(&cont->mutex, NULL);

    for(int nIndex = 0; nIndex < iNparam; nIndex++){
        pthread_t my_thread;
        int threadNum = 0;
        // Optionen werden ausgewählt
        if(option == 0) 
        {
            threadNum = pthread_create(&my_thread, NULL, &thread_func, cont);
        } 
        else if (option == 1)
        {
            threadNum = pthread_create(&my_thread, NULL, &thread_func_opL, cont);
        } 
        else if(option == 2) 
        {
            threadNum = pthread_create(&my_thread, NULL, &thread_func_opF, cont);
        }
        if(threadNum) {
            perror("pthread_create(...) failed\n");
            return -1;
        }
        list_append(li, my_thread, nIndex);
    }

    void* sResult = NULL;
    for(int nIndex = 0; nIndex < iNparam; nIndex++)
    {
        pthread_t thisThreadID = 0;
        struct list_elem* threadElem = li->first;
        if (nIndex == 0)
        {
            thisThreadID = threadElem->data;
        }
        else
        {
            for (int listIDX = 0; listIDX < nIndex; listIDX++)
            {
                threadElem = threadElem->next;
            }
            thisThreadID = threadElem->data;
        }
      
    int result = pthread_join(thisThreadID, sResult);
    if(result) {
            perror("pthread_join(...) failed\n");
            return -1;
    }

    }

    pthread_mutex_destroy(&cont->mutex);

    return 0;
}