#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void partition(int *v, int *i, int *j, int low, int high) {
  *i = low;
  *j = high;
  int pivot = v[(low + high) / 2];
  do {
    while (v[*i] < pivot)
      (*i)++;
    while (v[*j] > pivot)
      (*j)--;
    if (*i <= *j) {

      int temp = v[*i];
      v[*i] = v[*j];
      v[*j] = temp;

      // swap(&v[*i], &v[*j]);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

void quicksort(int *v, int low, int high) {
  int i, j;
  partition(v, &i, &j, low, high);
  if (low < j)
    quicksort(v, low, j);
  if (i < high)
    quicksort(v, i, high);
}

void quicksort_tasks(int *v, int low, int high) {
  int i, j;
  int threshold = 1e7;
  partition(v, &i, &j, low, high);
  if (high - low < threshold || (j - low < threshold || high - i < threshold)) {
    if (low < j)
      quicksort_tasks(v, low, j);
    if (i < high)
      quicksort_tasks(v, i, high);
  } else {
#pragma omp task untied
    { quicksort_tasks(v, low, j); }
    quicksort_tasks(v, i, high);
  }
}

int main() {
  FILE *file;
  file = fopen("test.txt", "w");
  int size = 1e9;

  int *ans = malloc(sizeof(int) * size);

  for (int i = 0; i < size; ++i) {
    ans[i] = rand() % 10000;
  }

  double t = 0.0;

  t -= wtime();
  quicksort(ans, 0, size - 1);
  t += wtime();
  for (int temp = 2; temp <= 8; temp += 2) {
    double t_paralel = 0.0;
    int *ans_paralel = malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
      ans_paralel[i] = rand() % 10000;
    }
    t_paralel -= wtime();
#pragma omp parallel num_threads(temp)
    {
      // printf("%d\n", omp_get_num_threads());
#pragma omp single
      quicksort_tasks(ans_paralel, 0, size - 1);
    }
    t_paralel += wtime();

    fprintf(file, "%d %f\n", temp, t * 1.0 / t_paralel);
    printf("Threads = %d\nSpeedup = %f\n", temp, t * 1.0 / t_paralel);
    free(ans_paralel);
  }
  free(ans);
  fclose(file);
}
