#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	int tempo;
	int i;
	tempo  = time(NULL);
	if(argc>1) tempo = atoi(argv[1]);
	srand(tempo);

	printf("Este programa aceita 0 ou 1 argumento.\n");
	printf("Passe um inteiro como primeiro argumento e ele será usado como seed para o random.\n");

	for(i=0;i<20;i++){
		printf("%d\t", rand()%60);
	} 
	printf("\ntime: %d\n", tempo);
    return 0;
}
