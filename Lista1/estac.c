#include <stdlib.h>
#include <string.h>
#include "estac.h"

carro* inserirCarro(char placa[], char marca[], char cor[]){
    carro* novo = (carro*)malloc(sizeof(carro));
    strcpy(novo->placa, placa);
    strcpy(novo->marca, marca);
    strcpy(novo->cor, cor);

    return novo;
}

int removerCarro(carro* a){
    
}
