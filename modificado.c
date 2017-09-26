#include <stdio.h>
#include <stdlib.h>
 
int colocaCaixas(FILE *f, int itens[], int n, int tamCaixa)
{
   int nCaixas = 0, restante = tamCaixa;

	//fprintf(f,"\n%d\t", nCaixas);
	fprintf(f,"    \n");
 
   // Para cada item
   for (int i=0; i<n; i++)
   {

       // Se não cabe na caixa
       if (itens[i] > restante)
       {
	//fprintf(f,"-  %d:\t", bin_rem);
	nCaixas++;
	restante = tamCaixa - itens[i];
	fprintf(f,"\n");
	//fprintf(f,"\ncaixa numero %d:\t", nCaixas);
       }
       else
         bin_rem -= itens[i];
	fprintf(f,"%d\t", i);
   }
	fseek(f, 0, SEEK_SET);	
	fprintf(f,"%d", nCaixas);
   return Caixas;
}

int main (){
	int caixaSize;
	int nCaixas, i;
	int somaTudo = 0;
	int *itens;
	FILE *f, *nCaixas;
	f = fopen("instancias/Falkenauer_u500_05.txt", "rt");
	nCaixas = fopen("nCaixasultado/nCaixasultado.txt", "wt");
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

	printf("%d\n", colocaCaixas(nCaixas, itens, nCaixas, caixaSize));	
	
	for(i=0;i<nCaixas;i++){
		somaTudo+=itens[i];
	}
printf("soma:\n%d\n", somaTudo);
printf("tamanho:\n%d\n", caixaSize);
	printf("caixas necessarias:\n%d\n", somaTudo/caixaSize);

	free(itens);
	return 0;
}
