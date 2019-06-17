#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "date.h"

int main(int argc, char* argv[]) {
	
	if(argc != 4) return 0;
	
	int m = atoi(argv[1]);
	int d = atoi(argv[2]);
	int y = atoi(argv[3]);
	
	date entrada;
	define(&entrada, m,d,y);
	
	char msg[512];
	toString(&entrada,msg);
	printf("%s", msg);
	
	return 0;
}
