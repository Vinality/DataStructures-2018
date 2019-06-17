#include "priority_queue.h"

int filhoEsq(int i){
	return (2*i + 1);
}

int filhoDir(int i){
	return (2*i + 2);
}

int pai(int i){
	return ((i-1)/2);
}

void swap(T *A, T *B)
{ T t = *A ; *A = *B; *B = t; }

void fixUp(priority_queue *q, int k){
	while (k > 0 && q->comp(q->vetor[pai(k)],q->vetor[k])){
		swap(&(q->vetor[k]), &(q->vetor[pai(k)]));
		k = pai(k);
	}
}

void fixDown(priority_queue *q){
	
}

void inicializar(priority_queue *q, int (*comp)(T,T)){
	q->n = 0;
	q->comp = comp;
}

void inserir(priority_queue *q, T item){
	if(q->n < MAX){
		q->vetor[q->n] = item;
		fixUp(q, q->n);
		q->n++;
	}
}

void remover(priority_queue *q, T* item){
    *item = q->vetor[0];
    q->vetor[0] = q->vetor[MAX]; //talvez max -1?
    q->n--;
    fixDown(q);
}

void prioritario(priority_queue *q, T* item){
	if(q->n > 0)
		*item = q->vetor[0];
}

int tamanho(priority_queue *q){
	return q->n;
}

// VIOLOU O DADO ABSTRATO
void imprimir(priority_queue *q){
	for(int i=0;i<q->n; i++)
		printf("%d ", q->vetor[i].idade );
	printf("\n");
}
