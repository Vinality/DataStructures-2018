#include <stdio.h>
#include <stdlib.h>
#include "accumulator.h"

int main(int argc, char* argv[]){

    if(argc == 1)
        return 0;

    acumulator a;
    initialize(&a);
    int temp = 0;
    char msg[512];

    for(int i = 1; i < argc; i++){
        temp = atoi(argv[i]);
        addDataValue(&a, temp);
        mean(&a);
        toString(&a, msg);
        printf("%s", msg);
    }
}
