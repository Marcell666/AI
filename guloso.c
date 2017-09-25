#include <stdio.h>
#include <stdlib.h>
 
// Returns number of bins required using next fit 
// online algorithm
int nextFit(FILE *f, int weight[], int n, int c)
{
   // Initialize result (Count of bins) and remaining
   // capacity in current bin.
   int res = 0, bin_rem = c;

	//fprintf(f,"\n%d\t", res);
	fprintf(f,"    \n");
 
   // Place items one by one
   for (int i=0; i<n; i++)
   {

       // If this item can't fit in current bin
       if (weight[i] > bin_rem)
       {
	//fprintf(f,"-  %d:\t", bin_rem);
	res++;  // Use a new bin
	bin_rem = c - weight[i];
	fprintf(f,"\n");
	//fprintf(f,"\ncaixa numero %d:\t", res);
       }
       else
         bin_rem -= weight[i];
	fprintf(f,"%d\t", i);
   }
	fseek(f, 0, SEEK_SET);	
	fprintf(f,"%d", res);
   return res;
}

int main (){
	int caixaSize;
	int nCaixas, i;
	int somaTudo = 0;
	int *itens;
	FILE *f, *res;
	f = fopen("instancias/Falkenauer_u500_05.txt", "rt");
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
