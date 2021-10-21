#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TH 2 // thread
#define MAX 500

pthread_mutex_t mutex_int;

void *formacrescente(void *threadident){
    int ident = *((int*)threadident);

    printf("Create Thread %d\n", ident);

    int init = 1;
    
    while(init <= MAX){
        pthread_mutex_lock(&mutex_int);
        printf("Thread %d Crescente: %d\n", ident, ++init);
        pthread_mutex_unlock(&mutex_int); 
    }

    pthread_exit(0);

}

void *formadecrescente(void *threadident){
    int ident = *((int*)threadident);
    printf("Create Thread %d\n", ident);

    int init = MAX;
    while(init >= 1){
        pthread_mutex_lock(&mutex_int);
        printf("Thread %d Forma Decrescente: %d\n", ident, --init);
        pthread_mutex_unlock(&mutex_int); 
    }

    // fim da thread
    pthread_exit(0);

}

int main(){
    // declarando as threads
    pthread_t thread1, thread2;

    //identificadores das threads
	int identThread1 = 1;
	int identThread2 = 2;

  
    pthread_mutex_init(&mutex_int, NULL);
	
    // passando argumento para a thread
	pthread_create(&thread1, NULL, formacrescente, (void *)(&identThread1));
	pthread_create(&thread2, NULL, formadecrescente, (void *)(&identThread2));
	
    // esperando ate que a thread especificada termine
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

    //liberando mutex que nao e mais necessario
    pthread_mutex_destroy(&mutex_int);

    return 0;
}