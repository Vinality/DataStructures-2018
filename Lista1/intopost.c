#include <stdio.h>
#include "stack2.h"

int main(){
    char expression[50];
    printf("INSIRA EXPRESSAO INFIXA:\n");
    scanf("\n%[^\n]s", expression);

    inToPos(expression);
    return 0;
}
