#include <stdio.h>
#include "queue.h"

int main(){

    fila *f = inicializa();

    int valor;

    printf("  0 - Sair\n 1 - Inserir na fila\n 2 - Retirar da fila\n 3 - Checar o proximo da fila\n 4 - Printar fila\n");

    int opc = 1;
    while(opc != 0){
        scanf("%d", &opc);

        switch (opc) {
            case 0: break;
            case 1:
                scanf("%d", &valor);
                put(f, valor);
                break;

            case 2:
                printf("Elemento removido: %d\n", pop(f));
                break;

            case 3:
                printf("O elemento no começo da fila é: %d\n", first(f));
                break;

            case 4:
                printaFila(f);
                break;
        }
    }
    destroyQueue(f);
    return 0;
}
