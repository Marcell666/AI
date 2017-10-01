#include <stdio.h>
#include <stdlib.h>
#include "sort.h"



int comparaPesoCrescente(Item *itemA, Item *itemB){
	return itemA->peso > itemB->peso;
}
int comparaPesoDecrescente(Item *itemA, Item *itemB){
	return itemA->peso < itemB->peso;
}
int comparaCaixaCrescente(Item *itemA, Item *itemB){
	return itemA->caixa > itemB->caixa;
}
int comparaCaixaDerescente(Item *itemA, Item *itemB){
	return itemA->caixa < itemB->caixa;
}

void sort(Item **itens, int nItens, fCompara compara) {

	int i, j, troca;
	Item *itemAux;

	for (i = 0; i < nItens - 1; i++) {
		troca = 0;
		for (j = 0; j < nItens - i - 1; j++) {
			//printf("vai comparar %d > %d => %d \n", itens[j]->caixa, itens[j+1]->caixa,compara(itens[j],itens[j + 1]));
			if (compara(itens[j],itens[j + 1])) {
				//printf("troca\n");
				itemAux = itens[j];
				itens[j] = itens[j + 1];
				itens[j + 1] = itemAux;
				troca = 1;
			}
		}
		if(!troca)
			break;
	}
}
