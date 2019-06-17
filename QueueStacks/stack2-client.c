#include <stdio.h>
#include "stack2.h"

int main(){

    pilha *p;
    createStack(p);

    char letra;

    printf("  0 - Sair\n 1 - Inserir na pilha\n 2 - Retirar da pilha\n 3 - Checar elemento do topo e tamanho\n 4 - Printar pilha\n");

    int opc = 1;
    while(opc != 0){
        scanf("%d", &opc);

        switch (opc) {
            case 0:
                break;

            case 1:
                scanf(" %c", &letra);
                pushStack(p, letra);
                break;

            case 2:
                if(!emptyStack(p))
                    printf("Elemento removido: %c\n", popStack(p));
                break;

            case 3:
                printf("O elemento do topo é: %c\n", stackTop(p));
                printf("O numero de elementos é: %d\n", stackSize(p)-1);
                break;

            case 4:
                printStack(p);
                break;
        }
    }

    destroyStack(p);
    return 0;
}
