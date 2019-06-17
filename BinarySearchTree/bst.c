//Vinicius Brandao Crepschi   RA: 743601

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

arvore* novoNo(int dado){
    arvore* novo = (arvore*)malloc(sizeof(arvore));
    novo->esq = novo->dir = NULL;
    novo->item = dado;

    return novo;
}

arvore* inserir(arvore *t, int dado){
    if(t == NULL)
        return novoNo(dado);

    if(dado < t->item)
        t->esq = inserir(t->esq, dado);

    else if(dado > t-> item)
        t->dir = inserir(t->dir, dado);

    return t;
}

arvore* remover(arvore *t, int dado){
    if(t == NULL)
        return t;

    if(dado < t->item)
        t->esq = remover(t->esq, dado);

    else if(dado > t->item)
        t->dir = remover(t->dir, dado);

    else{
        if(t->esq == NULL){
            arvore *temp = t->dir;
            free(t);
            return temp;
        }
        else if(t->dir == NULL){
            arvore *temp = t->esq;
            free(t);
            return temp;
        }

        arvore *temp = minimo(t->dir);
        t->item = temp->item;
        t->dir = remover(t->dir, temp->item);
    }
    return t;
}

int busca(arvore *t, int dado){
    arvore *temp = t;
    while(temp){
        if(dado < temp->item)
            temp = temp->esq;
        else if(dado > temp->item)
            temp = temp->dir;
        else //quando dado == t->item
            return 1;
    }
    return 0;
}

arvore* maximo(arvore *t){
    if(t->dir == NULL)
        return t;
    else
        return maximo(t->dir);
}

arvore* minimo(arvore *t){
    if(t->esq == NULL)
        return t;
    else
        return maximo(t->esq);
}

void printInOrder(arvore *t){
    if(t == NULL)
        return;

    printInOrder(t->esq);
    printf("%d ", t->item);
    printInOrder(t->dir);
}

void printPreOrder(arvore *t){
    if(t == NULL)
        return;

    printf("%d ", t->item);
    printInOrder(t->esq);
    printInOrder(t->dir);
}

void printPostOrder(arvore *t){
    if(t == NULL)
        return;

    printInOrder(t->esq);
    printInOrder(t->dir);
    printf("%d ", t->item);
}

unsigned nodeCount(arvore *t){
    int qtd = 1;

    if(!t)
        return 0;

    else{
        qtd += nodeCount(t->esq);
        qtd += nodeCount(t->dir);
        return qtd;
    }
}

int leafCount(arvore *t){
    if(!t)
        return 0;
    if(t->esq == NULL && t->dir == NULL)
        return 1;
    else
        return leafCount(t->esq) + leafCount(t->dir);
}

void destruirBst(arvore *t){
    if(t == NULL)
        return;

    destruirBst(t->esq);
    destruirBst(t->dir);

    free(t);
}
