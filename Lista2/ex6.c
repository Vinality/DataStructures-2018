//EX6

No* espelho(No* t){
    if(!t)
        return;

    else{
        No* temp;
        espelho(t->dir);
        espelho(t->esq);

        temp = t->esq;
        t->esq = t->dir;
        t->dir = t->esq;
    }
}
