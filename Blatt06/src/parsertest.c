#include "list.h"

int parser(char cmdLineInput[]);


int main (int argc, char *argv[] , char *envp[] )
{
    while (1)
    {
        printf("$ ");

        char cmdLineInput[1024] = {0};
        fgets(cmdLineInput, 1024, stdin);

        if (strcmp(cmdLineInput, "exit\n") == 0)
        {
            return 1;
        }

        int parsing = parser(cmdLineInput);

    }
}