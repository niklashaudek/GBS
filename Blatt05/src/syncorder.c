#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
#include <pthread.h>
#include <fcntl.h> // For open(...)
// #include <sys/types.h>
// #include <sys/stat.h>
#include <errno.h>



pthread_mutex_t myMutex;
pthread_mutex_t condMutex;
pthread_cond_t cond;
long currentThreadID = 0;


// ohne option l und f
static void* thread_func (void* data) // Thread Routine
{
    int kValue = *(int*)data;
    FILE* fd = NULL;
    
    switch (kValue)
    {
        case 0: fd = fopen("0.txt", "r"); break;
        case 1: fd = fopen("1.txt", "r"); break;
        case 2: fd = fopen("2.txt", "r"); break;
        case 3: fd = fopen("3.txt", "r"); break;
        case 4: fd = fopen("4.txt", "r"); break;
        case 5: fd = fopen("5.txt", "r"); break;
        case 6: fd = fopen("6.txt", "r"); break;
        case 7: fd = fopen("7.txt", "r"); break;
        case 8: fd = fopen("8.txt", "r"); break;
        case 9: fd = fopen("9.txt", "r"); break;
        default: printf ("No such file found!\n"); exit (-7);
    }

    if (fd <= 0)
    {
        printf("Error in -l\n");
        printf("Error Number: %d\n", errno);
        printf ("Error opening file number %d.\n", kValue);
        exit (-7);
    }

    // printf("Thread for file %i is running!\n", kValue);s
    int runningNumberI = 0;
    
    while (1)
    {
        char fileInput[65] = {0};

        int iRead = fread( fileInput, 1, 64, fd );
        if (iRead <= 0)
        {
            break;
        }
        printf("[%02d] %03d\t", kValue, runningNumberI);
        printf("%s", fileInput);
        printf("\n");
        runningNumberI++;
    }

    fclose(fd); // Close file again and free the file descriptor.

    pthread_exit(data);
 
    return data;
}

// option l
static void* thread_func_opL (void* data) // Thread Routine Option l
{
    int kValue = *(int*)data;
    FILE* fd = NULL;
    
    switch (kValue)
    {
        case 0: fd = fopen("0.txt", "r"); break;
        case 1: fd = fopen("1.txt", "r"); break;
        case 2: fd = fopen("2.txt", "r"); break;
        case 3: fd = fopen("3.txt", "r"); break;
        case 4: fd = fopen("4.txt", "r"); break;
        case 5: fd = fopen("5.txt", "r"); break;
        case 6: fd = fopen("6.txt", "r"); break;
        case 7: fd = fopen("7.txt", "r"); break;
        case 8: fd = fopen("8.txt", "r"); break;
        case 9: fd = fopen("9.txt", "r"); break;
        default: printf ("No such file found!\n"); exit (-7);
    }

    if (fd <= 0)
    {
        printf("Error in -l\n");
        printf("Error Number: %d\n", errno);
        printf ("Error opening file number %d.\n", kValue);
        exit (-7);
    }

    // printf("Thread for file %i is running!\n", kValue);s
    int runningNumberI = 0;
    
    while (1)
    {
        // printf("vor Mutex Lock \n");
        pthread_mutex_lock(&myMutex);
        // printf("nach Mutex Lock \n");

        char fileInput[65] = {0};

        int iRead = fread( fileInput, 1, 64, fd );
        if (iRead <= 0)
        {
            break;
        }
        printf("[%02d] %03d\t", kValue, runningNumberI);
        printf("%s", fileInput);
        printf("\n");
        runningNumberI++;

        pthread_mutex_unlock(&myMutex);
    }

    fclose(fd); // Close file again and free the file descriptor.

    pthread_exit(data);
 
    return data;
}

// option f
static void* thread_func_opF (void* data) // Thread Routine Option f
{
    int kValue = *(int*)data;
    FILE* fd = NULL;

    switch (kValue)
    {
        case 0: fd = fopen("0.txt", "r"); break;
        case 1: fd = fopen("1.txt", "r"); break;
        case 2: fd = fopen("2.txt", "r"); break;
        case 3: fd = fopen("3.txt", "r"); break;
        case 4: fd = fopen("4.txt", "r"); break;
        case 5: fd = fopen("5.txt", "r"); break;
        case 6: fd = fopen("6.txt", "r"); break;
        case 7: fd = fopen("7.txt", "r"); break;
        case 8: fd = fopen("8.txt", "r"); break;
        case 9: fd = fopen("9.txt", "r"); break;
        default: printf ("No such file found!\n"); exit (-7);
    }

    if (fd <= 0)
    {
        printf("Error in -l\n");
        printf("Error Number: %d\n", errno);
        printf ("Error opening file number %d.\n", kValue);
        exit (-7);
    }

    // printf("vor Mutex Lock \n");
    pthread_mutex_lock(&myMutex);
    // printf("nach Mutex Lock \n");

    // printf("Thread for file %i is running!\n", kValue);s
    int runningNumberI = 0;

    while (1)
    {
        char fileInput[65] = {0};

        int iRead = fread( fileInput, 1, 64, fd );
        if (iRead <= 0)
        {
            break;
        }
        printf("[%02d] %03d\t", kValue, runningNumberI);
        printf("%s", fileInput);
        printf("\n");
        runningNumberI++;
    }

    fclose(fd); // Close file again and free the file descriptor.
    pthread_mutex_unlock(&myMutex);


    pthread_exit(data);
 
    return data;
}

int write_buffer (long thread, char *buffer, int len)
{
    if (buffer == NULL)
    {
        currentThreadID++;
        pthread_cond_signal(&cond);
        return 1;
    }
    
    while (currentThreadID != thread)
    {
        pthread_mutex_lock(&condMutex); //mutex lock
        pthread_cond_wait(&cond, &condMutex); //wait for the condition
    }

    write(1, buffer, len);

    pthread_mutex_unlock(&condMutex);
    
    return 1;
}

// otion o
static void* thread_func_opO (void* data) // Thread Routine Option o
{
    int kValue = *(int*)data;
    FILE* fd = NULL;

    switch (kValue)
    {
        case 0: fd = fopen("0.txt", "r"); break;
        case 1: fd = fopen("1.txt", "r"); break;
        case 2: fd = fopen("2.txt", "r"); break;
        case 3: fd = fopen("3.txt", "r"); break;
        case 4: fd = fopen("4.txt", "r"); break;
        case 5: fd = fopen("5.txt", "r"); break;
        case 6: fd = fopen("6.txt", "r"); break;
        case 7: fd = fopen("7.txt", "r"); break;
        case 8: fd = fopen("8.txt", "r"); break;
        case 9: fd = fopen("9.txt", "r"); break;
        default: printf ("No such file found!\n"); exit (-7);
    }

    if (fd <= 0)
    {
        printf("Error in -l\n");
        printf("Error Number: %d\n", errno);
        printf ("Error opening file number %d.\n", kValue);
        exit (-7);
    }

    // printf("vor Mutex Lock \n");
    // pthread_mutex_lock(&myMutex);
    // printf("nach Mutex Lock \n");

    // printf("Thread for file %i is running!\n", kValue);s

    // int writing = write_buffer(kValue, fd, 100);

    int runningNumberI = 0;

    while (1)
    {
        char fileInput[65] = {0};

        int iRead = fread( fileInput, 1, 64, fd );
        if (iRead <= 0)
        {
            break;
        }

        char szString[100] = {0};

        sprintf(szString, "[%02d] %03d\t", kValue, runningNumberI);
        write_buffer(kValue, szString, strlen(szString));

        sprintf(szString, "%s", fileInput);
        write_buffer(kValue, szString, strlen(szString));

        sprintf(szString, "\n");
        write_buffer(kValue, szString, strlen(szString));

        runningNumberI++;
    }

    write_buffer(kValue, NULL, 0);

    fclose(fd); // Close file again and free the file descriptor.
    // pthread_mutex_unlock(&myMutex);


    pthread_exit(data);
 
    return data;
}

int main(int argc, char *argv[]) {

    list_t *li = list_init();
    // list_t *threadList = list_init();
    if (( li = list_init()) == NULL)
    {
        printf ("Cannot allocate memory\n");
        exit(-5);
    }
    /*
    if (( threadList = list_init()) == NULL)
    {
        printf ("Cannot allocate memory\n");
        exit(-5);
    }
    */

    int opt = 0;
    int iNparam = 1;  // default
    int option = 0; //default

    while ((opt = getopt (argc, argv, "-n:-l-f-o")) != -1) // diese Funktion verändert sich nicht
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
        case 'o':
            if(option == 0)
                option = 3;
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

    if ( pthread_mutex_init(&myMutex, NULL) != 0 )
    {
        printf("\n mutex: myMutex init failed\n");
        return 1;
    }

    if ( pthread_mutex_init(&condMutex, NULL) != 0 )
    {
        printf("\n mutex: condMutex init failed\n");
        return 1;
    }

    if ( pthread_cond_init(&cond, NULL) != 0 )
    {
        printf("\n condition init failed\n");
        return 1;
    }

    int aiIndex[10] = {0};

    for(int nIndex = 0; nIndex < iNparam; nIndex++)
    {
        pthread_t my_thread;
        int threadNum = 0;

        aiIndex[nIndex] = nIndex;

        // Optionen werden ausgewählt
        if(option == 0) 
        {
            threadNum = pthread_create(&my_thread, NULL, &thread_func, &aiIndex[nIndex]);
        } 
        else if (option == 1)
        {
            threadNum = pthread_create(&my_thread, NULL, &thread_func_opL, &aiIndex[nIndex]);
        } 
        else if(option == 2) 
        {
            threadNum = pthread_create(&my_thread, NULL, &thread_func_opF, &aiIndex[nIndex]);
        }
        else if(option == 3) 
        {
            threadNum = pthread_create(&my_thread, NULL, &thread_func_opO, &aiIndex[nIndex]);
        }
        if(threadNum) {
            perror("pthread_create(...) failed\n");
            return -1;
        }
        usleep(1000);
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
        if(result)
        {
            perror("pthread_join(...) failed\n");
            return -1;
        }

    }

    pthread_mutex_destroy(&myMutex);

    return 0;
}