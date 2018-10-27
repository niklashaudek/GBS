#include <stdio.h>

int main(int argc, char **argv) {
    printf("Oct\tDec\tHex\tChar\n");
    int i = 0;
    printf("00%#o\t%d\t0%x\t%c\n",i,i,i,i);
    i = 1;
    do
    {
        printf("0%#o\t%d\t0%x\t%c\n",i,i,i,i);
        i++;
    }
    while(i<=7);
    do
    {
        printf("%#o\t%d\t0%x\t%c\n",i,i,i,i);
        i++;
    }
    while(i<=15);
    do
    {
        printf("%#o\t%d\t%x\t%c\n",i,i,i,i);
        i++;
    }
    while(i<=63);
    do
    {
        printf("%o\t%d\t%x\t%c\n",i,i,i,i);
        i++;
    }
    while(i<=127);
}