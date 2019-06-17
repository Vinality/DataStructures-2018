#include <stdlib.h>
#include <stdio.h>
#include "queue2.h"

void destroyQueue(fila *f){
    if(f->primeiro != NULL){
        no *aux = f->primeiro;
        no *aux2;

        if(aux->prox == NULL){
            free(aux);
        }

        while(aux->prox != NULL){
            aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
        f->primeiro = NULL;
    }
}

void createQueue(fila *f){
    f = (fila*)malloc(sizeof(fila));
    f->primeiro = NULL;
    f->indiceparcial = 0;
}

int emptyQueue(fila *f){
    if(f->primeiro == NULL)
        return 1;
    else
        return 0;
}

void popQueue(fila *f){
    no *aux = f->primeiro;
    f->primeiro = f->primeiro->prox;
    free(aux);

    if(f->indiceparcial != 0)
        f->indiceparcial--;
}

void putQueue(fila *f, int val){
    no *novo = (no*)malloc(sizeof(no));
    novo->valor = val;
    no *aux = f->primeiro;

    if(f->primeiro == NULL){
        f->primeiro = novo;
        novo->prox = NULL;
    }
    else{
        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
        novo->prox = NULL;
    }

    f->indiceparcial++;
}

int queueSize(fila *f){
    return f->indiceparcial;
}

int queueFirst(fila *f){
    if(f->primeiro == NULL)
        return 0;

    no *aux = f->primeiro;
    while(aux->prox != NULL)
        aux = aux->prox;

    return aux->valor;
}

void printQueue(fila *f){
	no *aux = f->primeiro;
	while(aux != NULL) {
		printf("%d ", aux->valor);
		aux = aux->prox;
	}
	printf("\n");
}

int nElementos(no *p){
    if(p->prox == NULL)
        return 1;
    else{
        return 1 + nElementos(p->prox);
    }
}

// no* menorElemento(no *p){
//     if(p->prox == NULL)
// }

no* menorElemento(no *p){
    no* aux = p;
    no* menor = p;
    while(aux->prox != NULL){
        if(aux->valor < menor->valor)
            menor = aux;

        aux = aux->prox;
    }
    if(aux->valor < menor->valor)
        menor = aux;
    return menor;
}

fila* inverteLista(fila *f){
    if(f->primeiro == NULL)
        return 0;
    if(f->primeiro->prox == NULL)
        return f;

    no* aux = f->primeiro;
    no* ant = NULL;
    no* prox = NULL;

    while(aux != NULL){
        prox = aux->prox;
        aux->prox = ant;
        ant = aux;
        aux = prox;
    }
    f->primeiro = ant;
    return f;
}
