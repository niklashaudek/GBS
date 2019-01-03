#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int mem_init (unsigned int size, unsigned int blocksize, enum mem_algo strategy);

void *mem_alloc (unsigned int size);

void mem_free (void *addr);

void mem_dump ();