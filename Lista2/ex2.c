//EX2

int conta_nos(node *t){
    int qtd = 1;

    if(!t)
        return 0;

    else{
        qtd += conta_nos(t->esq);
        qtd += conta_nos(t->dir);
        return qtd;
    }
}
