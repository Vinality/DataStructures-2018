#ifndef STACK2_H_
#define STACK2_H_
#include <stdlib.h>

typedef struct _pilha{
    char a;
    struct _pilha *prox;
}no;

typedef struct {
    no *primeiro;
    int indiceparcial;
}pilha;

void createStack(pilha *p);

void destroyStack(pilha *p);

int emptyStack(pilha *p);

char popStack(pilha *p);

void pushStack(pilha *p, char op);

int stackSize(pilha *p);

int stackTop(pilha *p);

void printStack(pilha *p);

void inToPos(char expression[]);

#endif
