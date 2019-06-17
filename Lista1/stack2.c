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

pilha* createStack(pilha *p){
    p = (pilha*)malloc(sizeof(pilha));
    p->primeiro = NULL;
    p->indiceparcial = 0;

    return p;
}

int emptyStack(pilha *p){
    if(p->primeiro == NULL){
        return 1;
    }
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
}

int stackSize(pilha *p){
    return p->indiceparcial;
}

char stackTop(pilha *p){
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

int isOperator(char a){
    if(a=='+' || a=='-' || a=='*' || a=='/'){
        return 1;
    }
    else
        return 0;
}

int hasPrecedence(char a, char b){
    char prec[4] = {'-', '+', '*', '/'};
    int pre1, pre2;
    for(int j = 0; j<4; j++){
        if(a == prec[j])
            pre1 = prec[j];
        if(b == prec[j])
            pre2 = prec[j];
    }
    if((pre1 == 3 && pre2 == 2) || (pre1 == 2 && pre2 == 3))
        return 1;

    if(pre1 <= pre2){
        return 1;
    }
    else{
        return 0;
    }
}

void inToPos(char expression[]){
    pilha *p = createStack(p);

    for(int i=0; expression[i]!='\0'; i++){
        if(isOperator(expression[i])){
            if(emptyStack(p)){
                pushStack(p, expression[i]);
            }

            else if(hasPrecedence((stackTop(p)), expression[i])){
                while(!emptyStack(p) && hasPrecedence((stackTop(p)), expression[i]))
                    printf("%c", popStack(p));

                pushStack(p, expression[i]);
            }
        }
        else if(expression[i]=='('){
            pushStack(p, expression[i]);
        }

        else if(expression[i]==')'){
            while(!emptyStack(p) && stackTop(p)!='('){
                printf("%c", popStack(p));
            }
        }

        else
            printf("%c", expression[i]);
    }
    while(!emptyStack(p))
        printf("%c", popStack(p));

    printf("\n");
}
