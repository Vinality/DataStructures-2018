#include "heapqueue.h"
#include <stdio.h>

void swap(T *A, T *B)
{ T t = *A ; *A = *B; *B = t; }

void fixUp(priority_queue *q, int k){
    while (k > 0 && q->comp(q->vetor[(k-1)/2], q->vetor[k])){
        swap(&(q->vetor[k]), &(q->vetor[(k-1)/2]));
        k = (k-1)/2;
    }
}

void incializar(priority_queue *q, int (*comp)(T,T)){
    q->n = 0;
    q->comp = comp;
}

void inserir(priority_queue *q, T item){
    if(q->n < MAX){
        q->vetor[q->n] = item;
        q->n++;
        fixUp(q, q->n);
    }
}

void remover(priority_queue *q, T* item){
    //recupera o elemento do topo
    //troca de lugar com elemento da base
    //decrementa n
    //fixDown trademark all rights reserved
}

void prioritario(priority_queue *q, T* item){
    if(q->n > 0)
        *item = q->vetor[0];
}

int tamanho(priority_queue *q){
    return q->n;
}

void imprimir(priority_queue *q){
    for(int i=0; i<q->n; i++){
        printf("%d ", q->vetor[i].idade);
    }
    printf("\n");
}
