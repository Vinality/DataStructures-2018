// LISTA 2 - EX1

void largura(No* t){
    fila *queue;
    No *temp = t;

    while(temp){
        printf("%d ", temp->data);

        if(temp->esq)
            put(queue, temp->esq);

        if(temp->dir)
            put(queue, temp->dir);

        temp = get(queue);
    }
}
