#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "counter.h"

int main(int argc, char* argv[]) {
	
	if(argc != 2) return 1;
	
	srand (time(NULL));
	
	int flips = atoi(argv[1]);
	
	counter *h = initialize("heads");
	counter *t = initialize("tails");
	
	for(int i = 0; i < flips; i++) {
		if( rand()%2 )
			increment(h);
		else
			increment(t);
	}
	
	char msg[512];
	toString(h,msg);
	printf("%s", msg);
	toString(t,msg);
	printf("%s", msg);
	
	int d = tally(h) - tally(t);
	printf("Delta: %d\n", d);
	
	destroy(h);
	destroy(t);
	
	return 0;
}
