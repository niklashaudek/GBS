// #include <stdio.h>
// #include <string.h>
#include <stdlib.h>
#include <pthread.h>

// Hier soll die Datenstruktur und die Funktionsprototypen definiert werden

struct list_elem {
    struct list_elem            *next;  // Zeiger auf das naechste Element
    pthread_t	                data;  // Zeiger auf ein Datenobject
    int                         iThreadNumber;
};

typedef struct list {
	struct list_elem *first;    // erstes Element in der Liste
	struct list_elem *last;     // letztes Element in der Liste
} list_t;

/* function prototypes */
list_t           *list_init ();
struct list_elem *list_append (list_t *list, pthread_t data, int iThreadNumber);
struct list_elem *list_append_threadNum (list_t *list, int data);
struct list_elem *list_remove_thread (list_t *list, struct list_elem *elem);