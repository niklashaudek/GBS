#include "memory.h"
#include "list.h"

unsigned int g_blocksize;
char* g_startAdresse;
unsigned int g_memsize;
enum mem_algo g_strategy;

list_t* memList;

int mem_init (unsigned int size, unsigned int blocksize, enum mem_algo strategy)
{
    g_blocksize = blocksize;
    g_startAdresse = (char*) malloc (size);
    g_memsize = size;
    g_strategy = strategy;

    memList = list_init();
    struct memblock* firstMemblock = (struct memblock*) malloc (sizeof(struct memblock));
    if (firstMemblock != NULL) 
    {
        firstMemblock->addr = g_startAdresse;
        firstMemblock->in_use = 0;
        firstMemblock->next = NULL;
        firstMemblock->size = g_memsize;
        firstMemblock->status = frei;

        list_append(memList, (char*) firstMemblock);

        return size;
    }
    else
    {
        return 0;
    }
}

void *mem_alloc (unsigned int size)
{
    if (first == g_strategy)
    {
        struct list_elem* current = memList->first;
        struct memblock* currentMemblock = current->argument;
        for (int iIdx = 1; current != NULL; iIdx++ )
        {
            if (currentMemblock->size - currentMemblock->in_use >= size)
            {
                // hier was machen
                return currentMemblock;
            }
            current = current->next;
        }
    }
    else if (worst == g_strategy)
    {
        struct list_elem* current = memList->first;
        struct memblock* currentMemblock = current->argument;
        int groeßterVerschnitt = 0;
        int worstPosition = 0;
        for (int iIdx = 1; current != NULL; iIdx++ )
        {
            if (currentMemblock->size - currentMemblock->in_use - size >= groeßterVerschnitt)
            {
                groeßterVerschnitt = currentMemblock->size - currentMemblock->in_use - size;
                worstPosition = iIdx;
            }
            current = current->next;
        }
        current = memList->first;
        for (int iIdx = 1; iIdx < worstPosition; iIdx++ )
        {
            current = current->next;
        }
        currentMemblock = current->argument;
        // hier weiter machen
        return currentMemblock;
    }
}

void mem_free (void *addr)
{
    return;
}

void mem_dump ()
{
    struct list_elem* current = memList->first;
    for (int iIdx = 1; current != NULL; iIdx++ )
    {
        struct memblock* currentMemblock = current->argument;


        printf("%d:[%p %c %d/%d] ", iIdx,
                                currentMemblock->addr, 
                                currentMemblock->status == frei ? 'F' : 'P', 
                                currentMemblock->in_use, 
                                currentMemblock->size);

        current = current->next;
    }
    printf("\n");

    return;
}