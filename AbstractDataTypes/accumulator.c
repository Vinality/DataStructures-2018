#include <stdlib.h>
#include <stdio.h>
#include "accumulator.h"

void initialize(acumulator* a){
    a->soma = 0;
    a->qtd = 0;
    a->media = 0;
}

void addDataValue(acumulator* a, double val){
    a->soma += val;
    a->qtd++;
}

double mean(acumulator* a){
    a->media = a->soma/a->qtd;
    return a->media;
}

double value(acumulator* a){
    return a->soma;
}

void toString(acumulator* a, char* str){
    sprintf(str,"%.2lf %.2lf %.2lf\n", a->soma, a->qtd, a->media);
}
