#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// fertig, bitte nichts ändern
int main(int argc, char **argv) {
    char buf[128] = {0};
    char exitString[6] = "exit\n";
    while (1)
    {
        fgets(buf, 128, stdin);
        if (!strncmp(buf, exitString, 5))
        {
            return 0;
        }
        else
        {
            system(buf);
        }
    }
}