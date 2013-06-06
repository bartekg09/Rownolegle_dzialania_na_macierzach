#include "matrix.h"
#include <stdlib.h>

matrix_t 
read_mt( FILE *p1 )
{
	int i, ts;
	matrix_t nm;

	if( fscanf(p1, "%i x %i", &nm.rn, &nm.cn) != 2 || nm.rn <= 0 || nm.cn <= 0 )
		exit(-1);
	while ( (i = fgetc(p1)) == ' ')
		;

	if ( i != '[')
		exit(-5);

	ts= nm.rn * nm.cn;
/*wczytywanie*/

		for( i=0; i < ts; i++)
		{
			if ( fscanf( p1, "%lf", (&nm.p[i])) != 1);
		}
	
	while( (i= fgetc(p1)) == ' ')
		;
	while( (i= fgetc(p1)) == '\n')
		;

	if( i!= ']')
		exit(-8);
	return nm;
}

matrix_t
suma( matrix_t *a, matrix_t *b )
{

	int i, j, ts;
	matrix_t wynik;
	
	if(a->rn != b->rn && a->cn != b->cn)
	{
		fprintf(stderr, "Nie mozna zsumowac macierzy o roznych wymiarach\n");
		 exit(-5);
	}
	ts= a->rn * a->cn;

	for(i = 0; i < ts; i++)
	{
			(&wynik)->p[i] = a->p[i] + b->p[i];
	}

	wynik.rn= a->rn;
	wynik.cn= a->cn;

	return wynik;
}

matrix_t
roznica( matrix_t *a, matrix_t *b )
{
	int i, ts;
	matrix_t wynik;
	
	if(a->rn != b->rn && a->cn != b->cn)
	{
		fprintf(stderr, "Nie mozna odjac elementow macierzy o roznych wymiarach\n");
		 exit(-5);
	}


	for (i = 0; i < ts; i++)
		(&wynik)->p[i] = a->p[i] - b->p[i];
	
	wynik.rn = a->rn;
	wynik.cn = a->cn;

	return wynik;
}
	
matrix_t 
dot_mt( matrix_t *a, matrix_t *b )
{

	matrix_t wynik;
	int i, j, k;

	if(a->cn != b->rn)
	{
		fprintf(stderr, "Nie mozna pomnozyc takich macierzy (l.kolumn pierwszej powinna rownac sie l.wierszy drudiej)\n");
		exit(-5);
	}

	k=0;

	for(i= 0; i < b->cn; i++, j+= b->cn)
	{
		for(k; j< a->rn; j++, i+= a->rn, k++)
				wynik.p[k]+= a->p[i] * b->p[j];
	}

	wynik.rn = a->rn;
	wynik.cn = b->cn;

	return wynik;
}

void 
print(matrix_t a, FILE * p3)
{
	int i, j, ts;
	ts = a.rn * a.cn;

	fprintf(p3, "%d x %d [\n",a.rn, a.cn);
	for(j=0; j< ts; j+= a.rn){
		for (i = j; i < j+ a.rn; i++) 
			fprintf(p3, "\t%g", a.p[i]);

	fprintf(p3, "\n");
	}

	fprintf(p3, "]\n");
}
