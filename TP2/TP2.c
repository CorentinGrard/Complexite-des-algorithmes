#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 5
#define SIZE_DOMAIN 5

void solve(int somme, int i, int z, int size);

int size[]   = {10, 11, 12, 13, 14}; 
int result[] = {52, 57, 62, 67, 72};
int domain[] = {2, 3, 5, 7, 9};
int nbSol = 0;

int main(int argc, char **argv)
{
    for (int i = 0; i < SIZE; i++)
    {
        struct timespec startTime, finish;
        double elapsed;
        printf("Number of variables : %d\n", size[i]);
        printf("Result : %d\n", result[i]);
        clock_t start = clock();
        clock_gettime(CLOCK_MONOTONIC, &startTime);
        solve(0, 0, result[i], size[i]);
        clock_t end = clock();
        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = (finish.tv_sec - startTime.tv_sec);
        elapsed += (finish.tv_nsec - startTime.tv_nsec) / 1000000000.0;
        double time = ((double)end - start) / CLOCKS_PER_SEC;
        printf("Time of exec : %f s\n", elapsed);
        printf("Number of solutions : %d\n", nbSol);
        printf("Time of CPU exec : %f s\n\n", time);
    }
}

void solve(int somme, int i, int z, int size)
{
    if (i < size && somme < z)
    {
        for (int j = 0; j < SIZE_DOMAIN; j++)
        {
            solve(somme + domain[j], i + 1, z, size);
        }
    }
    if (i == size && somme == z)
    {
        nbSol++;
    }
}
