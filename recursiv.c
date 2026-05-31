#include <stdio.h>

void do_stuff();

void do_stuff()
{
	printf("hello, world\n");
}

int main(int argc, char *argv[])
{
	-- (* (& argc));

	do_stuff();

	return (argc > 0) ? main(argc, argv) : 0;
}
