#include <stdio.h>
#include <unistd.h>

void hexdump (FILE *output, char *buffer, int length);

void hexdump (FILE *output, char *buffer, int length) 
{
    //char test[100];
    for (int pufferOffset = 0; pufferOffset < length; pufferOffset+=16)
    {
        fprintf(output, "%06x : ", pufferOffset);
        for (int pufferZeichen = pufferOffset; pufferZeichen < pufferOffset + 16; pufferZeichen++)
        {
            if (pufferZeichen < length)
            {
                //sprintf(test, "%2x ", (unsigned char)buffer[pufferZeichen]);
                fprintf(output, "%02x ", (unsigned char)buffer[pufferZeichen]);
            }
            else
            {
                fprintf(output, "   ");
            }
        }
        fprintf(output, "  ");
        for (int pufferZeichen = pufferOffset; pufferZeichen < pufferOffset + 16; pufferZeichen++)
        {
            if (pufferZeichen >= length) break;

            if (buffer[pufferZeichen] >= 32 && buffer[pufferZeichen] <= 126)
            {
                fprintf(output, "%c", buffer[pufferZeichen]);
            }
            else
            {
                fprintf(output, ".");
            }
            
        }
        fprintf(output, "\n");
    }
    

}

