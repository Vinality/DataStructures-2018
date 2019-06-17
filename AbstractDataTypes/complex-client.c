#include <stdio.h>
#include <stdlib.h>
#include "complex.h"

int main(int argv, char *argc[]){
    if(argv != 5)
        return 0;

    double a1, a2, b1, b2;
    a1 = atoi(argc[1]);
    a2 = atoi(argc[2]);
    b1 = atoi(argc[3]);
    b2 = atoi(argc[4]);

    Complex a = newComplex(a1, a2);
    Complex b = newComplex(b1, b2);
    Complex soma = complexAdd(a, b);
    Complex mult = complexMultiply(a, b);

    printf("Real: %.2lf Imaginario: %.2lfi\n", complexRe(a), complexIm(a));
    printf("Real: %.2lf Imaginario: %.2lfi\n", complexRe(b), complexIm(b));
    printf("Soma A+B: %.2lf + %.2lfi\n", complexRe(soma), complexIm(soma));
    printf("Multiplicação A*B: %.2lf + %.2lfi\n", complexRe(mult), complexIm(mult));
    printf("Modulo A e B: %.2lf, %.2lf\n", complexMod(a), complexMod(b));
    printf("Argumento A e B: %.2lf, %.2lf\n", complexArg(a), complexArg(b));

    destroyComplex(a);
    destroyComplex(b);
    destroyComplex(soma);
    destroyComplex(mult);

    return 0;
}
