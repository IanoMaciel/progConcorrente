#include <stdio.h>
#include <pthread.h>

int l = 5, c = 4;

int start_routine(int linha []) {
	int resultado = 0;
	for (int j=0; j<c; j++){
		resultado += linha[j];
	}
}

int main() {
	// l = linhas; c = colunas
	// declara como 0 as duas
	
	int entrada;
	int matriz[5][4];
	pthread_t threads[5];
	
	// lê o tamanho da matriz q o usuario quer e define a matriz dinamica

	
	for (int i=0; i<l; i++){
		for (int j=0; j<c; j++){
			printf("Digite o valor da linha %d e coluna %d\n", i, j);
			scanf("%d", &entrada);
			matriz[i][j] = entrada;	
		}
	}
	
	for (int i=0; i<l; i++){
		int soma = pthread_create (&threads[i], NULL, start_routine (l), (void *) matriz[i]);
		printf("Soma da linha: %d\n", soma);
	}
	
return 0;
}