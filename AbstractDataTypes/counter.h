#ifndef COUNTER_H_
#define COUNTER_H_

#define MAX 256

typedef struct _counter {
	char id[MAX];
	int atual;
} counter;

counter* initialize(char* id);

void increment(counter* c);

int	tally(counter* c);

void toString(counter* c, char* str);

void destroy(counter* c);

#endif
