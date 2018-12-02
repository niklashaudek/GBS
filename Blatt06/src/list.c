#include "list.h"
// hier sollen die Funktionen implementiert werden

// Note: Elementcounter wurde hinzugefügt
list_t *list_init () 
{
    list_t* pListe = (list_t*) malloc (sizeof(list_t*));
    pListe->first = NULL;
    pListe->last = NULL;
    pListe->elementCount = 0;
    return pListe;
}

/*
struct list_elem *list_insert (list_t *list, char *data) // fertig
{
    struct list_elem* pElement = (struct list_elem*) malloc(sizeof(struct list_elem));
    pElement->argument = data;
    if (list->last != NULL)
    {
        pElement->next = list->first;
        list->first = pElement;
    } else
    {
        list->last = pElement;
        list->first = pElement;
        list->first->next = NULL;
    }
    
    return pElement;
}
*/

struct list_elem *list_append (list_t *list, char *argument) // fertig
{
    struct list_elem* pElement = (struct list_elem*) malloc(sizeof(struct list_elem));
    pElement->argument = argument;
    if (list->last != NULL)
    {
        list->last->next = pElement;
        list->last = pElement;
        list->last->next = NULL;
    } 
    else
    {
        list->last = pElement;
        list->first = pElement;
        list->first->next = NULL;
        
    }
    list->elementCount++;
    return pElement;
}

/*

int list_remove (list_t *list, struct list_elem *elem) // fertig
{
    struct list_elem *toDeleteElement = list->first;
    struct list_elem *prevElement = NULL;
    do
    {
        if (strcmp (toDeleteElement->argument, elem->argument) == 0)
        {
            if (prevElement != NULL) prevElement->next = toDeleteElement->next;
            else
            {
                list->first = toDeleteElement->next;
            }
            free (toDeleteElement); // toDeleteElement löschen
            return 0;
        }
        prevElement = toDeleteElement;
        toDeleteElement = toDeleteElement->next;

    } while (toDeleteElement != NULL);

    return -1; // Objekt wurde nicht gefunden
}

void list_finit (list_t *list) // fertig
{
    struct list_elem *comp = list->first; // Element, welches gelöscht werden kann
    struct list_elem *pNext = NULL;
    do
    {
        pNext = comp->next; // nextPointer zwischenspeichern
        free (comp->argument); // data löschen
        free (comp); // comp löschen
        comp = pNext; // nächstes Element auswählen
    } while (comp != NULL);

    free (list);
}

struct list_elem *list_find (list_t *list,char *data, int (*cmp_elem) (const char *, const char*)) // fertig
{
    struct list_elem *comp = list->first; // Element, welches verglichen werden soll
    do
    {
        if (0 == (*cmp_elem) (comp->argument, data)) { // Funktion zum Vergleichen der data anwenden
            return comp;
        }
        comp = comp->next;
    } while (comp != NULL);

    return NULL;
}

void list_print (list_t *list, void (*print_elem) (char *)) // fertig
{
    struct list_elem *comp = list->first; // Element, welches verglichen werden soll
    do
    {
        (*print_elem) (comp->argument);
        comp = comp->next;
    } while (comp != NULL);
}

void print_string (char *data) // fertig
{
    static int idx = 1;
    printf("%d:%s\n", idx, data);
    idx++;
}

int cmp_elem (const char *str1, const char *str2) // fertig
{
    return strcmp (str1, str2);
}

*/