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
read_mt( FILE *f )
{
	int i, j;

	matrix_t nm;

	if( fscanf(f, "%i x %i", &nm.rn, &nm.cn) != 2 || nm.rn <= 0 || nm.cn <= 0 )
		exit(-1);
	while ( (i = fgetc(f)) == ' ')
		;

	if ( i != '[')
		exit(-5);

/*wczytywanie*/
	for( j=0; j<nm.rn; j++)
	{
		for( i=0; i<nm.cn; i++)
		{
			if ( fscanf( f, "%lf", (&nm.p[i][j])) != 1);
		}
	}
	
	while( (i= fgetc(f)) == ' ')
		;
	while( (i= fgetc(f)) == '\n')
		;

	if( i!= ']')
		exit(-8);
	return nm;
}


double*
get_row(int n, char * af)
{
	double * w;
	int i, j, k;
	
	int a;
	int b;
	
	FILE *f = fopen(af, "r");

	if(fscanf(f, "%i x %i", &a, &b) != 2)
		exit(-1);
		
	w = malloc(a*sizeof(double));
	
	while ( (i = fgetc(f)) == ' ')
		;
	
	if ( i != '[')
		exit(-5);
	
	for(j=0; j<n; j++)
	{
		for(k=0; k<a; k++)
		{			
			if(fscanf( f, "%lf", &w[k]) != 1);
	
			while( (i= fgetc(f)) == ' ')
				;	
		}		
		while( (i= fgetc(f)) == '\n')
			;	
	}
	fclose(f);
	return w;
}


double*
get_column(int n, char * af)
{
	double * w;
	int i, j, k;
	
	int a;
	int b;
	
	FILE * f = fopen(af, "r");

	if(fscanf(f, "%i x %i", &a, &b) != 2)
		exit(-1);
		
	w = malloc(b*sizeof(double));
	
	while ( (i = fgetc(f)) == ' ')
		;
	
	if ( i != '[')
		exit(-5);
	
	for(j=0; j<b; j++)
	{
		for(k=0; k<n; k++)
		{			
			if(fscanf( f, "%lf", &w[j]) != 1);
	
			while( (i= fgetc(f)) == ' ')
				;
			if(i==EOF)
				return w;	
		}
		
		while((i= fgetc(f)) == '\n')
		{
			if(i==EOF)
				break;	
		}	
	}
	fclose(f);
	return w;		
}


double
get_elem(int m, int n, char * af)
{
	double elem;
	int i,j,k;
	
	int a;
	int b;
	
	FILE * f = fopen(af, "r");
	
	if(fscanf(f, "%i x %i", &a, &b) != 2)
		exit(-1);
	
	while ( (i = fgetc(f)) == ' ')
		;
	
	if ( i != '[')
		exit(-5);
		
	for(j=0; j<n; j++)
	{
		for(k=0; k<m; k++)
		{			
			if(fscanf(f, "%lf", &elem) != 1)
				;
	
			while((i= fgetc(f)) == ' ')
				;
		}
		
		while((i= fgetc(f)) != '\n')
		{
			if(i==EOF)
				break;	
		}
			
		while((i= fgetc(f)) == '\n')
		{
			if(i==EOF)
				break;	
		}				
	}
	fclose(f);
	return elem;		
}
