#include <stdio.h>

int main(){

    char string[10001];
    int par=0, i, erro=0;

    scanf("%s[ˆ\n]", string);

    for(i=0; string[i] != '\n'; i++){
        if(string[i]=='('){
            par++;
        }

        if(string[i]==')'){
            if(par <= 0){
                erro = 1;
                break;
            }
            par--;
        }
    }

    if(erro == 0 && par == 0)
        printf("correct\n");
    else
        printf("incorrect\n");

    return 0;
}
