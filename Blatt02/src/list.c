#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// hier sollen die Funktionen implementiert werden

list_t *list_init (){ // noch unsicher
list_t = *list;
*list->first = NULL;
*list->last = NULL;
return *list;
}

struct list_elem *list_insert (list_t *list, char *data){ 
list_elem element = malloc(sizeof(list_elem));
*element->data = *data; // darf element jeweils ein Pointer sein?
*element->next = *list->first;
*list->first = *element; // darf element hier ein Pointer sein?
}

struct list_elem *list_append (list_t *list, char *data){
list_elem element = malloc(sizeof(list_elem));
*element->data = *data; // darf element jeweils ein Pointer sein?
*list->last = *element;
*element->next = NULL;
}

int list_remove (list_t *list, struct list_elem *elem){

}

void list_finit (list_t *list){
free(*list);
*list->first = NULL;
*list->last = NULL;
}

struct list_elem *list_find (list_t *list,char *data, int (*cmp_elem) (const char *, const char*)){

}

void list_print (list_t *list, char (*print_elem) (char *)){

}

