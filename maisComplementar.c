#include <stdio.h>
#include <stdlib.h>
#include <time.h.h>

typedef struct item{
	int peso;
	int posOrig;
	int caixa;
} Item;

//acha um vizinho melhor e muda o estado para ele
void buscaLocal(Item* itens, int nItens, int *restante, int *nCaixas, int tamCaixa){
	posA = rand()%nItens;
	restoAtual = tamCaixa;
	posB = -1;
	int temp;

//Vamos analisar os casos em que retiramos de uma caixa e colocamos em outra separadamente, pode ser que um item caiba em outra caixa que está mais cheia do que a que ele está, nesse caso queremos colocar esse elemento em outra caixa (e esvaziar esta).
	for(i=0;i<*nCaixas;i++){
		//Se o item cabe na caixa
		if(0 < restante[i] && itens[posA]->peso < restante[i]<= restante[e]){
			// e se ela esta mais cheia do que a atual
			if(restante[i]>restante[posA]+itens[posA]->peso)
				//coloco esse item naquela caixa e retorno
				restante[itens[posA]->caixa] += itens[posA]->peso;
				itens[posA]->caixa = i;
				restante[itens[posA]->caixa] -= itens[posA]->peso;
				printf("troca de caixa\n");
				return 2;
			}
		}
	}

	//para cada item
	for(i=0;i<nItens;i++){
		//se a caixa para a qual ele vai, vai ficar mais ocupada do que a caixa na qual ele está
		novoResto = restante[itens[i]->caixa] - (itens[posA]->peso - itens[i]->peso);
		if(0<= novoResto && novoResto < restante[i] && novoResto < restante[itens[posA]){
		//encontramos um vizinho valido e potencialmente melhor que o estado atual, basta compara-lo com o anterior
		if(novoResto<restoAtual){
			//encontramos um vizinho melhor que o anterior
			restoAtual = novoResto;
			posB = i;
		}		
	}
	//verificamos se um vizinho foi encontrado, fazemos a troca e retornamos	
	if(posB==-1){
		printf("Nenhum vizinho foi encontrado :(\n");
		return 1;
	}
	printf("trocando %d,peso:%d com %d,peso%d\n", posA, itens[posA]->peso, posB, itens[posB]->peso);
	temp = itens[posB]->caixa;
	itens[posB]->caixa = itens[posA]->caixa;
	itens[posA]->caixa = temp; 	
	return 0;
}


int colocaCaixas(FILE *f, int itensVet[], int n, int tamCaixa, int maxLoop, int minCaixas)
{
	
	//quantidade de itens no vetor de maiores e no vetor de menores
	int contMaior, contMenor;
	//vamos colocar metade dos elementos no primeiro e metade no segundo
	int *maiores, *menores;
	//espaço restante numa caixa
	int *restante;
	//vetor de ponteiro para o tipo Item que guarda os itens, note que cada item sabe em que caixa está
	Item **itens;
	int qtdCaixas = 0;
	int i,e;
	int tempo = time(NULL);
	srand(tempo);

	contMaior = n/2;
	contMenor = n-contMenor;

	maiores = (int*) malloc(contMaior*sizeof(int));
	menores = (int*) malloc(contMenor*sizeof(int));

	restante = (int*) malloc(n*sizeof(int));
	itens = (Item**) malloc(n*sizeof(Item*));

	//Inicializando

	for(i=0;i<n;i++){
		itens[i] = (Item*) malloc(sizeof(Item));
		if(!itens[i] ){
			printf("erro\n");
			exit(EXIT_FAILURE);
		}
		restante[i] = tamCaixa;
	}

	//Transformando os itens em itensVet em instancias da estrutura Item

	for (i=0;i<n;i++){
		itens[i]->peso = itensVet[i];
		itens[i]->posOrig = i;
		itens[i]->caixa = -1;
	}

	// TODO sort() AQUI É NECESSARIO!!
	
	//Fim da inicializando

	//fprintf(f,"\n%d\t", res);
	fprintf(f,"    \n");

	//

	//divindo itens em dois vetores, um com a primeira metade (maiores valores dentre todos os itens) e outro com a segunda metade (menores valores)
	//TODO se quiser mudar o criterio de divisão, é aqui que isso acontece.


	for (i=0; i<n; i++)
	{
		if (i<contMaior)
			maiores[i] = itens[i];
		else
			menores[i-contMaior] = itens[i];
	}


	//distribuindo entre caixas

	for(i=0;i<contMaior;i++){
		caixas[qtdCaixas][posVazia] = maiores[i];
		restante[qtdCaixas] = tamCaixa - maiores[i];
       		for(e=0;e<contMenor;e++){
			if(menores[e] != 0 && menores[e] <= restante[qtdCaixas]){
				caixas[qtdCaixas][posVazia[qtdCaixas]] = menores[e];
				restante[qtdCaixas] -= menores[e];
				menores[e] = 0;
				posVazia[qtdCaixas] += 1;
			}
		}
		qtdCaixas++;
	}

	for(i=0;i<contMenor;i++){
		if(menores[i] != 0 && menores[i] > restante){
			res++;
			restante = c - menores[i];
		}
		else if(menores[i] != 0 && menores[i] <= restante){
			restante -= menores[i];
		}
	}

	//Agora temos uma solução, vamos fazer uma busca local

	for(i=0;i<maxLoop;i++){
		if(qtdCaixas == minCaixas){
			printf("encontrado numero solicitado de caixas");
			break;
		}

		ret = buscaLocal(itens, n, &qtdCaixas, restante, tamCaixa);
		if(ret==1) break;
	}
			

	//o que é uma solução aceitavel?
		//parametro para quantas caixas quero
		//parametro para limite de quantas vezes vai rodar
	//posso so rodar X vezes?
		//resposta acima
	//como vou gerar os vizinhos?
		//swap entre elementos dentro de caixas
		//vou escolher um elemento aleatoriamente e vou trocar ele de lugar com todos os vizinhos e tentar colocar em todas as caixas.
	// como vou representar isso?
		//por uma matriz nX4, com n sendo um numero de vizinhos
		//e os 4 valores seriam a posição dos outros dos dois itens na caixa

		//com dois valores e uma matriz mx2 onde m é o numero de vizinhos e 2 as duas colunas são a posição de um item na matriz 
	//como vou escolher um bom vizinho?
		//menor quantidade de caixas. E se for a mesma quantidade?

		//vou escolher um vizinho que tenha feito a caixa B ficar o mais proximo possivel de alcançar a capacidade maxima.
	//Como sei que encontrei uma boa solução?
		//primeira pergunta

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

	free(maiores);
	free(menores);

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

