#include <stdlib.h>
#include <stdio.h>
#include "listapd.h"

int inserirLista(int v, no **l){
    no *novo = (no*)malloc(sizeof(no));
    novo->valor = v;
    no *aux = *l;

    if(*l == NULL){
        novo->prox = NULL;
        *l = novo;
        return 1;
    }

    while(aux->prox != NULL)
        aux = aux->prox;

    novo->prox = NULL;
    aux->prox = novo;

    return 1;
}

int listaVazia(no **l){
    if(*l == NULL)
        return 1;
    else
        return 0;
}

int removerEle(int v, no **l){
    no *aux = *l;
    if(*l == NULL)
        return 0;

    if(aux->valor == v){
        *l = aux->prox;
        return 1;
    }

    while(aux->prox != NULL){
        if(aux->prox->valor == v){
            if(aux->prox->prox == NULL){
                aux->prox = NULL;
                return 1;
            }
            else{
                aux->prox = aux->prox->prox;
                return 1;
            }
        }
    }
    return 0;
}

int listamanho(no **l){
    no *aux = *l;
    int qtd = 0;
    while(aux != NULL){
        qtd++;
        aux = aux->prox;
    }
    return qtd;
}

void printaLista(no **l){
    no *aux = *l;
    while(aux != NULL){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}


void destroiLista(no **l){
    if(*l != NULL){
        no *aux = *l;
        no *aux2;

        if(aux->prox == NULL){
            free(aux);
        }

        while(aux->prox != NULL){
            aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
        *l = NULL;
    }
}

no* concatenaListas(no **f, no **l){
    int flag = 1;
    no *conc = *f;
    *f = (*f)->prox;
    no *aux = conc;

    while(*f != NULL || *l != NULL){
        if(*f == NULL){
            aux->prox = *l;
            return conc;
        }
        if(*l == NULL){
            aux->prox = *f;
            return conc;
        }

        if(flag){
            aux->prox = *l;
            *l = (*l)->prox;
            aux = aux->prox;
            flag = 0;
        }
        else{
            aux->prox = *f;
            aux = aux->prox;
            *f = (*f)->prox;
            flag = 1;
        }
    }
    return conc;
}
