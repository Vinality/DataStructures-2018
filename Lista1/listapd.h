#ifndef LISTPD_H_
#define LISTPD_H_
#include <stdlib.h>

typedef struct _no{
    int valor;
    struct _no *prox;
}no;

int inserirLista(int v, no **l);
int listaVazia(no **l);
int removerEle(int v, no **l);
int listamanho(no **l);
void printaLista(no **l);
void destroiLista(no **l);
no* concatenaListas(no **f, no **l);

#endif
