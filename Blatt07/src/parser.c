#include "list.h"
#include "unistd.h"

char* buildingStringErweitern (char* oldStr, int oldStrLen)
{
    if (NULL == oldStr && 0 == oldStrLen)
    {
        char* newStr = ( char* ) malloc ( 1 * sizeof(char) );
        newStr[oldStrLen] = '\0';
        return newStr;
    }
    char* newStr = ( char* ) malloc ( (oldStrLen+1) * sizeof(char) );
    if(newStr == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    for (int strIndex = 0; strIndex < oldStrLen; strIndex++)
    {
        newStr[strIndex] = oldStr[strIndex];
    }
    newStr[oldStrLen] = '\0';
    return newStr;
}


list_t* parser(char cmdLineInput[], char *envp[])
{
    
    list_t* li = list_init();
    if (( li = list_init()) == NULL)
    {
        perror ("Cannot allocate memory " );
        exit(1);
    }

    char* buildingString = ( char* ) malloc ( 2 * sizeof(char) );

    int cmdLinePos = 0;
    int buildPos = 0;
/*
    buildingString[buildPos++] = cmdLineInput[cmdLinePos++];
    buildingString[buildPos++] = cmdLineInput[cmdLinePos++];
*/
    int switchLeft = 0;
    int switchRight = 0;
    while ('\n' != cmdLineInput[cmdLinePos])
    {
        switch (cmdLineInput[cmdLinePos])
        {
            case ' ':
                if (0 != cmdLinePos) 
                {
                    list_append(li, buildingString);
                }
                buildingString = buildingStringErweitern(NULL, 0); // new char array allcoation
                buildPos = 0;
                cmdLinePos++;
                while (' ' == cmdLineInput[cmdLinePos])
                {
                    cmdLinePos++;
                }
                break;
            case '\n':
                break;
            case '<':
                if(switchLeft > 0)
                {
                    perror("Switch Left kommt zu häufig vor.");
                    exit(-2);
                }
                switchLeft++;
                buildingString[buildPos++] = cmdLineInput[cmdLinePos++];
                buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                buildingString[buildPos++] = cmdLineInput[cmdLinePos++];
                buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                break;
            case '>':
                if(switchRight > 0)
                {
                    perror("Switch Right kommt zu häufig vor.");
                    exit(-3);
                }
                switchRight++;
                buildingString[buildPos++] = cmdLineInput[cmdLinePos++];
                buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                buildingString[buildPos++] = cmdLineInput[cmdLinePos++];
                buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                break;
            default:
                buildingString[buildPos++] = cmdLineInput[cmdLinePos++];
                buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                break;
        }
        if ('\n' == cmdLineInput[cmdLinePos])
        {
            list_append(li, buildingString);
            break;
        }
    }

    return li;
}