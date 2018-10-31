#include "list.h"

// hier soll die Main Funktion geschrieben werden

// diese Main ist ein Test vom Sheet
int main (int argc, char *argv[] , char *envp[] ) {
    list_t *li;
    if (( li = list_init()) == NULL)
    {
        perror ("Cannot allocate memory " );
        exit(1);
    } 
    if (list_append (li , "erstes") == NULL || list_append (li, "zweites" ) == NULL || list_append (li, "drittes") == NULL )
    {
        perror ("Cannot allocate memory"); 
        exit(1);
    } 
    list_print(li,print_string); 
    exit(0);
}
