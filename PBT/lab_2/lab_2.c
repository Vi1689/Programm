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

void parallel(int n, int m);
void matrix_vector_multiplication(double *a, double *b, double *c, int n, int m,
                                  int FLOW);

void matrix_vector_multiplication_cycle(double *a, double *b, double *c, int n,
                                        int m, int FLOW);

void matrix_vector_multiplication_no(double *a, double *b, double *c, int n,
                                     int m);

void matrix_vector_multiplication_cycle_no(double *a, double *b, double *c,
                                           int n, int m);

void parallel(int n, int m) {
  double *a = malloc(sizeof(*a) * n * m);
  double *b = malloc(sizeof(*b) * m);
  double *c = malloc(sizeof(*c) * n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i * m + j] = i + j;
    }
  }
  for (int i = 0; i < m; ++i) {
    b[i] = i;
  }
  FILE *f1, *f2, *f3, *f4, *f5, *f6;
  f1 = fopen("lab_2/test_1.txt", "a");
  f2 = fopen("lab_2/test_2.txt", "a");
  f3 = fopen("lab_2/test_3.txt", "a");
  f4 = fopen("lab_2/test_4.txt", "a");
  f5 = fopen("lab_2/test_5.txt", "a");
  f6 = fopen("lab_2/test_6.txt", "a");

  for (int i = 2; i <= 8; i += 2) {
    double t = wtime();
    matrix_vector_multiplication(a, b, c, n, m, i);
    t = wtime() - t;
    double t2 = wtime();
    matrix_vector_multiplication_no(a, b, c, n, m);
    t2 = wtime() - t2;
    printf("Number of threads = %d\ntime matrix_vector_multiplication = %f\n",
           i, t);
    switch (n) {
    case 15000:
      fprintf(f1, "%d %f\n", i, t2 / t);
      break;
    case 20000:
      fprintf(f2, "%d %f\n", i, t2 / t);
      break;
    case 25000:
      fprintf(f3, "%d %f\n", i, t2 / t);
      break;
    default:
      printf("Error\n");
      break;
    }
    t = wtime();
    matrix_vector_multiplication_cycle(a, b, c, n, m, i);
    t = wtime() - t;
    t2 = wtime();
    matrix_vector_multiplication_cycle_no(a, b, c, n, m);
    t2 = wtime() - t2;
    printf("Number of threads = %d\ntime matrix_vector_multiplication_cycle = "
           "%f\n",
           i, t);
    switch (n) {
    case 15000:
      fprintf(f4, "%d %f\n", i, t2 / t);
      break;
    case 20000:
      fprintf(f5, "%d %f\n", i, t2 / t);
      break;
    case 25000:
      fprintf(f6, "%d %f\n", i, t2 / t);
      break;
    default:
      printf("Error\n");
      break;
    }
  }

  fclose(f1);
  fclose(f2);
  fclose(f3);
  fclose(f4);
  fclose(f5);
  fclose(f6);

  free(a);
  free(b);
  free(c);
}

void matrix_vector_multiplication(double *a, double *b, double *c, int n, int m,
                                  int FLOW) {
#pragma omp parallel num_threads(FLOW)
  {
    int nthreads = omp_get_num_threads();
    int threadid = omp_get_thread_num();
    int items_per_thread = m / nthreads;
    int lb = threadid * items_per_thread;
    int ub = (threadid == nthreads - 1) ? (m - 1) : (lb + items_per_thread - 1);
    for (int i = lb; i <= ub; i++) {
      c[i] = 0.0;
      for (int j = 0; j < m; j++)
        c[i] += a[i * m + j] * b[j];
    }
  }
}

void matrix_vector_multiplication_no(double *a, double *b, double *c, int n,
                                     int m) {
  for (int i = 0; i < n; i++) {
    c[i] = 0.0;
    for (int j = 0; j < m; j++)
      c[i] += a[i * m + j] * b[j];
  }
}

void matrix_vector_multiplication_cycle(double *a, double *b, double *c, int n,
                                        int m, int FLOW) {
#pragma omp parallel num_threads(FLOW)
  {
    int nthreads = omp_get_num_threads();
    int threadid = omp_get_thread_num();
    for (int i = threadid; i < n; i += nthreads) {
      c[i] = 0.0;
      for (int j = 0; j < m; ++j) {
        c[i] += a[i * m + j] * b[j];
      }
    }
  }
}

void matrix_vector_multiplication_cycle_no(double *a, double *b, double *c,
                                           int n, int m) {
  for (int i = 0; i < n; ++i) {
    c[i] = 0.0;
    for (int j = 0; j < m; ++j) {
      c[i] += a[i * m + j] * b[j];
    }
  }
}

int main() {
  long a = sysconf(_SC_PHYS_PAGES);
  long b = sysconf(_SC_PAGESIZE);
  printf("Размер матрицы = %lli x %lli\nРазмер вектора = %lli\n", a, b, b);
  for (int i = 15000; i <= 25000; i += 5000) {
    int n = i, m = i;
    printf("Размер матрицы = %d x %d\nРазмер вектора = %d\n", n, m, m);
    printf("Memory used: %d MiB\n", ((m * n + m + n) * sizeof(double)) >> 20);
    parallel(n, m);
  }
  return 0;
}
