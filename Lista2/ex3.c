//EX3

int leafCount(node *t){
    if(!t)
        return 0;
    if(t->esq == NULL && t->dir == NULL)
        return 1;
    else
        return leafCount(t->esq) + leafCount(t->dir);
}
