#ifndef _MATRIX_H
#define _MATRIX_H
#define MAX 10000
typedef struct {
	double        p[MAX];	/* vector of columns */
	int		rn;
	int		cn;
}		matrix_t;

#include <stdio.h>

matrix_t read_mt (FILE *p);

matrix_t suma (matrix_t *a, matrix_t *b);

matrix_t roznica (matrix_t *a, matrix_t *b);

matrix_t dot_mt (matrix_t *a, matrix_t *b);

void print (matrix_t a, FILE * p);

#endif
