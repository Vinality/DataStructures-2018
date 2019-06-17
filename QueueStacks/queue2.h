#ifndef QUEUE2_H_
#define QUEUE2_H_
#include <stdlib.h>

typedef struct _fila{
    int valor;
    struct _fila *prox;
}no;

typedef struct {
    no *primeiro;
    int indiceparcial;
}fila;

void createQueue(fila *f);

void destroyQueue(fila *f);

int emptyQueue(fila *f);

void popQueue(fila *f);

void putQueue(fila *f, int v);

int queueSize(fila *f);

int queueFirst(fila *f);

void printQueue(fila *f);

int nElementos(no *p);

no* menorElemento(no *p);

fila* inverteLista(fila *f);

#endif
