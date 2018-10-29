#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    while (1)
    {
        char buf[256] = {0};
        int counter = read(0, buf, sizeof(buf)) - 1;


        if (strncmp(buf, "exit", 4))
        {
            return 0;
        }
    }
}