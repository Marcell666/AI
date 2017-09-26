#include <stdio.h>
#include <stdlib.h>
 
int colocaCaixas(FILE *f, int itens[], int n, int tamCaixa)
{
	//espaço restante numa caixa
	int *restante;
	//matriz que guarda os itens em cada caixa
	int **caixas;
	//guarda qual a próxima posição vazia em cada linha da matriz caixas
	int *posVazia;
	int qtdCaixas = 0;
	int i,e;

	restante = (int*) malloc(n*sizeof(int));
	caixas = (int**) malloc(n*sizeof(int*));
	posVazia = (int*) malloc(n*sizeof(int));

	if(!restante || !caixas || !posVazia ){
		printf("erro\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<n;i++){
		caixas[i] = (int*) malloc(n*sizeof(int));
		if(!caixas[i] ){
			printf("erro\n");
			exit(EXIT_FAILURE);
		}
		restante[i] = tamCaixa;
		posVazia[i] = 0;
	}

	//fprintf(f,"\n%d\t", res);
	fprintf(f,"          \n");

	//sort(itens);

	//Para cada item
	for (i=0; i<n; i++)
	{
		
		//vamos olhar para cada caixa
		for(e=0; e<n; e++){
			//se cabe na caixa
			if(itens[i]<=restante[e]){
				caixas[e][posVazia[e]] = itens[i]; //=i
				restante[e]-= itens[i];
				posVazia[e] += 1;
				if(e>qtdCaixas) qtdCaixas = e;
				//colocamos na caixa e olhamos para o proximo item
				break;
			}
			// se não cabe continuamos o loop e olhamos para a proxima caixa
		}
	}
	qtdCaixas++;
	fprintf(f, "%d\n", qtdCaixas);
	for(i=0;i<qtdCaixas;i++){
		for(e=0;e<posVazia[i];e++){
			fprintf(f, "%d\t", caixas[i][e]);
		}
		fprintf(f, "\n");
	}

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
