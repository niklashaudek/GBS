#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum mem_algo { none = 0, first = 1 , worst = 2 };
enum eStatus { frei , used };

struct memblock {
    struct memblock *next;  // Zeiger auf das naechste Element
    enum eStatus status ; // ist der Speicherblock frei
    char *addr ; // Adresse des Speicherblocks
    unsigned int size ; // Laenge des Speicherblocks
    unsigned int in_use; // Anteil zugewiesener Speicher; 0 wenn status == free
};

int mem_init (unsigned int size, unsigned int blocksize, enum mem_algo strategy);

void *mem_alloc (unsigned int size);

void mem_free (void *addr);

void mem_dump ();


#endif