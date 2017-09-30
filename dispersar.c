#include <stdio.h>
#include <stdlib.h>
#include <time.h.h>

typedef struct item{
	int peso;
	int posOrig;
	int caixa;
} Item;



int colocaCaixas(FILE *f, int itensVet[], int nItens, int tamCaixa, int maxLoop, int minCaixas)
{

	//espaço restante numa caixa
	int *restante;
	//vetor de ponteiro para o tipo Item que guarda os itens, note que cada item sabe em que caixa está
	Item **itens;
	int qtdCaixas = 0;
	int i,e;
	int tempo = time(NULL);
	srand(tempo);

	restante = (int*) malloc(n*sizeof(int));
	itens = (Item**) malloc(n*sizeof(Item*));

	//Inicializando

	for(i=0;i<nItens;i++){
		itens[i] = (Item*) malloc(sizeof(Item));
		if(!itens[i] ){
			printf("erro\n");
			exit(EXIT_FAILURE);
		}
		restante[i] = tamCaixa;
	}

	//Transformando os itens em itensVet em instancias da estrutura Item

	for (i=0;i<nItens;i++){
		itens[i]->peso = itensVet[i];
		itens[i]->posOrig = i;
		itens[i]->caixa = -1;
	}
	
	//Fim da inicializando

	//fprintf(f,"\n%d\t", res);
	fprintf(f,"    \n");

	//dispersar
	for(i=0;i<nItens;i++){
		for(e=0;e<qtdCaixas;e++){
			if(itens[i]->peso <= restante[e]){
				itens[i]->caixa = qtdCaixas;
				restante[qtdCaixas] -= itens[i]->peso;
				break;
			}
		}
		if(itens[i].caixa->==-1){
			qtdCaixas++;
			itens[i]->caixa = qtdCaixas;
			restante[qtdCaixas] -= itens[i]->peso;
		}
	}

	//Encontramos? uma solução! basta colocar num arquivo

	qtdCaixas++;
	fprintf(f, "%d\n", qtdCaixas);
	for(i=0;i<qtdCaixas;i++){
		for(e=0;e<posVazia[i];e++){
			fprintf(f, "%d\t", caixas[i][e]);
		}
		fprintf(f, "\n");
	}
	
	printf("%d", tempo);

	free(restante);
	free(caixas);
	free(posVazia);

	return qtdCaixas;
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

	printf("%d\n", colocaCaixas(res, itens, nCaixas, caixaSize));	
	
	for(i=0;i<nCaixas;i++){
		somaTudo+=itens[i];
	}
printf("soma:\n%d\n", somaTudo);
printf("tamanho:\n%d\n", caixaSize);
	printf("caixas necessarias:\n%d\n", somaTudo/caixaSize);

	free(itens);
	return 0;
}

