//Vinicius Brandao Crepschi   RA: 743601

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){

    arvore *arvore = NULL;
    int opc, n;
    printf("AVL 1.0\n \n"
           "0- Sair\n"
           "1- Inserir na arvore\n"
           "2- Remover da arvore\n"
           "3- Buscar na arvore\n"
           "4- Maior termo da arvore\n"
           "5- Menor termo da arvore\n"
           "6- Imprimir em In order\n"
           "7- Imprimir em Pre order\n"
           "8- Imprimir em Post order\n"
           "9- Numero de nos\n");

    scanf("%d", &opc);

    while(opc != 0){
        switch (opc) {
            case 1:
                printf("Valor a inserir:\n");
                scanf("%d", &n);
                arvore = inserir(arvore, n);
                printf("Inserido com sucesso\n");
                break;

            case 2:
                printf("Valor a remover:\n");
                scanf("%d", &n);
                arvore = remover(arvore, n);
                break;

            case 3:
                printf("Valor a ser buscado:\n");
                scanf("%d", &n);
                if(busca(arvore, n))
                    printf("Valor encontrado na arvore\n");
                else
                    printf("Valor não se encontra na arvore\n");
                break;

            case 4:
                printf("O maior termo da arvore é: %d\n", maximo(arvore)->item);
                break;

            case 5:
                printf("O menor termo da arvore é: %d\n", minimo(arvore)->item);
                break;

            case 6:
                printf("Arvore in order: ");
                printInOrder(arvore);
                printf("\n");
                break;

            case 7:
                printf("Arvore pre order: ");
                printPreOrder(arvore);
                printf("\n");
                break;

            case 8:
                printf("Arvore post order: ");
                printPostOrder(arvore);
                printf("\n");
                break;

            case 9:
                printf("Numero de nos: %d\n", nodeCount(arvore));
                break;
        }
        scanf("%d", &opc);
    }
    destruirAvl(arvore);
    return 0;
}
