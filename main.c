#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include <pthread.h>
#include <time.h>

static void *
dot_part(void *args)
{
	void * r = NULL;
	
	int i,j,k;
	int tmp;
	int tmp2;
	
	int flag=0;
	int ile_kolumn;
	int ile_wierszy;
	
	int id_in_kolumny;
	int id_in_wiersze;
	
	double ** wiersze;
	double ** kolumny;
	
	clock_t start, finish;
	
	//double * wiersz_tmp;
	//double * kolumna_tmp;
	
	wymiary_t a;
	//wymiary_t b;
	
	dane_watku_t dane_watku= *(dane_watku_t*)args;
	
	int * id_wierszy= malloc(dane_watku.rn_wyn*sizeof(int));
	int * id_kolumn = malloc(dane_watku.cn_wyn*sizeof(int));
	
	/*wydruk kontrolny danych w watku*/
	/*printf("Watek %i:\npocz-> %i\ndlug-> %i\nid_op->%i\nmac1-> %s\nmac2-> %s\nrn_wyn-> %i\ncn_wyn-> %i\n-----------\n",
				dane_watku.id_operacji,
				dane_watku.poczatek,
				dane_watku.dlugosc,
				dane_watku.id_operacji,
				dane_watku.f1,
				dane_watku.f2,
				dane_watku.rn_wyn,
				dane_watku.cn_wyn);
	*/
	
	/*-1 będzie oznaczeniem konca wczytywanych liczb*/
	for(i=0; i< dane_watku.rn_wyn; i++)
		id_wierszy[i]= -1;

	for(i=0; i< dane_watku.cn_wyn; i++)
		id_kolumn[i]= -1;
		
	printf("Watek: %i: Ustawilem id watku i id kolumn na -1\n", dane_watku.id_operacji);		
		
		
	/*zczytywanie identyfikatorwo potrzebnych wierszy i kolumn*/
	
	for(i=0, j=dane_watku.poczatek; j<dane_watku.poczatek+dane_watku.dlugosc; j++)
	{
		tmp = j/dane_watku.cn_wyn;
		for(k=0;k<i;k++)
		{
			if(id_wierszy[k]==tmp)
			{
				flag=1;
			}
		}
		
		if(flag!=1)
		{
			id_wierszy[i]= tmp;
			i++;
		}
		
		flag=0;
	}
	
	printf("Watek: %i: Zczytalem identyfikatory wierszy\n", dane_watku.id_operacji);	
	
	ile_wierszy=i;
	//id_wierszy= realloc(id_wierszy, (size_t)ile_wierszy);
	
	for(i=0, j=dane_watku.poczatek; j<dane_watku.poczatek+dane_watku.dlugosc; j++)
	{
		tmp = j%dane_watku.cn_wyn;
		for(k=0;k<i;k++)
		{
			if(id_kolumn[k]==tmp)
			{
				flag=1;
			}
		}
		
		if(flag!=1)
		{
			id_kolumn[k]= tmp;
			i++;
		}
		
		flag=0;
	}	
	ile_kolumn=i;
	
	printf("Watek: %i: Zczytalem identyfikatory kolumn\n", dane_watku.id_operacji);	
	
	//id_kolumn= realloc(id_kolumn, (size_t)ile_kolumn);
	
	/*wydruk kontrolny wierszy i kolumn po redukcji ich id*/
	/*
	printf("Po redukcji potrzebne sa wiersze i kolumny:\n");
	for(i=0; i<ile_wierszy; i++)
	{
		printf("w%i\n", id_wierszy[i]);
	}
	
	for(i=0; i<ile_kolumn; i++)
	{
		printf("k%i\n", id_kolumn[i]);
	}
	*/
	/* czytanie kolumn z pliku według id */
	
	printf("Watek: %i: Pobieram wiersze wedlug id\n", dane_watku.id_operacji);	
	wiersze= malloc(sizeof(double*)*ile_wierszy);
	for(i=0; i<ile_wierszy; i++)
	{
		wiersze[i]= get_row(id_wierszy[i]+1,dane_watku.f1);
	}
	printf("Watek: %i: Pobrano wiersze\n", dane_watku.id_operacji);	
	
	kolumny= malloc(sizeof(double*)*ile_kolumn);
	printf("Watek: %i: Pobieram kolumny wedlug id\n", dane_watku.id_operacji);	
	for(i=1; i<ile_kolumn+1; i++)
	{
		kolumny[i-1]= get_column(id_kolumn[i-1]+1,dane_watku.f2);
	}
	printf("Watek: %i: Pobrano kolumny\n", dane_watku.id_operacji);	
	/*wydruk kontrolny zredukowanych wierszy i kolumn*/
	/*
	printf("\nZredukowane tablice wiersze i kolumny:\n");
	for(j=0; j<ile_wierszy; j++){
		printf("Wiersze %i: [ ", j);
		for(i=0; i<dane_watku.cn_wyn; i++)
			printf("%lf ",wiersze[j][i]);
		printf("]\n");
	}
	
	for(j=0; j<ile_kolumn; j++){
		printf("\nKolumny %i: [ ", j);
		for(i=0; i<dane_watku.rn_wyn; i++)
			printf("%lf ",kolumny[j][i]);
		printf("]");
	}
	*/
	
	/*liczenie*/
	start=clock();
	/*pobieranie wymiarow plikow chyba nie beda potrzebne na rzecz tmp i tmp2*/
	a= read_wymiary(dane_watku.f1);
	//b= read_wymiary(dane_watku.f2);
	
	printf("Watek: %i: Rozpoczynam liczenie swojej czesci\n", dane_watku.id_operacji);	
	/*dla kazdego elementu*/
	for(i=dane_watku.poczatek; i<dane_watku.poczatek+dane_watku.dlugosc;i++)
	{
		tmp  = i/dane_watku.cn_wyn; /*id_wiersza elem*/
		tmp2 = i%dane_watku.cn_wyn; /*id_kolumny elem*/
		
		//printf("el. w%i,k%i\n",tmp,tmp2);
		
		/*odnajdowanie id_kolumny w tablicy id_kolumn*/
		for(k=0; k<ile_kolumn; k++)
		{
			if(id_kolumn[k]==tmp2)
			{
				id_in_kolumny= k;
				break;
			}
			if(k==ile_kolumn-1 && id_kolumn[k]!=tmp2)
			{
				printf("Error, nie ma kolumny o id %i w pamieci\n",tmp2);
				exit(-1);
			}
		}
		
		for(k=0; k<ile_wierszy; k++)
		{
			if(id_wierszy[k]==tmp)
			{
				id_in_wiersze= k;
				break;
			}
			if(k==ile_wierszy-1 && id_wierszy[k]!=tmp)
			{
				printf("Error, nie ma wiersza o id %i w pamieci\n",tmp);
				exit(-1);
			}
		}
		
		dane_watku.mac_wyn_dot[tmp][tmp2] = mnoz_wec(wiersze[id_in_wiersze],kolumny[id_in_kolumny],a.cn);
		
	}
	finish=clock();
	(*dane_watku.count_duration)= (double)(finish-start)/(CLOCKS_PER_SEC/1000);
	printf("Watek: %i: Koncze liczenie swojej czesci\n", dane_watku.id_operacji);	
	return (void *)r;
}

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
	
	//double * row_tmp;
	//double * column_tmp;
	//double elem_tmp;
	
	double ** wyniki_dot;
	
	double * count_durations;
	clock_t start, finish;
	double duration;
	double count_duration= 0;
	

	
	int i,j,tmp;
	
	/*zmienne watkowe*/
	pthread_t * threads;
	//int tab[100]; /*tmp do pozniejszej redukcji*/
	
	if(argc < 6)
	{
		printf("Za malo argumentow!\nWywolanie programu:\n./a.out macA op macB macW l_watkow\n");
		return -1;
	}
	
	start=clock();
	/*checking input matrix files and reading sizes*/
	if(!(f_tmp=fopen(argv[1], "r")))
	{
		printf("Nie moge otworzyc pliku: %s\n", argv[1]);
		return -2;
	}else {
		fclose(f_tmp);
		wym_A = read_wymiary(argv[1]);
	}
	if(!(f_tmp=fopen(argv[3], "r")))
	{
		printf("Nie moge otworzyc pliku: %s\n", argv[3]);
		return -3;
	}else{
		fclose(f_tmp); 
		wym_B= read_wymiary(argv[3]);	
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
	
	count_durations = malloc(ile_watkow * sizeof(double));
	
	start = clock();
	
	
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
		dane_watkow[i].id_operacji=	i/*d_operacji*/;
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
		dane_watkow[i].count_duration= &count_durations[i];
	}
	
	
		
	/*dzialania rownolegle*/
	/*mnozenie*/
	threads = malloc(sizeof(pthread_t)*ile_watkow);
	
	wyniki_dot = malloc(sizeof(double*)*mac_wyn.rn);
	
	for(i=0;i<mac_wyn.rn;i++)
		wyniki_dot[i]=malloc(sizeof(double)*mac_wyn.cn);
	
	for(i=0;i<mac_wyn.rn;i++)
	{
		for(j=0; j<mac_wyn.cn;j++)
		{
			wyniki_dot[i][j]=0;
		}
	}
	
	for(i=0; i< ile_watkow; i++)
	{
		dane_watkow[i].mac_wyn_dot= wyniki_dot;
	}
	
	for(i=0;i<ile_watkow;i++)
	{
		//tab[i]=i;
		pthread_create(&threads[i], NULL, dot_part, (void*)&dane_watkow[i]);
	}
	
	for(i=0; i<ile_watkow;i++)
	{
		pthread_join(threads[i], NULL);
	}	
	
	/*wypisanie danych watkow*/
	/********************************************************************************/
	/*for(i=0;i<ile_watkow; i++)
	{
		printf("Watek %i:\npocz-> %i\ndlug-> %i\nid_op->%i\nmac1-> %s\nmac2-> %s\nrn_wyn-> %i\ncn_wyn-> %i\n-----------\n",
				i,dane_watkow[i].poczatek,
				dane_watkow[i].dlugosc,
				dane_watkow[i].id_operacji,
				dane_watkow[i].f1,
				dane_watkow[i].f2,
				dane_watkow[i].rn_wyn,
				dane_watkow[i].cn_wyn);
	}*/
	
	
	/*sprawdzenie i wypisanie funkcji pobierajacych kolumny*/
	/**********************************************************************************
	row_tmp = get_row(5,argv[1]);
	column_tmp = get_column(5,argv[1]);
	
	printf("Row: [");
	for(i=0; i<mac_wyn.rn; i++)
		printf("%lf, ",row_tmp[i]);
	printf("]\n"); 	
	 
	printf("Column: [\n "); 
	for(i=0; i<mac_wyn.cn; i++)
		printf("%lf\n ",column_tmp[i]);
	printf("]\n"); 	
	
	
	elem_tmp = get_elem(2,5,argv[1]);
	printf("Elem: %lf\n",elem_tmp);	
	
	*/
	/*
	printf("\n\nWynik:\n");
	print_mat_wyn_dot(wyniki_dot,mac_wyn.rn, mac_wyn.cn);
	*/
	
	/*finalization*/
	fclose(f_wyn);
	
	finish = clock();
	
	for(i=0; i<ile_watkow; i++)
	{
		count_duration+= count_durations[i];
	}
	
	duration = (double)(finish-start)/(CLOCKS_PER_SEC/1000);
	printf("\n----------------------------------------------------------------------------\n");
	printf("Czas wykonania programu:		%2.5f 	ms\n", duration);
	printf("Czas obliczeń danych programu:   	%2.5f 	ms\n", count_duration);
	printf("Czas obliczeń działań na plikach:	%2.5f 	ms\n", duration - count_duration);	
	return 0;
}
