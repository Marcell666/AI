#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "sort.h"

//acha um vizinho melhor e muda o estado para ele
void buscaLocal(Item** itens, int nItens, int *restante, int nCaixas, int tamCaixa) {
	Item *itemA;
	int posB;
	int restoAtual, novoResto;
	int temp;
	int i;
	itemA = itens[rand() % nItens];
	posB = -1;
	restoAtual = tamCaixa;

	//Vamos analisar os casos em que retiramos de uma caixa e colocamos em outra separadamente, pode ser que um item caiba em outra caixa que está mais cheia do que a que ele está, nesse caso queremos colocar esse elemento em outra caixa (e esvaziar esta).
	for (i = 0;i<nCaixas;i++) {
		//Se o item cabe na caixa
		// e se ela esta mais cheia do que a atual
		if (itemA->peso < restante[i] && restante[i]<restante[itemA->caixa] + itemA->peso) {
			//coloco esse item naquela caixa e retorno

			/*
			printf("troca de caixa\n");
			printf("restoA: %d\t restoB: %d\t\n", restante[itemA->caixa], restante[i]);
			printf("pesoA: %d\n", itemA->peso);
			printf("caixaA: %d\t caixaB: %d\n", itemA->caixa, i);
			*/

			restante[itemA->caixa] += itemA->peso;
			itemA->caixa = i;
			restante[itemA->caixa] -= itemA->peso;
			return;
		}
	}

	//para cada item
	for (i = 0;i<nItens;i++) {
		//se a caixa para a qual ele vai, vai ficar mais ocupada do que a caixa na qual ele está
		novoResto = restante[itens[i]->caixa] - (itemA->peso - itens[i]->peso);

		if (0 <= novoResto && novoResto < restante[i] && novoResto < restante[itemA->caixa]) {
			//printf("novoResto: %d, pesoA:%d, pesoB:%d, restanteB:%d\n", novoResto, itemA->peso, itens[i]->peso, restante[itens[i]->caixa]);
			//encontramos um vizinho valido e potencialmente melhor que o estado atual, basta compara-lo com o anterior
			if (novoResto<restoAtual) {
				//encontramos um vizinho melhor que o anterior
				restoAtual = novoResto;
				posB = i;
			}
		}
	}
	//verificamos se um vizinho foi encontrado, fazemos a troca e retornamos	
	if (posB == -1) {
		//printf("Nenhum vizinho foi encontrado :(\n");
		return;
	}
	//printf("trocando da caixa %d, peso:%d com item da caixa %d, peso:%d\n", itemA->caixa, itemA->peso, itens[posB]->caixa, itens[posB]->peso);
	temp = itens[posB]->caixa;
	itens[posB]->caixa = itemA->caixa;
	itemA->caixa = temp;
	//printf("agora o restante na caixa %d e %d\n", itemA->caixa, restante[itemA->caixa]);
	//printf("agora o restante na caixa %d e %d\n", itens[posB]->caixa, restante[itens[posB]->caixa]);
	return;
}


int colocaCaixas(FILE *f, Item **itens, int nItens, int tamCaixa, int minCaixas, int maxLoop, int semente)
{
	//quantidade de itens no vetor de maiores e no vetor de menores
	int contMaior, contMenor;
	//vamos colocar metade dos elementos no primeiro e metade no segundo
	Item **maiores, **menores;
	//espaço restante numa caixa
	int *restante;
	int qtdCaixas = 0;
	int i, e;
	int vazias;
	srand(semente);

	//printf("SEED USADO: %d\n", semente);

	restante = (int*)malloc(nItens * sizeof(int));

	//Inicializando

	for (i = 0;i<nItens;i++) {
		restante[i] = tamCaixa;
	}

	sort(itens, nItens, comparaPesoDecrescente);

	//Fim da inicializando

	//divindo itens em dois vetores, um com a primeira metade (maiores valores dentre todos os itens) e outro com a segunda metade (menores valores)

	contMaior = nItens / 2;
	contMenor = nItens - contMaior;

	maiores = itens;
	menores = itens + contMaior;

	//distribuindo entre caixas

	//complementar
	for (i = 0;i<contMaior;i++) {
		maiores[i]->caixa = qtdCaixas;
		restante[qtdCaixas] = tamCaixa - maiores[i]->peso;
		for (e = 0;e<contMenor;e++) {
			if (menores[e]->caixa == -1 && menores[e]->peso <= restante[qtdCaixas]) {
				menores[e]->caixa = qtdCaixas;
				restante[qtdCaixas] -= menores[e]->peso;
			}
		}
		qtdCaixas++;
	}

	//guloso entre os que sobraram
	for (i = 0;i<contMenor;i++) {
		if (menores[i]->caixa == -1) {
			for (e = qtdCaixas;e<nItens;e++) {
				if (menores[i]->peso <= restante[e]) {
					menores[i]->caixa = e;
					restante[e] -= menores[i]->peso;
				}
			}
		}
	}

	//Agora temos uma solução, vamos fazer uma busca local

	for (i = 0;i<maxLoop;i++) {

		if (qtdCaixas == minCaixas) {
			printf("Esncontrado numero solicitado de caixas");
			break;
		}

		buscaLocal(itens, nItens, restante, qtdCaixas, tamCaixa);
	}

	//Encontramos? uma solução! basta colocar num arquivo

	//primeiro deixamos em ordem crescente de caixa;
	sort(itens, nItens, comparaCaixaCrescente);

	//então colocamos no arquivo

	vazias = 0;
	for (i = 0;i<qtdCaixas;i++) {
		if (restante[i] == tamCaixa)vazias++;
	}
	fprintf(f, "%d\n", qtdCaixas - vazias);
	for (i = 0, e = 0;i<nItens;i++) {

		//printf("posOrig:%d\tpeso:%d\tcaixa:%d\n", itens[i]->posOrig, itens[i]->peso, itens[i]->caixa);

		if (itens[i]->caixa != e) fprintf(f, "\n");
		fprintf(f, "%d\t", itens[i]->posOrig+1);
		e = itens[i]->caixa;
	}
	fprintf(f, "\n");
	fprintf(f, "\n%d\n", semente);

	//for (i = 0;i<qtdCaixas;i++) printf("restante[%d] = %d\n", i, restante[i]);
	free(restante);

	return qtdCaixas - vazias;
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
	printf("tamPathB: %d \n", (int)strlen(pathB));
	printf("PathB: %s \n", pathB);
	return pathB;

}
int main(int argc, char **argv) {
	char *resPath;
	char *fPath;
	int caixaSize;
	int nItens, i;
	int somaTudo = 0;
	int minCaixas, maxLoop = 1000;
	int semente;
	Item **itens;
	FILE *f, *res;
	clock_t tic, toc;

	if (argc < 2 || 4 < argc) {
		printf("Modo de uso: ./executavel path/nome_da_instancia\n ou \n");
		printf("Modo de uso: ./executavel path/nome_da_instancia semente\n ou \n");
		printf("Modo de uso: ./executavel path/nome_da_instancia semente max\n");
		printf("Onde 'semente' sera usada na funcao random e 'max' ira controlar o numero maximo de iteracoes ate que uma solucao nao-otima seja aceita.\n");
		exit(EXIT_FAILURE);
	}
	if (argc >= 4)
		maxLoop = atoi(argv[3]);
	if (argc >= 3)
		semente = atoi(argv[2]);
	if (argc == 2)
		semente = time(NULL);

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
		printf("Tentando com .txt...\n");
		fPath = (char*) malloc((strlen(argv[1]) + 4) * sizeof(char));
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
	printf("%d\n", colocaCaixas(res, itens, nItens, caixaSize, minCaixas, maxLoop, semente));

	//encerrando
	printf("Peso total:\n%d\n", somaTudo);
	printf("Tamanho de cada caixa:\n%d\n", caixaSize);
	printf("Estimativa de caixas necessarias:\n%d\n", minCaixas);
	printf("Semente usada:\n%d\n", semente);

	for (i = 0;i<nItens;i++)
		free(itens[i]);
	free(itens);
	toc = clock();
	printf("Tempo de execucao: %f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
	return 0;
}
