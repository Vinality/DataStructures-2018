//ex10

node* minimo(node *t){
    node *temp = t;
    while(temp->esq){
        temp = temp->esq;
    }
    return temp;
}
