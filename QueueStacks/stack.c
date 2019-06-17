#include <stdio.h>
#include "stack.h"

int empty(int topo){
    if(topo == 0)
        return 1;
    else
        return 0;
}

int full(int topo){
    if(topo == 10)
        return 1;
    else
        return 0;
}

void push(int s[], int item, int *topo){
    s[*topo] = item;
    *topo = *topo +1;
}

int pop(int s[], int *topo){
    *topo = *topo - 1;
    return s[*topo];
}

int top(int s[], int topo){
    if(topo > 0)
        return s[topo-1];
    else
        return 0;
}

void printaPilha(int s[]){
    for(int i = 0; i < 10; i++){
        printf("%d ", s[i]);
        printf("\n");
    }
}
