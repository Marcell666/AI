// Ordena um vetor de ITEMs de forma crescente por peso.
void sortCresc(Item **itens, int nItens) {

	int i, j, troca;
	Item *itemAux;

	for (i = 0; i < nItens - 1; i++) {
		troca = 0;
		for (j = 0; j < nItens - i - 1; j++) {
			if (itens[i]->peso > itens[i + 1]->peso) {
				itemAux = itens[i];
				itens[i] = itens[i + 1];
				itens[i + 1] = itemAux;
				troca = 1;
			}
		}
		if(!troca)
			break;
	}
}

// Ordena um vetor de ITEMs de forma decrescente por peso.
void sortDecr(Item **itens, int nItens) {

	int i, j, troca;
	Item *itemAux;

	for (i = 0; i < nItens - 1; i++) {
		troca = 0;
		for (j = 0; j < nItens - i - 1; j++) {
			if (itens[i]->peso < itens[i + 1]->peso) {
				itemAux = itens[i];
				itens[i] = itens[i + 1];
				itens[i + 1] = itemAux;
				troca = 1;
			}
		}
		if (!troca)
			break;
	}
}
