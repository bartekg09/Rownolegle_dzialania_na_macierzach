#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


int
main(int argc, char ** argv)
{
	int ile_watkow;
	int id_operacji;
	int problem_size;
	FILE * f_tmp;
	FILE * f_wyn;
	matrix_t mac_wyn;
	dane_watku_t * dane_watkow;
	wymiary_t wym_A;
	wymiary_t wym_B;
	
	int i,tmp;
	
	if(argc < 6)
	{
		printf("Za malo argumentow!\nWywolanie programu:\n./a.out macA op macB macW l_watkow\n");
		return -1;
	}
	
	/*checking input matrix files and reading sizes*/
	if(!(f_tmp=fopen(argv[1], "r")))
	{
		printf("Nie moge otworzyc pliku: %s\n", argv[1]);
		return -2;
	}else {
		wym_A = read_wymiary(f_tmp);
		fclose(f_tmp);
	}
	if(!(f_tmp=fopen(argv[3], "r")))
	{
		printf("Nie moge otworzyc pliku: %s\n", argv[3]);
		return -3;
	}else{ 
		wym_B= read_wymiary(f_tmp);	
		fclose(f_tmp);
	}
	
	/*checking and reading of operand*/
	if ( strcmp( argv[2], "+" ) == 0 ) 
		id_operacji = 1;
		
	if ( strcmp( argv[2], "-" ) == 0 )
		id_operacji = 2;
		
	if ( strcmp( argv[2], "dot" ) == 0 )
		id_operacji = 3;
	else
	{
		fprintf(stderr,"Bledny operator\n");
		return(-4);
	}
	
	f_wyn = fopen(argv[4],"a");
	
	/*reading number of threads*/
	ile_watkow= atoi(argv[5]);
	
	/*inicjalization of table of structures for threads*/
	dane_watkow = malloc(ile_watkow * sizeof(dane_watku_t));
	
	/*decomposition*/
	mac_wyn.rn = wym_A.rn;
	mac_wyn.cn = wym_B.cn;
	problem_size= mac_wyn.rn*mac_wyn.cn;
	
	tmp= problem_size/ile_watkow;
	
	for(i=0; i< ile_watkow; dane_watkow[i].dlugosc=0,i++);
	
	for(i=0; i< problem_size % ile_watkow; dane_watkow[i].dlugosc++, i++);
	
	for(i=0; i< ile_watkow; i++)
	{
		dane_watkow[i].dlugosc+= tmp;
		dane_watkow[i].id_operacji=	id_operacji;
		if(i==0)
		{
			dane_watkow[i].poczatek=0;
		} else
		{
			dane_watkow[i].poczatek= dane_watkow[i-1].poczatek + dane_watkow[i-1].dlugosc;
		}
		
		strncpy(dane_watkow[i].f1,argv[1],MAX_NAME);
		strncpy(dane_watkow[i].f2,argv[3],MAX_NAME);	
		
		dane_watkow[i].rn_wyn= mac_wyn.rn;
		dane_watkow[i].cn_wyn= mac_wyn.cn;
	}
	
	
	/*wypisanie danych watkow*/
	for(i=0;i<ile_watkow; i++)
	{
		printf("Watek %i:\npocz-> %i\ndlug-> %i\nid_op->%i\nmac1-> %s\nmac2-> %s\nrn_wyn-> %i\ncn_wyn-> %i\n-----------\n",
				i,dane_watkow[i].poczatek,
				dane_watkow[i].dlugosc,
				dane_watkow[i].id_operacji,
				dane_watkow[i].f1,
				dane_watkow[i].f2,
				dane_watkow[i].rn_wyn,
				dane_watkow[i].cn_wyn);
	}
	
	 	
	/*finalization*/
	fclose(f_wyn);
	
	return 0;
}
