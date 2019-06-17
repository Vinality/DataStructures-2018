#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct _fila{
    int v[10];
    int insert, start, qtd;
}fila;

fila* inicializa();

int empty(fila *f);

void put(fila *f, int item);

int pop(fila *f);

int first(fila *f);

void printaFila(fila *f);

void destroyQueue(fila *f);

#endif
