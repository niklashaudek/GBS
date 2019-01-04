#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct list_elem {
    struct list_elem* next;  // Zeiger auf das naechste Element
    void* argument;  // Zeiger auf ein Datenobject
};

typedef struct list {
	struct list_elem *first;    // erstes Element in der Liste
	struct list_elem *last;     // letztes Element in der Liste
    int size;           // zählt Elemente in der Liste
} list_t;


// function prototypes

list_t           *list_init ();
// struct list_elem *list_insert (list_t *list, char *data);
struct list_elem *list_append (list_t *list, char *data);
struct list_elem *list_append_processID (list_t *list, int processID);
int list_remove (list_t *list, struct list_elem *elem);
int get_length (list_t *list);
struct list_elem* list_put (list_t *list, struct list_elem *current, char *data);



