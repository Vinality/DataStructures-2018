//Vinicius Brandao Crepschi   RA: 743601

#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int max(int a, int b){
    return (a>b)? a : b;
}

int getAltura(arvore *t){
    if(t == NULL)
        return 0;

    return t->altura;
}

arvore* novoNo(int dado){
    arvore* novo = (arvore*)malloc(sizeof(arvore));
    novo->esq = novo->dir = NULL;
    novo->item = dado;
    novo->altura = 1;

    return novo;
}

arvore* rotacionaDireita(arvore *A){
    arvore *B = A->esq;
    A->esq = B->dir;
    B->dir = A;

    A->altura = max(getAltura(A->esq), getAltura(A->dir))+1;
    B->altura = max(getAltura(B->esq), getAltura(B->dir))+1;

    return B;
}

arvore* rotacionaEsquerda(arvore *A){
    arvore *B = A->dir;
    A->dir = B->esq;
    B->esq = A;

    A->altura = max(getAltura(A->esq), getAltura(A->dir))+1;
    B->altura = max(getAltura(B->esq), getAltura(B->dir))+1;

    return B;
}

arvore* rotacionaED(arvore *A){
    A->esq = rotacionaEsquerda(A->esq);
    return rotacionaDireita(A);
}

arvore* rotacionaDE(arvore *A){
    A->dir = rotacionaDireita(A->dir);
    return rotacionaEsquerda(A);
}

int getBal(arvore *t){
    if(t == NULL)
        return 0;

    return (getAltura(t->esq) - getAltura(t->dir));
}

arvore* inserir(arvore *t, int dado){
    if(t == NULL)
        return novoNo(dado);


    if(dado < t->item)
        t->esq = inserir(t->esq, dado);

    else if(dado > t->item)
        t->dir = inserir(t->dir, dado);

    //fator de balanceamento
    int bal = getBal(t);

    if(bal == 2){
        //Caso EE
        if(dado < t->esq->item)
            t = rotacionaDireita(t);
        //Caso ED
        else
            t = rotacionaED(t);
    }

    else if(bal == -2){
        //Caso DD
        if(dado > t->dir->item)
            t = rotacionaEsquerda(t);
        //Caso DE
        else
            t = rotacionaDE(t);
    }

    t->altura = 1 + max(getAltura(t->esq), getAltura(t->dir));
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

void destruirAvl(arvore *t){
    if(t == NULL)
        return;

    destruirAvl(t->esq);
    destruirAvl(t->dir);

    free(t);
}
