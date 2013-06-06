#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


/*funkcja zczytujaca wymiary macierzy*/
wymiary_t
read_wymiary (FILE * f)
{
	wymiary_t wymiary;
	
	if( fscanf(f, "%i x %i", &wymiary.rn, &wymiary.cn) != 2 
						    			  || wymiary.rn <= 0 
						    			  || wymiary.cn <= 0)
	{
		exit(-1);
	}
	return wymiary;
}


/* funkcja zczytujaca cala macierz*/
matrix_t 
read_mt( FILE *p1 )
{
	int i, j;

	matrix_t nm;

	if( fscanf(p1, "%i x %i", &nm.rn, &nm.cn) != 2 || nm.rn <= 0 || nm.cn <= 0 )
		exit(-1);
	while ( (i = fgetc(p1)) == ' ')
		;

	if ( i != '[')
		exit(-5);

/*wczytywanie*/
	for( j=0; j < nm.rn; j++)
	{
		for( i=0; i < nm.cn; i++)
		{
			if ( fscanf( p1, "%lf", (&nm.p[i][j])) != 1);
		}
	}
	
	while( (i= fgetc(p1)) == ' ')
		;
	while( (i= fgetc(p1)) == '\n')
		;

	if( i!= ']')
		exit(-8);
	return nm;
}

/*funkca wczytujaca dane do liczenia*/
/*count_data
zczytaj_dane(FILE *f1, FILE *f2, dane_watku d_watku)
{
	count_data c_data;
	
	
	return c_data;	
}*/
