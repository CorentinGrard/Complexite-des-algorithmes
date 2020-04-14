#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

#define SIZE 5
#define SIZE_DOMAIN 5

typedef struct
{
  int somme;
  int i;
  int z;
  int size;
  int result;
} solve_struct;

void *solve_thread(void *args);
int init(int z, int size);
int solve(int somme, int i, int z, int size);

int size[] = {10, 11, 12, 13, 14};
int result[] = {52, 57, 62, 67, 72};
int domain[] = {2, 3, 5, 7, 9};

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

    int nbSol = init(result[i], size[i]);
    clock_t end = clock();
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - startTime.tv_sec);
    elapsed += (finish.tv_nsec - startTime.tv_nsec) / 1000000000.0;

    printf("Time of exec : %f s\n", elapsed);
    double time = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Number of solutions : %d\n", nbSol);
    printf("Time of CPU exec : %f s\n\n", time);
  }
}

int init(int z, int size)
{
  pthread_t solve_thread_array[SIZE_DOMAIN];
  solve_struct *args_array[SIZE_DOMAIN];
  for (int i = 0; i < SIZE_DOMAIN; ++i)
  {
    solve_struct *args = malloc(sizeof *args);
    args_array[i] = args;
    args->somme = domain[i];
    args->i = 1;
    args->z = z;
    args->size = size;
    args->result = 0;
    if (pthread_create(&solve_thread_array[i], NULL, solve_thread, args))
    {
      // free(args);
      //goto error_handler;
    }
  }
  int nbSol = 0;
  for (int j = 0; j < SIZE_DOMAIN; ++j)
  {
    pthread_join(solve_thread_array[j], NULL);
    nbSol += args_array[j]->result;
    free(args_array[j]);
  }
  return nbSol;
}

void *solve_thread(void *args)
{
  solve_struct *actual_args = args;
  actual_args->result = solve(actual_args->somme, actual_args->i, actual_args->z, actual_args->size);
  return 0;
}

int solve(int somme, int i, int z, int size)
{
  if (i == size && somme == z)
  {
    return 1;
  }
  else if (i == size)
  {
    return 0;
  }
  int k = 0;
  for (int j = 0; j < SIZE_DOMAIN; j++)
  {
    k += solve(somme + domain[j], i + 1, z, size);
  }
  return k;
}
