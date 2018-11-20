#include <stdio.h>
// #include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
#include <pthread.h>
#include <fcntl.h> // For open(...)


struct Container {
    int kValue;
    pthread_mutex_t mutex;
};

static void* thread_func (void* data) // Thread Routine
{
    struct Container* cont = (struct Container*) data;

    pthread_mutex_lock(&cont->mutex);

    char* textFile = NULL;
    int fd = 0;
    switch (cont->kValue)
    {
        case 0: fd = open("0.txt", O_WRONLY | O_CREAT); break;
        case 1: fd = open("1.txt", O_WRONLY | O_CREAT); break;
        case 2: fd = open("2.txt", O_WRONLY | O_CREAT); break;
        case 3: fd = open("3.txt", O_WRONLY | O_CREAT); break;
        default: printf ("No such file found!\n"); exit (-7);
    }
    cont->kValue++;
    if(fd <= 0) // On success open(...) returns a file descriptor greater than zero.
    {
        printf ("Failed to open file number %i\n", cont->kValue);
        exit (-6);
    }

    printf("Thread for file %i is running!\n", cont->kValue);

    int runningNumberI = 0;
    char fileInput[64] = {0};
    
    while (1)
    {
        printf("[%02d] %03d\t", cont->kValue, runningNumberI);
        fgets(fileInput, 64, &fd);
        printf("%s", fileInput);
        printf("\n");
        if (fileInput[63] == '\0')
        {
            break;
        }
        runningNumberI++;
    }

    // char* text = "Hallo 42\n";
    // write(fd, text, 9); // Write text into file.
    close(fd); // Close file again and free the file descriptor.

    pthread_mutex_unlock(&cont->mutex);

    pthread_exit(data);

    return data;
}

int main(int argc, char *argv[]) {

    list_t *li;

    int opt = 0;
    // int iKparam = 10; // default
    int iNparam = 1;  // default
    // int iRparam = 0;  // default

    while ((opt = getopt (argc, argv, "-n:")) != -1) // diese Funktion verändert sich nicht
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

    if (( li = list_init()) == NULL)
    {
        printf ("Cannot allocate memory\n");
        exit(-5);
    }

    struct Container* cont = malloc(sizeof(struct Container));
    cont->kValue = 0;
    pthread_mutex_init(&cont->mutex, NULL);

    for(int nIndex = 0; nIndex < iNparam; nIndex++){
        pthread_t my_thread;
        int threadNum = pthread_create(&my_thread, NULL, &thread_func, cont);
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
        int result = pthread_join(thisThreadID, &sResult);
        if(result) {
            perror("pthread_join(...) failed\n");
            return -1;
        }
    }

    pthread_mutex_destroy(&cont->mutex);

    return 0;
}