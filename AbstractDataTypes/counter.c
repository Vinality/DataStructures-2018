#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include "counter.h"

counter* initialize(char* id) {
	counter* c = (counter*)malloc(sizeof(counter));
	strcpy(c->id,id);
	c->atual = 0;
}

void increment(counter* c) {
	c->atual++;
}

int	tally(counter* c) {
	return c->atual;
}

void toString(counter* c, char* str) {
	sprintf(str,"%d %s\n",c->atual, c->id);
}

void destroy(counter* c) {
	free(c);
}
