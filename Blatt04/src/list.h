#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Hier soll die Datenstruktur und die Funktionsprototypen definiert werden

struct list_elem {
    struct list_elem            *next;  // Zeiger auf das naechste Element
    pthread_t	                data;  // Zeiger auf ein Datenobject
    int                         iThreadNumber;
    int                         iThreadPrio;
    int                         iThreadStarttime;
    int                         iThreadLaufzeit;
    int                         state; // 1=ready 2=ready+inList 3=notready
};

typedef struct list {
	struct list_elem *first;    // erstes Element in der Liste
	struct list_elem *last;     // letztes Element in der Liste
} list_t;

/* function prototypes */
list_t           *list_init ();
struct list_elem *list_append (list_t *list, pthread_t data);
struct list_elem *list_append_thread (list_t *list, int iThreadNumber, int iThreadPrio, int iThreadStarttime, int iThreadLaufzeit, int state);
int              list_remove_thread (list_t *list, struct list_elem *elem);