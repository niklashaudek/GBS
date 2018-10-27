#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    
    char buf[256];
    int counter = read(0, buf, sizeof(buf)) - 1;
    
    // Größe des Strings ermitteln
    // int counter = strlen(buf) - 1;
    buf[counter] = 0;
    
    
    // printf("Counter: %d" ,counter);
    
    // Array kopieren
    char coded[counter];
    for (int i = 0; i < counter; i++) {
        if (buf[i] < 65 || buf[i] > 122 || (buf[i] > 90 && buf[i] < 97)) {
            coded[i] = 0;
            break;
        }
        coded[i] = buf[i];
    }
    
    // Kleinbuchstaben in Grossbuchstaben umwandeln
    
    
    for (int i = 0; i < counter; i++) {
        if (coded[i] > 96 && coded[i] < 123) {
            coded[i] = coded[i] - 32;
        }
    }
    
    // ROT13 Kodierung
    for (int i = 0; i < counter; i++) {
        if (coded[i] > 64 && coded[i] < 78) {
            coded[i] = coded[i] + 13;
        }
        else if (coded[i] > 77 && coded[i] < 91) {
            coded[i] = coded[i] - 13;
        }
    }
    
    // printf("%d" ,sizeof(string));
    // printf("%d" ,sizeof(coded));
    printf("Hallo: %s -- %s\n", buf, coded);
}
