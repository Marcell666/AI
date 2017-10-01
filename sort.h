#include <stdio.h>
#include <stdlib.h>

typedef struct item{
	int peso;
	int posOrig;
	int caixa;
}Item;

typedef int (*fCompara)(Item*, Item*);

int comparaPesoCrescente(Item *itemA, Item *itemB);
int comparaPesoDecrescente(Item *itemA, Item *itemB);
int comparaCaixaCrescente(Item *itemA, Item *itemB);
int comparaCaixaDerescente(Item *itemA, Item *itemB);

void sort(Item **itens, int nItens, fCompara compara);
