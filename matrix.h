#ifndef _MATRIX_H
#define _MATRIX_H
#define MAX 100000
#define MAX_NAME 128
#include <stdio.h>


/*struktura przechowujaca cala macierz*/
typedef struct {
	double  **p;			/*matrix values */
	int		rn;				/*liczba wierszy*/
	int		cn;				/*liczba kolumn */
} matrix_t;


/*struktura z danymi dla watku*/
typedef struct {
	int poczatek;			/*id poczotakowego elementu dla watku*/ 
	int dlugosc;			/*liczba kolejnych elementow do przetworzenia*/
	char f1[MAX_NAME];		/*wskaznik do pliku pobrania danych*/
	char f2[MAX_NAME];
	int id_operacji;
	int rn_wyn;
	int cn_wyn;
} dane_watku_t; 


/*struktura przechowujaca wymiary macierzy*/
typedef struct {
	int rn;
	int cn;
} wymiary_t;


/*struktura przechowujaca identyfikatory kolumn i wierszy do zczytania dla watku*/
typedef struct {
	int * rows;
	int * columns;
} count_data;


/*definicje funkcji*/
matrix_t read_mt (FILE *p);

matrix_t suma (matrix_t *a, matrix_t *b);

matrix_t roznica (matrix_t *a, matrix_t *b);

matrix_t dot_mt (matrix_t *a, matrix_t *b);

void print (matrix_t a, FILE * p);

wymiary_t read_wymiary (FILE * f);

double * get_row(int n, char * af);

double * get_column(int n, char * af);

double get_elem(int m, int n, char * af);

#endif
