//Vinicius Brandao Crepschi   RA: 743601

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avlstr.h"

int max(int a, int b){
    return (a>b)? a : b;
}

int getAltura(arvore *t){
    if(t == NULL)
        return 0;

    return t->altura;
}

arvore* novoNo(char* plv){
    arvore* novo = (arvore*)malloc(sizeof(arvore));
    novo->esq = novo->dir = NULL;
    novo->palavra = plv;
    novo->altura = 1;

    return novo;
}

arvore* rotacionaEE(arvore *A){
    printf("CASO EE\n");
    arvore *B = A->esq;
    A->esq = B->dir;
    B->dir = A;

    A->altura = max(getAltura(A->esq), getAltura(A->dir)+1);
    B->altura = max(getAltura(B->esq), getAltura(B->dir)+1);

    return B;
}

arvore* rotacionaDD(arvore *A){
    printf("CASO DD\n");
    arvore *B = A->dir;
    A->dir = B->esq;
    B->esq = A;

    A->altura = max(getAltura(A->esq), getAltura(A->dir)+1);
    B->altura = max(getAltura(B->esq), getAltura(B->dir)+1);

    return B;
}

arvore* rotacionaED(arvore *A){
    printf("CASO ED\n");
    arvore* B = A->esq;
    arvore* C = B->dir;

    B->dir = C->esq;
    C->esq = B;
    A->esq = C->dir;
    C->dir = A;

    C->altura = max(getAltura(A->esq), getAltura(A->dir)+1);
    B->altura = max(getAltura(B->esq), getAltura(B->dir)+1);

    return C;
}

arvore* rotacionaDE(arvore *A){
    printf("CASO DE\n");
    arvore* B = A->dir;
    arvore* C = B->esq;

    B->esq = C->dir;
    C->dir = B;
    A->dir = C->esq;
    C->esq = A;

    C->altura = max(getAltura(A->esq), getAltura(A->dir)+1);
    B->altura = max(getAltura(B->esq), getAltura(B->dir)+1);

    return C;
}

int getBal(arvore *t){
    if(t == NULL)
        return 0;

    return (getAltura(t->esq) - getAltura(t->dir));
}

arvore* inserir(arvore *t, char* a){
    if(t == NULL){
        return novoNo(a);
    }

    if(strcmp(a, t->palavra) < 0){
        t->esq = inserir(t->esq, a);
    }

    else if(strcmp(a, t->palavra) > 0){
        t->dir = inserir(t->dir, a);
    }

    //Calcula altura na volta da recursao seguida do
    //fator de balanceamento
    int bal = getBal(t);
    t->altura = 1 + max(getAltura(t->esq), getAltura(t->dir));
    printf("b:%d ", bal);

    //Caso Esquerda-Esquerda
    if(bal > 1 && (strcmp(a, t->esq->palavra) < 0)){
        return rotacionaEE(t);
    }

    //Caso Direita-Direita
    if(bal < -1 && (strcmp(a, t->dir->palavra) > 0)){
        return rotacionaDD(t);
    }

    //Caso Esquerda-Direita
    if(bal > 1 && (strcmp(a, t->esq->palavra) > 0)){
        return rotacionaED(t);
    }

    //Caso Direita-Esquerda
    if(bal < -1 && (strcmp(a, t->dir->palavra) < 0)){
        return rotacionaDE(t);
    }

    return t;
}

int busca(arvore *t, char* a){
    arvore *temp = t;
    while(temp){
        if(strcmp(a, t->palavra) < 0)
            temp = temp->esq;
        else if(strcmp(a, t->palavra) > 0)
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
        return minimo(t->esq);
}

void printInOrder(arvore *t){
    if(t == NULL)
        return;

    printInOrder(t->esq);
    printf("%s ", t->palavra);
    printInOrder(t->dir);
}

void printPreOrder(arvore *t){
    if(t == NULL)
        return;

    printf("%s ", t->palavra);
    printPreOrder(t->esq);
    printPreOrder(t->dir);
}

void printPostOrder(arvore *t){
    if(t == NULL) return;

    printPostOrder(t->esq);
    printPostOrder(t->dir);
    printf("%s ", t->palavra);
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
