#include <stdio.h>
#include "queue2.h"

int main(){

    fila *f;
    createQueue(f);

    int valor;

    printf("  0 - Sair\n"
    "1 - Inserir na fila\n"
    "2 - Retirar da fila\n"
    "3 - Checar elemento do topo e tamanho\n"
    "4 - Printar fila\n"
    "5 - Quantidade de elementos\n"
    "6 - Menor elemento \n"
    "7 - Inverter fila\n");

    int opc = 1;
    while(opc != 0){
        scanf("%d", &opc);

        switch (opc) {
            case 0: break;
            case 1:
                scanf("%d", &valor);
                putQueue(f, valor);
                break;

            case 2:
                if(!emptyQueue(f))
                    popQueue(f);
                break;

            case 3:
                printf("O elemento no começo da fila é: %d\n", queueFirst(f));
                printf("O numero de elementos é: %d\n", queueSize(f)-1);
                break;

            case 4:
                printQueue(f);
                break;

            case 5:
                printf("Numero de elementos na lista: %d\n", nElementos(f->primeiro));
                break;

            case 6:
                printf("Menor elemento: %d\n", menorElemento(f->primeiro)->valor);
                break;

            case 7:
                inverteLista(f);
                printf("A lista foi invertida\n");
                break;
        }
    }

    destroyQueue(f);
    return 0;
}
