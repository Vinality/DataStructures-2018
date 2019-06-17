#include <stdio.h>
#include "listapd.h"

int main(){

    no *f = NULL;
    no *l = NULL;
    no *conc = NULL;
    int valor;

    printf("  0 - Sair\n"
    "1 - Inserir na lista 1\n"
    "2 - Retirar da lista 1\n"
    "3 - Printar listas\n"
    "4 - Quantidade de elementos\n"
    "5 - Inserir na lista 2\n"
    "6 - Retirar da lista 2\n");

    int opc = 1;
    while(opc != 0){
        scanf("%d", &opc);

        switch (opc) {
            case 0: break;
            case 1:
                scanf("%d", &valor);
                inserirLista(valor, &f);
                break;

            case 2:
                if(!listaVazia(&f)){
                    scanf("%d", &valor);
                    removerEle(valor, &f);
                }
                break;

            case 3:
                printaLista(&f);
                printaLista(&l);
                break;

            case 4:
                printf("Numero de elementos na lista: %d\n", listamanho(&f));
                break;

            case 5:
                scanf("%d", &valor);
                inserirLista(valor, &l);
                break;

            case 6:
                if(!listaVazia(&l)){
                    scanf("%d", &valor);
                    removerEle(valor, &l);
                }
                break;
        }
    }
    conc = concatenaListas(&f, &l);
    printf("LISTA CONCATENADA ---------------\n");
    printaLista(&conc);
    destroiLista(&l);
    destroiLista(&f);
    return 0;
}
