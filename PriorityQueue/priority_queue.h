#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <stdio.h>

#define MAX 100

typedef struct{
	int idade;
	int RA;
}T;

typedef struct{
	int n;
	T vetor[MAX];
	int (*comp)(T,T);
}priority_queue;

void inicializar(priority_queue *q, int (*comp)(T,T));
void inserir(priority_queue *q, T item);
void remover(priority_queue *q, T* item);
void prioritario(priority_queue *q, T* item);
int tamanho(priority_queue *q);

void imprimir(priority_queue *q);


#endif
