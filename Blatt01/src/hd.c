#include <stdio.h>
#include <string.h>

void hexdump (FILE *output, char *buffer, int length);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Bitte übergeben sie einen Parameter!\n");
    }
    else
    {
        //char szBuffer[256] = "Grundlagen Betriebssystem und Systemsoftware.";

        //strcpy( szBuffer, argv[1]);

        //hexdump(stdout, szBuffer, strlen(szBuffer)+1);
        for( int iIdx = 1; iIdx < argc; iIdx++ )
        {
            hexdump(stdout, argv[iIdx], (int)strlen(argv[iIdx])+1 );
            fprintf(stdout, "\n");
        }
    }

    return 0;
}