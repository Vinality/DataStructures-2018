//Vinicius Brandao Crepschi   RA: 743601

#include <stdio.h>
#include <stdlib.h>
#include "avlstr.h"

int main(){
    arvore *t = NULL;
    char plv1[20] = {'a','b'};
    char plv2[20] = {'a','d'};
    // scanf("%s", plv2); //ad
    char plv3[20] = {'e','b'};
    // scanf("%s", plv3); //eb
    char plv4[20] = {'c','b'};
    char plv5[20] = {'g','b'};
    char plv6[20] = {'a','h'};
    char plv7[20] = {'e','a'};

    t = inserir(t, plv1);
    t = inserir(t, plv2);
    t = inserir(t, plv3);
    t = inserir(t, plv4);
    t = inserir(t, plv5);
    t = inserir(t, plv6);
    t = inserir(t, plv7);

    printPreOrder(t);

    destruirAvl(t);

    return 0;
}
