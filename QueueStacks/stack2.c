#include <stdlib.h>
#include <stdio.h>
#include "stack2.h"

void destroyStack(pilha *p){
    if(p->primeiro != NULL){
        no *aux = p->primeiro;
        no *aux2;

        if(aux->prox == NULL){
            free(aux);
        }

        while(aux->prox != NULL){
            aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
        p->primeiro = NULL;
    }
}

void createStack(pilha *p){
    p = (pilha*)malloc(sizeof(pilha));
    p->primeiro = NULL;
    p->indiceparcial = 0;
}

int emptyStack(pilha *p){
    if(p->primeiro == NULL)
        return 1;
    else
        return 0;
}

char popStack(pilha *p){
    no *aux = p->primeiro;
    char a = p->primeiro->a;
    p->primeiro = p->primeiro->prox;
    free(aux);

    if(p->indiceparcial != 0)
        p->indiceparcial--;

    return a;
}

void pushStack(pilha *p, char op){
    no *novo = (no*)malloc(sizeof(no));
    novo->a = op;

    novo->prox = p->primeiro;
    p->primeiro = novo;
    p->indiceparcial++;
}

int stackSize(pilha *p){
    return p->indiceparcial;
}

int stackTop(pilha *p){
    if(p->primeiro != NULL)
        return p->primeiro->a;
    else
        return 0;
}

void printStack(pilha *p){
	no *aux = p->primeiro;
	while(aux != NULL) {
		printf("%c ", aux->a);
		aux = aux->prox;
	}
	printf("\n");
}
