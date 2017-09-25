#include <stdio.h>
#include <stdlib.h>
 
// Returns number of bins required using next fit 
// online algorithm
int nextFit(FILE *f, int itens[], int n, int c)
{
	int contMaior = 0, contMenor = 0;
	int *maiores, *menores;
	int metade = 375;
	int i,e;
	maiores = (int*) malloc(n*sizeof(int));
	menores = (int*) malloc(n*sizeof(int));
   int res = 0, bin_rem = c;

	//fprintf(f,"\n%d\t", res);
	fprintf(f,"    \n");

	for (i=0; i<n; i++)
	{
		if (itens[i] > metade){
			maiores[contMaior] = itens[i];
			contMaior++;
		}
		else{
			menores[contMenor] = itens[i];
			contMenor++;
		}
	}


	for(i=0;i<contMaior;i++){
		res++;
		bin_rem = c - maiores[i];
		fprintf(f, "\ncaixa numero %d:\n", res);
		fprintf(f, "%d\t", maiores[i]);
       		for(e=0;e<contMenor;e++){
			if(menores[e] != 0 && menores[e] <= bin_rem){
				bin_rem -= menores[e];
				fprintf(f, "%d\t", menores[e]);
				menores[e] = 0;
			}
		}
	}

	for(i=0;i<contMenor;i++){
		if(menores[i] != 0 && menores[i] > bin_rem){
			res++;
			bin_rem = c - menores[i];
			fprintf(f, "\n%d\t", menores[i]);
		}
		else if(menores[i] != 0 && menores[i] <= bin_rem){
			bin_rem -= menores[i];
			fprintf(f, "%d\t", menores[i]);
		}
	}

	fseek(f, 0, SEEK_SET);
	fprintf(f,"%d", res);
	
	free(maiores);
	free(menores);
	
	return res;
}

int main (){
	int caixaSize;
	int nCaixas, i;
	int somaTudo = 0;
	int *itens;
	FILE *f, *res;
	f = fopen("instancias/Falkenauer_t60_00.txt", "rt");
	res = fopen("resultado/resultado.txt", "wt");
	if(!f){
		printf("erro!");
		exit(EXIT_FAILURE);

	}
	fscanf(f, "%d\n", &nCaixas);
	fscanf(f, "%d\n", &caixaSize);
	itens = (int*) malloc(nCaixas*sizeof(int));
	if(!itens){
		printf("erro!");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<nCaixas;i++)
		fscanf(f, "%d\n", itens+i);

	printf("%d\n", nextFit(res, itens, nCaixas, caixaSize));	
	
	for(i=0;i<nCaixas;i++){
		somaTudo+=itens[i];
	}
printf("soma:\n%d\n", somaTudo);
printf("tamanho:\n%d\n", caixaSize);
	printf("caixas necessarias:\n%d\n", somaTudo/caixaSize);

	free(itens);
	return 0;
}
