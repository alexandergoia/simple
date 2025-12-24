#include <stdio.h>

int *addr;
void do_stuff();

int main(int argc, char *argv[])
{
    addr = & argc;
    (*addr)--;
    do_stuff();

    return (argc > 0) ? main(argc, argv) : 0;
}

void do_stuff() {}
