#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 14
#define SIZE_DOMAIN 5

void solve(int somme, int i, int z, int nbval);

int sol[SIZE];

int main(int argc, char **argv)
{
    clock_t start = clock();
    solve(0, 0, 72, SIZE);
    clock_t end = clock();
    double time = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time of exec : %f\n", time);
}

int domain[] = {2, 3, 5, 7, 9};

void solve(int somme, int i, int z, int nbval)
{
    if (i < nbval && somme < z)
    {
        for (int j = 0; j < SIZE_DOMAIN; j++)
        {
            sol[i] = domain[j];
            solve(somme + domain[j], i + 1, z, nbval);
        }
    }
    if (i == nbval && somme == z)
    {
        int k;
        for (k = 0; k < nbval; k++)
            printf("%d ", sol[k]);
        putchar('\n');
    }
}
