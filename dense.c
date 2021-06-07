#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
double *work;

void mul(double **x, double **y) {
  assert(x != y);
  for (int i = 0; i < n; i++) {
    memset(work, 0, sizeof(double) * n);
    for (int k = 0; k < n; k++) {
      for (int j = 0; j < n; j++) {
        work[j] += x[i][k] * y[k][j];
      }
    }
    memcpy(x[i], work, sizeof(double) * n);
  }
}

double **make() {
  double **a = (double **)malloc(sizeof(double *) * n);
  for (int i = 0; i < n; i++) {
    a[i] = (double *)malloc(sizeof(double) * n);
    memset(a[i], 0, sizeof(double) * n);
  }
  return a;
}

void copy(double **a, double **b) {
  for (int i = 0; i < n; i++) {
    memcpy(a[i], b[i], sizeof(double) * n);
  }
}

void clear(double **a) {
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}

int main() {
  scanf("%d%d", &n, &n);

  double **a = make(), **b = make();
  work = (double *)malloc(sizeof(double) * n);

  for (int i = 0; i < n; i++) {
    int j;
    while (scanf("%d", &j), j != -1) {
      --j;
      scanf("%lf", a[i] + j);
      b[i][j] = a[i][j];
    }
  }

  mul(b, a);

  printf("%d %d\n", n, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (b[i][j] < -1e-15 || b[i][j] > 1e-15) {
        printf("%d %lf ", j + 1, b[i][j]);
      }
    }
    printf("-1\n");
  }

  clear(a);
  clear(b);
  free(work);

  return 0;
}
