#include <stdio.h>
// #include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
// #include <ctype.h>
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

    int fd = open("%d.txt", cont->kValue, O_WRONLY | O_CREAT); // Open the file in write only and create it if it does not exist.
    if(fd <= 0) // On success open(...) returns a file descriptor greater than zero.
    {
        perror("Failed to open file \"file.txt\"");
        return;
    }

    int runningNumberI = 0;
    char fileInput[64];
    char finalInputFile[64];

    while (1)
    {
        int higherNumber = runningNumberI+1;
        finalInputFile[higherNumber*64];
        if (runningNumberI > 0)
        {
            for (int i = 0; i < runningNumberI*64; i++)
            {
                finalInputFile[i] = fileInput[i];
            }
        }
        fileInput[higherNumber*64];
        fgets(fileInput, 64, fd);
        for (int i = 0; i < higherNumber*64; i++)
            {
                finalInputFile[i] = fileInput[i];
            }
        if (fileInput[63] == '\0')
        {
            break;
        }
        runningNumberI++;
    }

    printf("[%02d] %03d\t", cont->kValue, runningNumberI);
    printf("%s", finalInputFile);
    printf("\n");

    // char* text = "Hallo 42\n";
    // write(fd, text, 9); // Write text into file.
    close(fd); // Close file again and free the file descriptor.

    pthread_exit((void*) cont->kValue);

    pthread_mutex_unlock(&cont->mutex);

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
                    printf ("Parameter N is no integer.");
                    exit (-1);
                }
            }
            iNparam = atoi(optarg);
            if (iNparam > 10)
            {
                printf ("Parameter N should be at maximum 10.");
                exit (-2);
            }
            break;
        default:
            printf ("You have to put in Parameter N");
            exit (-3);
        }
    }

    if( optind != argc )
    {
        printf ("Invalid Parameter!");
        exit (-4);
    }

    if (( li = list_init()) == NULL)
    {
        printf ("Cannot allocate memory" );
        exit(-5);
    }

    struct Container* cont = malloc(sizeof(struct Container));
    cont->kValue = 0;
    pthread_mutex_init(&cont->mutex, NULL);

    for(int nIndex = 0; nIndex < iNparam; nIndex++){
        pthread_t my_thread;
        int threadNum = pthread_create(&my_thread, NULL, &thread_func, &nIndex);
        if(threadNum) {
            perror("pthread_create(...) failed");
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
            perror("pthread_join(...) failed");
            return -1;
        }
    }

    pthread_mutex_destroy(&cont->mutex);

    return 0;
}