/*
	compilar/executar: gcc Q1.c -o Q1 -lpthread && ./Q1
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

int atual = 1; 			// Topo da fila de números
int max = 10; 			// Quantidade de números que serão testados
int qtd_threads = 0; 	// Quantidade de threads definidas
int qtd_execs = 0; 		// Quantidade de execuções
int n_primos = 0;		// Quantidade de números primos encontrados

int primo(int value)
{
	int i = 2;
	while (i < value && value%i != 0) i++;
	return i == value;
}

void *thread_fn(void *threadid)
{
	int *id = (int*) threadid; // Vem como argumento da thread
	int valor = 0; // Pega do espaço compartilhado
	int res = 0;
	while (atual <= max)
	{
		// Tranca o mutex, pega um valor para calcular e soma
		// para a próxima thread executar o próximo numero
		pthread_mutex_lock(&lock);
		valor = atual;
		atual++;
		pthread_mutex_unlock(&lock);

		// Calcula se é primo ou não e imprime o texto respectivo
		res = primo(valor);
		if(res)
		{
			printf("Thread %d: O número %d é primo.\n", *id, valor);
		} else {
			printf("Thread %d: O número %d não é primo.\n", *id, valor);
		}

		// Soma no contador de execuções e caso seja primo soma no
		// contador de primos também
		pthread_mutex_lock(&lock);
		if(res) {
			n_primos++;
		}
		qtd_execs++;
		pthread_mutex_unlock(&lock);

		// Espera até as outras threads executarem
		while (atual <= max && qtd_execs < valor + qtd_threads -1);
	}
}

int main() {
	int n_valores = 0, n_threads = 0, i = 0;

	int* args = (int *) malloc(sizeof(int));
	pthread_t* threads = (pthread_t *) malloc(sizeof(pthread_t));

	pthread_mutex_init(&lock, NULL);

	printf("Digite a quantidade de números a processar: ");
	scanf("%d", &n_valores);
	printf("Digite a quantidade de threads a criar: ");
	scanf("%d", &n_threads);

	max = n_valores;
	qtd_threads = n_threads;
	args = (int *) realloc(args, n_threads * sizeof(int));
	threads = (pthread_t *) realloc(threads, n_threads * sizeof(pthread_t));
	for (i = 0; i < n_threads; i++) {
		args[i] = i;
		pthread_create(&(threads[i]), NULL, thread_fn, &(args[i]));
	}
	for (i = 0; i < n_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&lock);

	printf("O número total de números primos encontrados foi: %d\n", n_primos);
	return 1;
}
