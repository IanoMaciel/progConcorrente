/*
   compilar/executar: gcc Q4.c -o Q4 -lpthread && ./Q4
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TH 10
#define TAM 1000

int array[TAM], scala, initial = 0, final = 99;

pthread_mutex_t exclusaoM;

void *multiply(void *idthread);
void printArray(int *array, int initial, int final);

int main(){
	pthread_t threads[TH];
	int thread_id[TH];
    long i;
 
    pthread_mutex_init(&exclusaoM, NULL);
	
	srand(time(NULL));

	for (i = 0;i < TAM; i++)
		array[i] = rand() % 1000 + 1;

	for (i = 0; i < TAM; i++)
		printf ("%d  ",array[i]);
	
	printf ("\n\nInforme um escalar: ");
	scanf ("%d", &scala);

	for (i = 0; i< TH; i++){
		thread_id[i] = i;
		pthread_create(&threads[i], NULL, multiply, &thread_id[i]);
	}
	
	for(i = 0; i <TH; i++)
		pthread_join(threads[i], NULL);

	
	if (array){
		printf ("\n\nResultdado: \n");
		printArray(array,0,999);
	}

	pthread_mutex_destroy(&exclusaoM);

	return 0;
}

void *multiply(void *idthread){
	long id = (long)idthread;
	int i;	
	
	for (i = initial; i<=final; i++){
		pthread_mutex_lock (&exclusaoM);
		array[i] *= scala;
		pthread_mutex_unlock (&exclusaoM);
	}

	initial=final+1;
	
	final+=100;

    pthread_exit(NULL);
	
}

void printArray(int *array, int initial, int final){
	int i;
	for (i = initial; i<=final; i++)
		printf ("%d  ",array[i]);
	
}

