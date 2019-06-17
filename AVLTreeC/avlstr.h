//Vinicius Brandao Crepschi   RA: 743601

#ifndef AVLSTR_H
#define AVLSTR_H

typedef struct _arvore{
    char* palavra;
    int altura;
    struct _arvore* esq;
    struct _arvore* dir;
} arvore;

arvore* inserir(arvore *t, char* a);
int busca(arvore *t, char* a);
arvore* maximo(arvore *t);
arvore* minimo(arvore *t);
void printInOrder(arvore *t);
void printPreOrder(arvore *t);
void printPostOrder(arvore *t);
unsigned nodeCount(arvore *t);
void destruirAvl(arvore *t);

#endif
