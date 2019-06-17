#ifndef ESTAC_H_
#define ESTAC_H_
#include <stdlib.h>

typedef struct _carro{
    char placa[8];
    char marca[30];
    char cor[20];
}carro;

carro* inserirCarro(char placa[], char marca[], char cor[]);
int removerCarro(carro* a);
int buscarCarro(carro* a);
void editarCarro(carro* a);

#endif
