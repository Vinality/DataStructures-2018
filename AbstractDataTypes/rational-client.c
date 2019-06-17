#include <stdio.h>
#include <stdlib.h>
#include "rational.h"

int main(int argc, char *argv[]){
    int numerador1, numerador2, denominador1, denominador2;
    char str[50];

    if(argc != 5)
        return 0;

    numerador1 = atoi(argv[1]);
    denominador1 = atoi(argv[2]);
    numerador2 = atoi(argv[3]);
    denominador2 = atoi(argv[4]);

    rational a = define(numerador1, denominador1);
    rational b = define(numerador2, denominador2);

    rational soma = plus(a,b);
    toString(soma, str);
    printf("SOMA: %s\n", str);

    rational sub = minus(a,b);
    toString(sub, str);
    printf("SUB: %s\n", str);

    rational multi = times(a,b);
    toString(multi, str);
    printf("MULT: %s\n", str);

    rational divi = divides(a,b);
    toString(divi, str);
    printf("DIVI: %s\n", str);

    if(equals(a,b))
        printf("SAO IGUAIS!!\n");
}
