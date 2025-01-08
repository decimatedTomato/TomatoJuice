#include <stdlib.h>

typedef struct {
    double **mat;
} dmatrix;

dmatrix *dmatrix_init(size_t x, size_t y);
void dmatrix_free(dmatrix *mat);