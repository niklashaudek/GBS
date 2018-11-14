#include "list.h"
#include <pthread.h>

list_t *list_init () 
{
    list_t* pListe = (list_t*) malloc (sizeof(list_t*));
    pListe->first = NULL;
    pListe->last = NULL;
    return pListe;
}

struct list_elem *list_append (list_t *list, pthread_t data) // fertig
{
    struct list_elem* pElement = (struct list_elem*) malloc(sizeof(struct list_elem));
    pElement->data = data;
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
    return pElement;
}

struct list_elem *list_append_thread (list_t *list, int iThreadNumber, int iThreadPrio, int iThreadStarttime, int iThreadLaufzeit)
{
    struct list_elem* pElement = (struct list_elem*) malloc(sizeof(struct list_elem));
    pElement->iThreadNumber = iThreadNumber;
    pElement->iThreadPrio = iThreadPrio;
    pElement->iThreadStarttime = iThreadStarttime;
    pElement->iThreadLaufzeit = iThreadLaufzeit;
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
    return pElement;
}

int list_remove_thread (list_t *list, struct list_elem *elem) // fertig
{
    struct list_elem *toDeleteElement = list->first;
    struct list_elem *prevElement = NULL;
    do
    {
        if (strcmp (toDeleteElement->data, elem->data) == 0)
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