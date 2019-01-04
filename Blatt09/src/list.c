#include "list.h"

list_t *list_init () 
{
    list_t* pListe = (list_t*) malloc (sizeof(list_t*));
    pListe->first = NULL;
    pListe->last = NULL;
    // pListe->size = (int) malloc(sizeof(int));
    pListe->size = 0;
    return pListe;
}

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
    list->size++;
    return pElement;
}

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

int get_length (list_t *list)
{
    int list_length = 0;
    struct list_elem *search = list->first;
    while(search != NULL)
    {
        list_length++;
        search = search->next;
    }
    return list_length;
}

struct list_elem* list_put (list_t *list, struct list_elem *current, char *data)
{
    struct list_elem* pElement = (struct list_elem*) malloc(sizeof(struct list_elem));
    pElement->argument = data;
    if (current == list->last)
    {
        current->next = pElement;
        list->last = pElement;
    }
    else
    {
        pElement->next = current->next;
        current->next = pElement;
    }
    return pElement;
}