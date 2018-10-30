#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list.h>


// #include funktioniert bei mir nicht
// hier soll die Main Funktion geschrieben werden
int main (int argc, char *argv[] , char *envp[] ) {
list_t *li;
i f (( li = list_init()) == NULL) {
perror ("Cannot allocate memory " ) ; exit(1);
} 
if (list_append (li , "erstes") == NULL || list_append (li, "zweites" ) == NULL || list_append (li, "drittes") == NULL ) {
perror("Cannot allocate memory") ; 
exit(1);} 
list_print(li,print_string); 
exit(0);
}
