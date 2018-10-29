#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    
    char buf[256] = {0};
    char exitString[5] = "exit";

    while (1)
    {
        int counter = read(0, buf, sizeof(buf)) - 1;

        if (!strncmp(buf, exitString, 4))
        {
            return 0;
        }
    }
}