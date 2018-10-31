#include <list.h>
// hier sollen die Funktionen implementiert werden

list_t *list_init (){
    list_t l;
}

struct list_elem *list_insert (list_t *list, char *data){

}

struct list_elem *list_append (list_t *list, char *data){

}

int list_remove (list_t *list, struct list_elem *elem){

}

void list_finit (list_t *list){

}

struct list_elem *list_find (list_t *list,char *data, int (*cmp_elem) (const char *, const char*)){

}

void list_print (list_t *list, char (*print_elem) (char *)){

}

