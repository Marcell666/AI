#include <stdio.h>
#include <stdlib.h>
#include <time.h.h>

int colocaCaixas(FILE *f, int itens[], int n, int tamCaixa, int maxLoop, int minCaixas)
{
	
	//quantidade de itens no vetor de maiores no vetor de menores
	int contMaior, contMenor;
	//vamos colocar metade dos elementos no primeiro e metade no segundo
	int *maiores, *menores;
	//espaço restante numa caixa
	int *restante;
	//matriz que guarda os itens em cada caixa
	int **caixas;
	//guarda qual a próxima posição vazia em cada linha da matriz caixas
	int *posVazia;
	int qtdCaixas = 0;
	int i,e;
	int time = time(NULL);
	srand(time);

	contMaior = n/2;
	contMenor = n-contMenor;

	maiores = (int*) malloc(contMaior*sizeof(int));
	menores = (int*) malloc(contMenor*sizeof(int));

	restante = (int*) malloc(n*sizeof(int));
	caixas = (int**) malloc(n*sizeof(int*));
	posVazia = (int*) malloc(n*sizeof(int));

	//Inicializando

	for(i=0;i<n;i++){
		caixas[i] = (int*) malloc(n*sizeof(int));
		if(!caixas[i] ){
			printf("erro\n");
			exit(EXIT_FAILURE);
		}
		restante[i] = tamCaixa;
		posVazia[i] = 0;
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
		posLinhaA = rand()%qtdCaixas;
		posColunaA = rand()%posVazia[qtdCaixas];
		restoAtual = tamCaixa;
		posLinhaB = 0;
		posColunaB = 0;
			for(e=0;e<qtdCaixas;e++){
				for(k=0;k<posVazia[e];k++){
					novoResto = restante -caixas[posLinhaA][posColunaA] - caixas[e][k];
					if(0<= novoResto && novoResto < restante[e]){
					//econtramos um vizinho valido, basta compara-lo com o anterior
					if(novoResto<restoAtual){
						//encontramos um vizinho melhor que o anterior
						restoAtual = resto
						posLinhaB = e;
						posLinhaB = k;
					}
				}
				//Vamos analisar os casos em que retiramos de uma caixa e colocamos em outra separadamente, pode ser que uma caixa com apenas um elemento tenha sido selecionada, nesse caso queremos colocar esse elemento em outra caixa (e esvaziar esta) mesmo que isso nao deixe a caixa na qual vamos colocar muita proxima da capacidade (isto é, mesmo que ela tambem tenha pouco elementos).
				if(caixas[posLinhaA][posColunaA] <= restante[e]){
				//verifica se este vizinho é melhor que o vizinho atual

				//a ordem dos elementos em uma caixa nao importa, então se eu estiver no meio de uma linha e quiser retirar aquele item, eu posso trocar ele com o ultimo elemento da linha e depois colocar em outra caixa.
	//Retirar item de uma caixa so tera prioridade se a caixa da qual eu retiro tiver apenas um item
				}
					

						
			}


	}

50

27 => 23

13 13 => 24

25 => 25

---------------

13 => 37

13 27 => 10

25 =>
			

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
	
	printf("%d", time);

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
