#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include <time.h>

void help()
{
	printf("Program należy wykonac z parametrami:\n gen l_kolumn l_wierszy zak_dolny zak_gorny plik_wyjsciowy\n");
	exit(0);
}

matrix_t 
generate_mt( FILE *p1, char ** argv )
{
	int i, j;
	int zakres_dolny;
	int zakres_gorny;

	matrix_t nm;

	nm.rn= atoi(argv[1]);
	nm.cn= atoi(argv[2]);

	zakres_dolny= atoi(argv[3]);
	zakres_gorny= atoi(argv[4]);


/*alokacja pamieci dla tablicy*/
	nm.p = malloc(nm.cn * sizeof *nm.p[i]);

	for (i = 0; i < nm.cn; i++)
		nm.p[i] = malloc(nm.rn * sizeof *nm.p[i]);

/*generowanie*/

	srand(time(NULL));

	for( j=0; j < nm.rn; j++)
	{
		for( i=0; i < nm.cn; i++)
		{
			nm.p[i][j]= zakres_dolny+(((double)rand()/RAND_MAX)*zakres_gorny);
		}
	}

	return nm;
}


void 
print(matrix_t a, FILE * p)
{
	int	i, j;

	fprintf(p, "%d x %d [\n",a.rn, a.cn);

	for (i = 0; i < a.rn; i++) {
		for (j = 0; j < a.cn; j++)
			fprintf(p, "\t%g", a.p[j][i]);
		fprintf(p, "\n");
	}
	fprintf(p, "]\n");
}


int main (int argc, char ** argv)
{
	/*zmienne*/
	matrix_t A;
	FILE *p1;
	
	if(argc < 5){
		help();
	}

	p1 = fopen( argv[5],"w");
	A= generate_mt(p1, argv);
	
	print(A, p1);
	fclose(p1);

	return 0;
}		
