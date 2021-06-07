#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

typedef double **dense;

struct elem {
  int col;
  double val;
};

typedef struct elem elem;

struct sparse_matrix {
  int rows;
  elem **begin;
  elem **mend;
  elem **end;
};

typedef struct sparse_matrix sparse;

void make_sparse(sparse *m) {
  m->rows = n;
  m->begin = (elem **)malloc(sizeof(elem *) * n);
  m->mend = (elem **)malloc(sizeof(elem *) * n);
  m->end = (elem **)malloc(sizeof(elem *) * n);

  for (int j = 0; j < n; j++) {
    m->begin[j] = (elem *)malloc(sizeof(elem));
    m->end[j] = m->begin[j];
    m->mend[j] = m->begin[j] + 1;
  }
}

// Do NOT forget!
void clear_sparse(sparse *m) {
  for (int j = 0; j < m->rows; j++) free(m->begin[j]);
  free(m->begin);
  free(m->mend);
  free(m->end);
}

void append(sparse m, int r, elem x) {
  if (m.end[r] == m.mend[r]) {
    int n = m.mend[r] - m.begin[r];
    elem *tmp = (elem *)malloc(sizeof(elem) * n * 2);
    memcpy(tmp, m.begin[r], sizeof(elem) * n);
    free(m.begin[r]);
    m.begin[r] = tmp;
    m.end[r] = tmp + n;
    m.mend[r] = tmp + n * 2;
  }
  *(m.end[r]++) = x;
}

int comp(const void *p, const void *q) {
  return ((const elem *)p)->col - ((const elem *)q)->col;
}

void make_dense(double ***a) {
  *a = (double **)malloc(sizeof(double *) * n);
  for (int i = 0; i < n; i++) {
    (*a)[i] = (double *)malloc(sizeof(double) * n);
    memset((*a)[i], 0, sizeof(double) * n);
  }
}

void clear_dense(double ***a) {
  for (int i = 0; i < n; i++) {
    free((*a)[i]);
  }
  free(*a);
}

int main() {
  scanf("%d%d", &n, &n);

  sparse a, b;
  make_sparse(&a);
  make_sparse(&b);

  dense c;
  make_dense(&c);

  for (int i = 0; i < n; i++) {
    int j;
    while (scanf("%d", &j), j != -1) {
      --j;
      elem e;
      scanf("%lf", &e.val);
      e.col = i;
      append(a, j, e);
      e.col = j;
      append(b, i, e);
    }
  }

  for (int i = 0; i < n; i++) {
    for (elem *e = a.begin[i]; e != a.end[i]; ++e) {
      for (elem *f = b.begin[i]; f != b.end[i]; ++f) {
        c[e->col][f->col] += e->val * f->val;
      }
    }
  }

  printf("%d %d\n", n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (c[i][j] > 1e-15 || c[i][j] < -1e-15)
        printf("%d %lf ", j + 1, c[i][j]);
    }
    printf("-1\n");
  }

  clear_sparse(&a);
  clear_sparse(&b);
  clear_dense(&c);

  return 0;
}
