#include "list.h"

extern int cmp_elem (const char *str1, const char *str2);

int main (int argc, char *argv[] , char *envp[] ) {
    
    list_t *li;
    if (( li = list_init()) == NULL)
    {
        perror ("Cannot allocate memory " );
        exit(1);
    } 

    for (int idx = 1; idx < argc; idx++)
    {
        if (strcmp (argv[idx], "-a") == 0 && idx+1 < argc)
        {
            list_append (li, argv[idx+1]);
        } else if (strcmp (argv[idx], "-i") == 0 && idx+1 < argc)
        {
            list_insert (li, argv[idx+1]);
        } else if (strcmp (argv[idx], "-r") == 0 && idx+1 < argc)
        {
            struct list_elem* pElement = list_find (li, argv[idx+1], cmp_elem);
            list_remove (li, pElement);
        }
    }

    list_print(li, print_string); 
    exit(0);


    
    /*
    list_t *li;
    if (( li = list_init()) == NULL)
    {
        perror ("Cannot allocate memory " );
        exit(1);
    } 
    if (list_append (li , "erstes") == NULL ||
        list_append (li, "zweites" ) == NULL ||
        list_append (li, "drittes") == NULL )
    {
        perror ("Cannot allocate memory"); 
        exit(1);
    } 
    list_print(li,print_string); 
    exit(0);
    */
}
