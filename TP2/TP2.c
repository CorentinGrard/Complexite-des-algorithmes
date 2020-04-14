#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 10
#define SIZE_DOMAIN 5

void solve(int somme, int i, int z);

int domain[] = {2, 3, 5, 7, 9};
int nbSol = 0;

int main(int argc, char **argv)
{
    clock_t start = clock();
    solve(0, 0, 52);
    clock_t end = clock();
    double time = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Number of solutions : %d\n", nbSol);
    printf("Time of exec : %f s\n", time);
}


void solve(int somme, int i, int z)
{
    if (i < SIZE && somme < z)
    {
        for (int j = 0; j < SIZE_DOMAIN; j++)
        {
            solve(somme + domain[j], i + 1, z);
        }
    }
    if (i == SIZE && somme == z)
    {
        nbSol++;
    }
}
