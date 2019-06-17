#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

fila* inicializa(){
    fila *f;
    f=(fila*)malloc(sizeof(fila));
    f->insert = 0;
    f->start = 0;
    f->qtd = 0;

    return f;
}

int empty(fila *f){
    if(f->insert == f->start)
        return 1;
    else
        return 0;
}

void put(fila *f, int item){
    if(f->qtd < 11){
        f->qtd++;
        f->v[f->insert++] = item;
        f->insert = f->insert % 11;
    }
}

int pop(fila *f){
    if(f->qtd > 0){
        f->qtd--;
        f->start++;
        f->start = f->start % 11;
    }
    return f->v[f->start-1];
}

int first(fila *f ){
    return f->v[f->start];
}

void printaFila(fila *f){
    for(int i = f->start; i<f->insert; i++){
        printf("%d ", f->v[i]);
    }
    printf("\n");
}

void destroyQueue(fila *f){
    free(f);
}
