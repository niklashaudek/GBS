#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Hier soll die Datenstruktur und die Funktionsprototypen definiert werden

struct list_elem {
    struct list_elem            *next;  // Zeiger auf das naechste Element
    pthread_t	                data;  // Zeiger auf ein Datenobject
    int                         iThreadNum;
    int                         iThreadPrio;
    int                         iTimeStep;
    int                         i

};

typedef struct list {
	struct list_elem *first;    // erstes Element in der Liste
	struct list_elem *last;     // letztes Element in der Liste
} list_t;

/* function prototypes */
list_t           *list_init ();
struct list_elem *list_append (list_t *list, pthread_t data);