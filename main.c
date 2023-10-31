#include <stdio.h>

int *addr;

void do_stuff();

int main(int argc, char *argv[])
{
    addr = & argc;
   
    int i;
    for(i = 0; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");

    (*addr)--;

    do_stuff();

    return (argc > 0) ? main(argc, argv) : 0;
}

void do_stuff()
{
    printf("doing something...\n");
}
