#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

struct particle {
  float x, y, z;
};

const float G = 6.67e-11;

omp_lock_t *locks;

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void calculate_forces(struct particle *p, struct particle *f, float *m, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      // Вычисление силы, действующей на тело i со стороны j
      float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) +
                         powf(p[i].z - p[j].z, 2));
      float mag = (G * m[i] * m[j]) / powf(dist, 2);
      struct particle dir = {
          .x = p[j].x - p[i].x, .y = p[j].y - p[i].y, .z = p[j].z - p[i].z};
      // Сумма сил, действующих на тело i
      f[i].x += mag * dir.x / dist;
      f[i].y += mag * dir.y / dist;
      f[i].z += mag * dir.z / dist;
      // Сумма сил, действующих на тело j (симметричность)
      f[j].x -= mag * dir.x / dist;
      f[j].y -= mag * dir.y / dist;
      f[j].z -= mag * dir.z / dist;
    }
  }
}

void move_particles(struct particle *p, struct particle *f, struct particle *v,
                    float *m, int n, double dt) {
  for (int i = 0; i < n; i++) {
    struct particle dv = {
        .x = f[i].x / m[i] * dt,
        .y = f[i].y / m[i] * dt,
        .z = f[i].z / m[i] * dt,
    };
    struct particle dp = {
        .x = (v[i].x + dv.x / 2) * dt,
        .y = (v[i].y + dv.y / 2) * dt,
        .z = (v[i].z + dv.z / 2) * dt,
    };
    v[i].x += dv.x;
    v[i].y += dv.y;
    v[i].z += dv.z;
    p[i].x += dp.x;
    p[i].y += dp.y;
    p[i].z += dp.z;
    f[i].x = f[i].y = f[i].z = 0;
  }
}

void calculate_forces_3(struct particle *p, struct particle *f, float *m,
                        int n) {
#pragma omp for schedule(dynamic, 4) nowait
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) +
                         powf(p[i].z - p[j].z, 2));
      float mag = (G * m[i] * m[j]) / powf(dist, 2);
      struct particle dir = {
          .x = p[j].x - p[i].x, .y = p[j].y - p[i].y, .z = p[j].z - p[i].z};
      omp_set_lock(&locks[i]);
      f[i].x += mag * dir.x / dist;
      f[i].y += mag * dir.y / dist;
      f[i].z += mag * dir.z / dist;
      omp_unset_lock(&locks[i]);
      omp_set_lock(&locks[j]);
      f[j].x -= mag * dir.x / dist;
      f[j].y -= mag * dir.y / dist;
      f[j].z -= mag * dir.z / dist;
      omp_unset_lock(&locks[j]);
    }
  }
}


int main(int argc, char *argv[]) {
  int n = (argc > 1) ? atoi(argv[1]) : 10;
  struct particle *p = malloc(sizeof(*p) * n); // Положение частиц (x, y, z)
  struct particle *f =
      malloc(sizeof(*f) * n); // Сила, действующая на каждую частицу (x, y, z)
  struct particle *v = malloc(sizeof(*v) * n); // Скорость частицы (x, y, z)
  float *m = malloc(sizeof(*m) * n); // Масса частицы
  for (int i = 0; i < n; i++) {
    p[i].x = rand() / (float)RAND_MAX - 0.5;
    p[i].y = rand() / (float)RAND_MAX - 0.5;
    p[i].z = rand() / (float)RAND_MAX - 0.5;
    v[i].x = rand() / (float)RAND_MAX - 0.5;
    v[i].y = rand() / (float)RAND_MAX - 0.5;
    v[i].z = rand() / (float)RAND_MAX - 0.5;
    m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
    f[i].x = f[i].y = f[i].z = 0;
  }
  double time_0 = 0.0, time_3 = 0.0;
  time_0 -= wtime();
  double dt = 1e-5;
  for (double t = 0; t <= 1; t += dt) { // Цикл по времени (модельному)
    calculate_forces(p, f, m, n);      // Вычисление сил – O(N^2)
    move_particles(p, f, v, m, n, dt); // Перемещение тел O(N)
  }
  time_0 += wtime();

locks = malloc(sizeof(omp_lock_t) * n);
for (int i = 0; i < n; i++)
omp_init_lock(&locks[i]);

FILE *f1 = fopen("test_3.txt", "w");

  for (int temp = 2; temp <= 8; temp += 2) {
    time_3 = 0.0;
    for (int i = 0; i < n; i++) {
      p[i].x = rand() / (float)RAND_MAX - 0.5;
      p[i].y = rand() / (float)RAND_MAX - 0.5;
      p[i].z = rand() / (float)RAND_MAX - 0.5;
      v[i].x = rand() / (float)RAND_MAX - 0.5;
      v[i].y = rand() / (float)RAND_MAX - 0.5;
      v[i].z = rand() / (float)RAND_MAX - 0.5;
      m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
      f[i].x = f[i].y = f[i].z = 0;
    }

    time_3 -= wtime();
#pragma omp parallel num_threads(temp)
    {
      for (double t = 0; t <= 1; t += dt) {
        calculate_forces_3(p, f, m, n);
#pragma omp barrier // Ожидание завершения расчетов f[i]
        move_particles(p, f, v, m, n, dt);
#pragma omp barrier // Ожидание завершения обновления p[i], f[i]
      }
    }
    time_3 += wtime();
    fprintf(f1, "%d %f\n", temp, time_0 * 1.0 / time_3);
  }
  free(m);
  free(v);
  free(f);
  free(p);
  free(locks);  fclose(f1);
}