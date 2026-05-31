/* scrieti un program C care sa calculeze
 * observatia despre functia naturala a
 * numerelor prime :
 * din Z_p in Z_2
 * x ^ (p - 1) = 0 ori 1, rezultatul trecut
 * din Z_p in Z_2
 *
 * si o verificare teoretic-matematica
 * 0 sau 1 in Z_2
 * dupa cum
 * 0 sau 1 in Z_p
 * dupa cum
 * p divide x ori nu
 *
 * numarul natural x trebuie sa fie maxim strict 10000,
 * deci un intreg int, nu inca long int ori long long
 *
 * in compilator : gcc natural_primes.c -o verify -lm -Wall
 * in consola : ./verify x p
 *
 * alexander goia, unix temple, 
 * planet unix/internet, 
 * 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define author printf("Author : Alexander Goia, Computing Facilities, 2026\n")

int verify(int x, int p);
int verify_factor(int x);
int verify_prime(int p);

int main(int argc, char *argv[])
{
	author ;

	if (argc != 3) {
		printf("Usage: verify integer prime\n");
		exit(EXIT_FAILURE);
	}

	int x = atoi(argv[1]);
	int p = atoi(argv[2]);
	int count = 1;
	long int factor = 1;

	if(x >= 10000) {
		printf("numar prea mare !\n");
       		return(EXIT_FAILURE);
	}

	int r = verify_prime(p);
	if (r == 1) {
		printf("%d nu e prim, nu continuam ...\n", p);
		return(-1);
	} else
	if (r == 0) {
		printf("%d e prim, putem continua ...\n", p);
	}

	for(count = 1; count <= (p-1); count++) {
		factor = factor * x;
		factor = factor % p;
	} // main program code

	if (factor == 1) {
		if(verify(x,p) == 1)
			printf("restul este 1, ok\n");
		else
			printf("o greseala pe undeva!\n");
		return 0;
	}

	if (factor == 0) {
		if(verify(x,p) == 0)
			printf("restul este 0, ok\n");
		else
			printf("o greseala pe undeva!\n");
		return 0;
	}

	printf("o mare greseala pe undeva !\n");
	return(EXIT_FAILURE);

}

int verify_prime(int p)
{
	int limit = (int) sqrt ((double)p);
	int i;

	for(i = 2; i <= limit; i++)
	{
		if(p % i == 0) {
			printf("la test, numarul p = %d nu e prim\n", p);
			return(1);
		}
	}
	return(0);
}

int verify(int x, int p)
{
	if(p == 0) {
		printf("0 nu e numar prim\n");
		exit(-1);
	}

	int maths;
	maths = x % p;

	if(maths == 0) return(0);
	if(maths != 0) return(1);

	printf("eroare la verificare\n");
	exit(EXIT_FAILURE);
}
