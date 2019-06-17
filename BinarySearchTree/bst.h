//Vinicius Brandao Crepschi   RA: 743601

#ifndef BST_H
#define BST_H

typedef struct _arvore{
    int item;
    int qtd;
    struct _arvore* esq;
    struct _arvore* dir;
} arvore;

arvore* inserir(arvore *t, int dado);
arvore* remover(arvore *t, int dado);
int busca(arvore *t, int dado);
arvore* maximo(arvore *t);
arvore* minimo(arvore *t);
void printInOrder(arvore *t);
void printPreOrder(arvore *t);
void printPostOrder(arvore *t);
unsigned nodeCount(arvore *t);
void destruirBst(arvore *t);

#endif
