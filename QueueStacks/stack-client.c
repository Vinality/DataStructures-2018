#include <stdio.h>
#include "stack.h"

int main(){

    int pilha[10];
    int valor, topo;
    topo = 0;

    printf("0 - Sair\n 1 - Inserir na pilha\n 2 - Retirar da pilha\n 3 - Checar elemento do topo\n 4 - Printar pilha\n");

    int opc = 1;
    while(opc != 0){
        scanf("%d", &opc);

        switch (opc) {
            case 0: break;
            case 1:
                scanf("%d", &valor);
                if(!full(topo))
                    push(pilha, valor, &topo);
                printf("TOPO %d\n", topo);
                break;

            case 2:
                if(!empty(topo))
                    printf("%d\n", pop(pilha, &topo));
                break;

            case 3:
                printf("O elemento do topo é: %d\n", top(pilha, topo));
                break;

            case 4:
                printaPilha(pilha);
                break;
        }
    }

    return 0;
}
