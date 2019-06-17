#ifndef STACK_H_
#define STACK_H_

int empty(int topo);

int full(int topo);

void push(int s[], int item, int *topo);

int pop(int s[], int *topo);

int top(int s[], int topo);

void printaPilha(int s[]);

#endif
