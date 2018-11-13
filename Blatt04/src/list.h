#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Hier soll die Datenstruktur und die Funktionsprototypen definiert werden

struct list_elem {
    struct list_elem            *next;  // Zeiger auf das naechste Element
    int	                        data;  // Zeiger auf ein Datenobject
};

typedef struct list {
	struct list_elem *first;    // erstes Element in der Liste
	struct list_elem *last;     // letztes Element in der Liste
} list_t;

/* function prototypes */
list_t           *list_init ();
struct list_elem *list_append (list_t *list, int data);