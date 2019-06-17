//EX7

int expTree(No *t){
    No *temp = t;
    stack *p;

    while(temp){
        if(isOperand(temp->data))
            if(t->esq || t->dir)
                return 0;

        else if(isOperator(temp->data)){
            if(t->esq && t->dir){
                push(t->esq);
                push(t->dir);
            }
            else
                return 0;
        }
        temp = pop(p);
    }
    return 1;
}
