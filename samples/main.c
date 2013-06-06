#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


int
main(int argc, char **argv)
{
	/*zmienne*/
	FILE *p1, *p2, *p3;
	
	matrix_t wektor1;
	matrix_t wektor2;

	/*wczytanie plikow z macierzami*/
	if( argc > 1 )
		p1 = fopen ( argv[1], "r" );
	else
	{
		fprintf(stderr, "Nie podales nazwy pliku z 1 macierza\n");
		exit(1);
	}
	if ( p1 == NULL )
	{
		fprintf ( stderr, "Plik wejsciowy %s nie istnieje !\n", argv[1]);
		exit(1);
	}

	if ( argc < 2 )
	{
		fprintf(stderr, "Nie podales operatora dzialania ani pozostalych plikow !\n");
		exit(1);
	}

	if(argc > 3)
		p2 = fopen ( argv[3], "r" );
	else
	{
		fprintf(stderr, "Nie podales nazwy pliku z 2 macierza\n");
		exit(1);
	}
	if ( p2 == NULL )
	{
		fprintf(stderr, "Plik wejsciowy %s nie istnieje !\n", argv[3]);
		exit(1);
	}

	p3 = argc > 4 ? fopen ( argv[4], "w"): stdout;

	/*ladowanie wektorow 1 i 2*/
	
	wektor1= read_mt(p1);
	wektor2= read_mt(p2);

	if ( strcmp( argv[2], "+" ) == 0 ) 
	{
		print( (&suma)( &wektor1, &wektor2 ), p3 );
		return 0;
	}

	if ( strcmp( argv[2], "-" ) == 0 )
	{
		print( (&roznica)( &wektor1, &wektor2 ), p3 );
		return 0;
	}

	if ( strcmp( argv[2], "dot" ) == 0 )
	{
		print( (&dot_mt)( &wektor1, &wektor2 ), p3 );
		return 0;
	}
	else
	{
		fprintf(stderr,"Bledny operator\n");
		exit(-6);
	}

	return 0;
}


