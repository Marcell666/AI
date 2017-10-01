#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "sort.h"

int colocaCaixas(FILE *f, Item **itens, int nItens, int tamCaixa)
{

	//espaço restante numa caixa
	int *restante;
	int qtdCaixas = 0;
	int i, e;

	restante = (int*)malloc(nItens * sizeof(int));
	if (!restante) {
		printf("erro ao alocar restantes\n");
		exit(EXIT_FAILURE);
	}

	//Inicializando

	for (i = 0;i<nItens;i++)
		restante[i] = tamCaixa;

	//Fim da inicializando

	qtdCaixas = 1;

	//dispersar
	for (i = 0;i<nItens;i++) {
		for (e = 0;e<qtdCaixas;e++) {
			if (itens[i]->peso <= restante[e]) {
				itens[i]->caixa = e;
				restante[e] -= itens[i]->peso;
				break;
			}
		}
		if (itens[i]->caixa == -1) {
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
	for (i = 0, e = 0;i<nItens;i++) {
		if (itens[i]->caixa != e) fprintf(f, "\n");
		fprintf(f, "%d\t", itens[i]->posOrig+1);
		e = itens[i]->caixa;
	}
	fprintf(f, "\n");

	free(restante);

	return qtdCaixas;
}
char* criaPath(char *pathA) {
	char *pathB;
	char *inicio;
	char *fim;
	int tamPath;
	inicio = strrchr(pathA, '/');
	fim = strrchr(pathA, '.');
	if (inicio == NULL) inicio = pathA;
	else inicio++;
	if (fim != NULL) *fim = '\0';
	//+4 ".sol" +1 '\0'
	tamPath = strlen("resultado/") + strlen(inicio) + 4 + 1;
	pathB = (char*)malloc(tamPath * sizeof(int));
	strcpy(pathB, "resultado/");
	strcat(pathB, inicio);
	strcat(pathB, ".sol\0");
	printf("tamPathB:%d \n", (int)strlen(pathB));
	printf("PathB:%s \n", pathB);
	return pathB;

}
int main(int argc, char **argv) {
	char *resPath;
	char *fPath;
	int caixaSize;
	int nItens, i;
	int somaTudo = 0;
	int minCaixas;
	Item **itens;
	FILE *f, *res;
	clock_t tic, toc;

	if (argc != 2) {
		printf("Modo de uso: ./executavel path/nome_da_instancia\n");
		exit(EXIT_FAILURE);
	}

	//Abrindo arquivos de entrada e saida

	#ifdef __linux__
		mkdir("resultado", 0777);
	#else
		_mkdir("resultado");
	#endif
	resPath = criaPath(argv[1]);

	f = fopen(argv[1], "rt");
	res = fopen(resPath, "wt");

	if (!f) {
		printf("Erro ao abrir arquivo de entrada\n");
		printf("Arquivo de entrada:\n%s\n", argv[1]);
		printf("Arquivo de saida:\n%s\n", resPath);
		printf("Tentando com .txt ...\n");
		fPath = (char*)malloc((strlen(argv[1]) + 4) * sizeof(char));
		strcpy(fPath, argv[1]);
		strcat(fPath, ".txt");
		f = fopen(fPath, "rt");
		free(fPath);
		if (f) printf("Sucesso!\n");
		else exit(EXIT_FAILURE);
	}
	if (!res) {
		printf("Erro ao abrir arquivo de saida\n");
		printf("Arquivo de entrada:\n%s\n", argv[1]);
		printf("Arquivo de saida:\n%s\n", resPath);
		exit(EXIT_FAILURE);
	}
	free(resPath);
	//iniciando contagem de tempo
	tic = clock();
	//lendo a quantidade de itens
	fscanf(f, "%d\n", &nItens);
	//lendo tamanho da caixa
	fscanf(f, "%d\n", &caixaSize);
	//alocando itens
	itens = (Item**)malloc(nItens * sizeof(Item*));
	if (!itens) {
		printf("Erro ao alocar vetor itens\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0;i<nItens;i++) {
		itens[i] = (Item*)malloc(sizeof(Item));
		if (!itens[i]) {
			printf("Erro ao alocar item\n");
			exit(EXIT_FAILURE);
		}
	}

	// Lendo do arquivo e preenchendo o vetor de itens
	for (i = 0;i<nItens;i++) {
		fscanf(f, "%d\n", &(itens[i]->peso));
		itens[i]->posOrig = i;
		itens[i]->caixa = -1;
	}
	// Procurando uma estimativa de quantas caixas vamos precisar
	// Isso nos da um criterio para o quão bom foi o resultado
	for (i = 0;i<nItens;i++) {
		somaTudo += itens[i]->peso;
	}
	minCaixas = somaTudo / caixaSize;
	if (minCaixas*caixaSize<somaTudo) minCaixas++;

	/* 		Colocando nas caixas 		*/
	printf("%d\n", colocaCaixas(res, itens, nItens, caixaSize));

	//encerrando
	printf("Peso total:\n%d\n", somaTudo);
	printf("Tamanho de cada caixa:\n%d\n", caixaSize);
	printf("Estimativa de caixas necessarias:\n%d\n", minCaixas);

	for (i = 0;i<nItens;i++)
		free(itens[i]);
	free(itens);
	toc = clock();
	printf("Tempo de execucao: %f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
	return 0;
}
