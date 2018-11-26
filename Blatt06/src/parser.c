#include "list.h"


char* buildingStringErweitern (char* oldStr, int oldStrLen)
{
    if (NULL == oldStr && 0 == oldStrLen)
    {
        char* newStr = ( char* ) malloc ( 1 * sizeof(char) );
        // free(newStr);
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
    // free(newStr);
    return newStr;
}


int parser(char cmdLineInput[], char *envp[])
{
    
    list_t* li = list_init();
    if (( li = list_init()) == NULL)
    {
        perror ("Cannot allocate memory " );
        exit(1);
    }

    // char buildingString[1] = {0};
    char* buildingString = ( char* ) malloc ( 1 * sizeof(char) );

    int cmdLinePos = 0;
    int buildPos = 0;
    int sonderFall = 0;

    while ('\n' != cmdLineInput[cmdLinePos]) // Bedingung kann auch 1 sein, da unten break vorkommt
    {

        if ('$' == cmdLineInput[cmdLinePos]) // Kümmert sich komplett um die Variable nach dem Zeichen: $
        {
            cmdLinePos++;
            char thisC = cmdLineInput[cmdLinePos];
            while ( ('0' < thisC && '9' > thisC) || ('A' < thisC && 'Z' > thisC) || '_' == thisC )
            {
                buildingString[buildPos] = thisC;
                buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                buildPos++;
                thisC = cmdLineInput[++cmdLinePos];
            }
            // Jetzt muss die passende Variable in envp gefunden werden
            while (0 != strncmp(*envp, buildingString, strlen(buildingString)-1))
            {
                envp++;
            }
            char* bufferStr = ( char* ) malloc ( strlen(*envp) * sizeof(char) );
            bufferStr = *envp;

            int positionBehindEqual = strlen(buildingString)+1;
            buildingString = buildingStringErweitern(NULL, 0); // new char array allcoation

            int posForBuild = 0;
            for (int idx = positionBehindEqual; idx < strlen(bufferStr); idx++)
            {
                buildingString[posForBuild] = bufferStr[idx];
                buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                posForBuild++;
            }
        }

        if ('\\' == cmdLineInput[cmdLinePos]) // Kümmert sich direkt um das nächste Zeichen
        {
            cmdLinePos++;
            buildingString[buildPos] = cmdLineInput[cmdLinePos];
            buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
            buildPos++;
            cmdLinePos++;
        }

        if ('"' == cmdLineInput[cmdLinePos]) // Sonderfall 1: " " (Doppelte Hochkomma)
        {
            if (0 == sonderFall) {sonderFall = 1; cmdLinePos++;}
            else if (1 == sonderFall) {sonderFall = 0; cmdLinePos++;}
            // else printf("Achtung geschachtelte Sonderzeichen!\n");
            // cmdLinePos++;
        }
        else if ('\'' == cmdLineInput[cmdLinePos]) // Sonderfall 2: ' ' (Einfache Hochkomma)
        {
            if (0 == sonderFall) {sonderFall = 2; cmdLinePos++;}
            else if (2 == sonderFall) {sonderFall = 0; cmdLinePos++;}
            // else printf("Achtung geschachtelte Sonderzeichen!\n");
            // cmdLinePos++;
        }

        if (0 == sonderFall)
        {
            // Standard fall ohne irgendwelche Hochkommas oder anderen Scheiß
            switch (cmdLineInput[cmdLinePos])
            {
                case ' ':
                    list_append(li, buildingString);
                    // printf("Argument: %s\n", buildingString); // Test Ausgabe
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
                default:
                    buildingString[buildPos] = cmdLineInput[cmdLinePos];
                    buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
                    buildPos++;
                    cmdLinePos++;
                    break;
            }
        }
        else if (1 == sonderFall || 2 == sonderFall)
        {
            buildingString[buildPos] = cmdLineInput[cmdLinePos];
            buildingString = buildingStringErweitern(buildingString, strlen(buildingString));
            buildPos++;
            cmdLinePos++;
        }




        // Anhängen des letzten Command Line Arguments
        if ('\n' == cmdLineInput[cmdLinePos])
        {
            list_append(li, buildingString);
            // printf("Argument: %s\n", buildingString); // Test Ausgabe
            break;
        }
    }

    if (0 != sonderFall)
    {
        printf("Sonderzeichen wurden nicht korrekt verwendet!\n");
        exit(-1);
    }

    // free(cmdLineInput);
    // free(buildingString);

    // Ausgabe
    struct list_elem* thisListElem = li->first;
    int elemCounter = 1;
    while (NULL != thisListElem)
    {
        printf("%i:%s\n", elemCounter, thisListElem->argument);
        elemCounter++;
        thisListElem = thisListElem->next;
    }

    return 1;
}