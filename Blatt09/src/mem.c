#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memory.h"

int main(int argc, char *argv[]) {

    int opt = 0;
    int mParam = 1048576; // default
    int bParam = 4096;  // default
    int algorithm = 0;  // default

    while ((opt = getopt (argc, argv, "-m:-b:-1:-w:-a:-f:")) != -1)
    {
        switch (opt)
        {
            case 'm':
                for( char* pChr = optarg; *pChr != 0; pChr++ )
                {
                    if (isdigit(*pChr) == 0)
                    {
                        printf ("Parameter -m is no integer.");
                        exit (-1);
                    }
                }
                mParam = atoi(optarg);
                break;
            case 'b':
                for( char* pChr = optarg; *pChr != 0; pChr++ )
                {
                    if (isdigit(*pChr) == 0)
                    {
                        printf ("Parameter -b is no integer.");
                        exit (-1);
                    }
                }
                bParam = atoi(optarg);
                break;
            case '1':
                if (algorithm == none) algorithm = first;
                else {printf ("Both Algorithms are set!"); exit (-1);}
                break;
            case 'w':
                if (algorithm == none) algorithm = worst;
                else {printf ("Both Algorithms are set!"); exit (-1);}
                break;
            default:
                printf ("Error!");
                exit (-3);
        }
    }
/*
    if( optind != argc )
    {
        printf ("Invalid Parameter!");
        exit (-4);
    }
*/
    if (none == algorithm)
    {
        printf ("Algorithm is not set!");
        exit (-5);
    }

    

    int iSize = mem_init(mParam, bParam, algorithm);
    mem_dump();


}