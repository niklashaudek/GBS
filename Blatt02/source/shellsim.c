#include <stdio.h>

int main(int argc, char **argv) {
    
    while (1)
    {
        char buf[256] = {0};
        int counter = read(0, buf, sizeof(buf)) - 1;

    }
    

    return 0;
}