#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define PI 3.1415

void QQ(double a, double b, double e, int n);
void monte_karlo_no();
void monte_karlo();

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

double f(double x) {
  return (25 * sin(x) * sin(x + 2) + (25 * cos(x) + 10) * cos(x + 2)) /
         (25 * cos(x) * cos(x) + 20 * cos(x) + 4);
}

void metod_pram() {
  FILE *f1;
  f1 = fopen("lab_3/test_1.txt", "w");
  double a = -1, b = 1, e = 1E-5;
  int n = 10000000;
  for (int temp = 2; temp <= 8; temp += 2) {
    double sq[2] = {0, 0}, t = wtime();
#pragma omp parallel num_threads(temp)
    {
      int new = n, k = 0;
      double delta = 1;
      for (; delta > e; new *= 2, k ^= 1) {
        double h = (b - a) / new, s = 0.0;
        sq[k] = 0;
#pragma omp barrier
#pragma omp for nowait
        for (int i = 1; i <= new; ++i) {
          s += f(a + h * (i + 0.5));
        }
#pragma omp atomic
        s *= h;
#pragma omp barrier
        if (new > n) {
          delta = f(sq[k] - sq[k ^ 1]) / 3.0;
        }
      }
    }
    t = wtime() - t;
    double t1 = wtime();
    QQ(a, b, e, n);
    t1 = wtime() - t1;
    fprintf(f1, "%d %f\n", temp, t1 / t);
  }
  fclose(f1);
}

void QQ(double a, double b, double e, int n) {
  double sq[2] = {0, 0};
  int new = n, k = 0;
  double delta = 1;
  for (; delta > e; new *= 2, k ^= 1) {
    double h = (b - a) / new, s = 0.0;
    sq[k] = 0;
    for (int i = 1; i <= new; ++i) {
      s += f(a + h * (i + 0.5));
    }
    s *= h;
    if (new > n) {
      delta = f(sq[k] - sq[k ^ 1]) / 3.0;
    }
  }
}

double ff(double x, double y) { return x / (y * y); }

double getrand() { return (double)rand() / RAND_MAX; }

double ggetrand(unsigned int *seed, int flag) {
  if (flag) {
    return (double)rand_r(seed) / RAND_MAX + (rand_r(seed) % 3) + 2.0;
  } else {
    return (double)rand_r(seed) / RAND_MAX;
  }
}

void monte_karlo() {
  FILE *f1 = fopen("lab_3/test_2.txt", "w");
  for (int temp = 2; temp <= 8; temp += 2) {
    int n = 10000000, in = 0;
    double s = 0;
    double t = wtime();
#pragma omp parallel num_threads(temp)
    {
      double s_loc = 0;
      int in_loc = 0;
      unsigned int seed = omp_get_thread_num();
#pragma omp for nowait
      for (int i = 0; i < n; ++i) {
        double x = ggetrand(&seed, 0);
        double y = ggetrand(&seed, 1);
        if (y > 2) {
          in_loc++;
          s_loc += ff(x, y);
        }
      }
#pragma omp atomic
      s += s_loc;
#pragma omp atomic
      in += in_loc;
    }
    double v = in / n;
    double res = v * s / in;
    t = wtime() - t;
    double t1 = wtime();
    monte_karlo_no();
    t1 = wtime() - t1;
    printf("Количество потоков = %d\nВремя параллельной программы = %f\nВремя "
           "последовательной "
           "программы = %f\n",
           temp, t, t1);
    fprintf(f1, "%d %f\n", temp, t1 / t);
  }
  fclose(f1);
}

void monte_karlo_no() {
  int n = 10000000, in = 0;
  double s = 0;
  for (int i = 0; i < n; ++i) {
    double x = getrand();
    double y = getrand() * 5;
    if (y > 2) {
      in++;
      s += ff(x, y);
    }
  }
  double v = PI * in / n;
  double res = v * s / in;
}

int main() {
  printf("Метод средних прямоугольников\n");
  metod_pram();
  printf("Метод монте-карло\n");
  monte_karlo();
}
