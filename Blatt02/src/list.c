#include "list.h"
// hier sollen die Funktionen implementiert werden

list_t *list_init () // noch unsicher
{
    return (list_t*) malloc (sizeof(list_t*));
    /*
    list_t = *list;
    *list->first = NULL;
    *list->last = NULL;
    return *list;
    */
}

struct list_elem *list_insert (list_t *list, char *data)
{
    struct list_elem* element = (struct list_elem*) malloc(sizeof(struct list_elem));
    *element->data = *data; // darf element jeweils ein Pointer sein?
    *element->next = *list->first;
    *list->first = *element; // darf element hier ein Pointer sein?
}

struct list_elem *list_append (list_t *list, char *data)
{
    struct list_elem* element = (struct list_elem*) malloc(sizeof(struct list_elem));
    *element->data = *data; // darf element jeweils ein Pointer sein?
    *list->last = *element;
    //*element->next = NULL;
}

int list_remove (list_t *list, struct list_elem *elem)
{
    struct list_elem *comp = *list->first; // Anfang der Liste ermitteln
    char *data_comp_1 = *comp->data; // Daten des Anfangs ermitteln
    char *data_comp_2 = *elem->data; // Daten des gesuchten Elementes ermitteln

    while(strcmp(*list->last, data_comp_1) == 0){ 
        if(strcmp(*data_comp_1, *data_comp_2)){
            //remove object
            return 0;
        }
        *comp = *comp->next; // auf nächstes Objekt der Liste springen
        *data_comp_1 = *comp->data; // erneut Daten zwischenspeichern
    } 
    return -1; // Objekt wurde nicht gefunden
}

void list_finit (list_t *list)
{
    free(*list);
    *list->first = NULL;
    *list->last = NULL;
}

struct list_elem *list_find (list_t *list,char *data, int (*cmp_elem) (const char *, const char*))
{
    struct list_elem *comp = *list->first; // Anfang der Liste ermitteln
    char *data_comp_1 = *comp->data; // Daten des Anfangs ermitteln
    char *data_comp_2 = *elem->data; // Daten des gesuchten Elementes ermitteln

    while(strncmp(*list->last, data_comp_1, ) == 0){ 
        if((*data_comp_1, *data_comp_2)){
            //remove object
            return 0;
        }
        *comp = *comp->next; // auf nächstes Objekt der Liste springen
        *data_comp_1 = *comp->data; // erneut Daten zwischenspeichern
    } 
return -1; // Objekt wurde nicht gefunden
}

void list_print (list_t *list, char (*print_elem) (char *))
{

}

void print_string (char *data)
{

}

int (*cmp_elem) (const char *, const char*)
{

}