#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

int colocaCaixas(FILE *f, Item **itens, int nItens, int tamCaixa)
{

	//espaço restante numa caixa
	int *restante;
	int qtdCaixas = 0;
	int i,e;
	int tempo = time(NULL);
	srand(tempo);

	restante = (int*) malloc(nItens*sizeof(int));
	if(!restante){
		printf("erro ao alocar restantes\n");
		exit(EXIT_FAILURE);
	}

	//Inicializando

	for(i=0;i<nItens;i++)
		restante[i] = tamCaixa;
	
	//Fim da inicializando

	//fprintf(f,"\n%d\t", res);
	fprintf(f,"    \n");

	qtdCaixas = 1;

	//dispersar
	for(i=0;i<nItens;i++){
		for(e=0;e<qtdCaixas;e++){
			if(itens[i]->peso <= restante[e]){
				itens[i]->caixa = e;
				restante[e] -= itens[i]->peso;
				break;
			}
		}
		if(itens[i]->caixa ==-1){
			qtdCaixas++;
			itens[i]->caixa = e;
			restante[e] -= itens[i]->peso;
		}
	}

	//Encontramos? uma solução! basta colocar num arquivo

	//primeiro deixamos em ordem crescente de caixa;
	sort(itens, nItens, comparaCaixaCrescente);
	
	//então colocamos no arquivo

	//qtdCaixas++;
	fprintf(f, "%d\n", qtdCaixas);
	for(i=0, e=0;i<nItens;i++){

		printf("posOrig:%d\tpeso:%d\tcaixa:%d\n", itens[i]->posOrig, itens[i]->peso, itens[i]->caixa );

		if(itens[i]->caixa != e) fprintf(f, "\n");
		fprintf(f, "%d\t", itens[i]->posOrig);
		e = itens[i]->caixa;
	}
	fprintf(f, "\n");	

	printf("%d\n", tempo);

	for(i=0;i<qtdCaixas;i++) printf("restante[%d] = %d\n", i, restante[i]);
	free(restante);

	return qtdCaixas;
}

int main() {

	int caixaSize;
	int nItens, i;
	int somaTudo = 0;
	int minCaixas;
	Item **itens;
	FILE *f, *res;
	f = fopen("instancias/Falkenauer_t60_00.txt", "rt");
	res = fopen("resultado/resultado.txt", "wt");
	if (!f) {
		printf("erro ao abrir instancia\n");
		exit(EXIT_FAILURE);
	}
	fscanf(f, "%d\n", &nItens);
	fscanf(f, "%d\n", &caixaSize);
	itens = (Item**) malloc(nItens * sizeof(Item*));
	if (!itens) {
		printf("erro ao alocar vetor itens\n");
		exit(EXIT_FAILURE);
	}

	//Inicializando

	for(i=0;i<nItens;i++){
		itens[i] = (Item*) malloc(sizeof(Item));
		if(!itens[i] ){
			printf("erro ao alocar item\n");
			exit(EXIT_FAILURE);
		}
	}

	// Lendo do arquivo e preenchendo o vetor de ITENS.
	for (i = 0;i<nItens;i++) {
		fscanf(f, "%d\n", &(itens[i]->peso));
		itens[i]->posOrig = i;
		itens[i]->caixa = -1;
	}
	// Somando todos os pesos
	for (i = 0;i<nItens;i++) {
		somaTudo += itens[i]->peso;
	}
	minCaixas = somaTudo / caixaSize;
	if(minCaixas*caixaSize<somaTudo) minCaixas++;

	printf("%d\n", colocaCaixas(res, itens, nItens, caixaSize));
	
	printf("soma:\n%d\n", somaTudo);
	printf("tamanho:\n%d\n", caixaSize);
	printf("caixas necessarias:\n%d\n", minCaixas);
	
	for(i=0;i<nItens;i++)
		free(itens[i]);
	free(itens);
	return 0;
}


