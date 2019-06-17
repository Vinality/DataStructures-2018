#include <stdlib.h>
#include "lista.h"
#include <stdio.h>

void inicializa(Lista *l) {
	l->ini = NULL;
	l->qtd = 0;
}

void insereInicio(Lista *l, T item) {
	No* p = (No*)malloc(sizeof(No));
	p->item = item;
	p->prox = l->ini;
	if(l->ini != NULL)
		l->ini->ant = p;
	p->ant = NULL;
	l->ini = p;
	l->qtd++;
}

void removeInicio(Lista *l, T* item) {
	if(l->ini != NULL) {
		No* p = l->ini;
		l->ini = l->ini->prox;
		l->ini->ant = NULL;
		*item = p->item;
		free(p);
	}
}

Iterador inicio(Lista *l) {
	Iterador it;
	it.p = l->ini;
	it.l = l;
	return it;
}

Iterador fim(Lista *l){
	Iterador it;
	it.p = l->ini;
	it.l = l;
	while(!acabou(&it))
		proximo(&it);

	return it;
}

void elemento(Iterador* it, T* item) {
	if(!acabou(it))
		*item = it->p->item;
}

void proximo(Iterador* it) {
	if( !acabou(it) ) {
		it->p = it->p->prox;
	}
}

void anterior(Iterador* it) {
	if( !acabou(it) ) {
		it->p = it->p->ant;
	}
}

int acabou(Iterador *it) {
	return it->p == NULL;
}

Iterador buscaPrimeiro(Lista* l, T item) {
	Iterador it = inicio(l);
	while( !acabou(&it) ) {
		if( it.p->item == item )
			return it;
		proximo(&it);
	}
	return it;
}

Iterador buscaProximo(Iterador* it, T item) {
	while( !acabou(it) ) {
		if( it->p->item == item )
			return *it;
		proximo(it);
	}
	return *it;
}

void insereDepois(Iterador* it, T item) {
	if(!acabou(it)) {
		No* novo = (No*)malloc(sizeof(No));
		novo->item = item;
		novo->prox = it->p->prox;
		novo->ant = it->p;
		it->p->prox = novo;
		it->l->qtd++;
	}
}

int quantidade(Lista* l) {
	return l->qtd;
}

void insereAntes(Iterador* it, T item) {
	if(!acabou(it)) {
		No* novo = (No*)malloc(sizeof(No));
		novo->item = item;
		novo->prox = it->p;
		it->p->ant = novo;
		if(it->p->ant != NULL){
			novo->ant = it->p->ant;
			it->p->ant->prox = novo;
		}
		else
			novo->ant = NULL;
	}
}

void insereFim(Lista* l, T item){
	No* novo = (No*)malloc(sizeof(No));
	novo->item = item;
	No* aux = l->ini;
	while(aux->prox != NULL)
		aux = aux->prox;

	novo->prox = NULL;
	novo->ant = aux;
	aux->prox = novo;
}

Iterador buscaUltimo(Lista* l, T item){
	Iterador it = fim(l);
	while(!acabou(&it)){
		if(it.p->item == item)
			return it;
		anterior(&it);
	}
	return it;
}

Iterador buscaAnterior(Iterador* it, T item){
	while( !acabou(it) ) {
		if( it->p->item == item )
			return *it;
		anterior(it);
	}
	return *it;
}

void removeDepois(Iterador* it, T* item){
	if(it->p->prox != NULL){
		No* aux = it->p->prox;
		*item = it->p->prox->item;
		it->p->prox = it->p->prox->prox;
		it->p->prox->ant = it->p;
		free(aux);
	}
}

void destroi(Lista* l){
	if(l->ini != NULL){
        No *aux = l->ini;
        No *aux2;

        if(aux->prox == NULL){
            free(aux);
        }

        while(aux->prox != NULL){
            aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
        l->ini = NULL;
    }
}

void remover(Iterador* it, T* item){
	No* aux;
	aux = it->p;
	*item = aux->item;

	if(it->p->prox != NULL && it->p->ant != NULL){
		it->p->ant->prox = it->p->prox;
		it->p->prox->ant = it->p->ant;
		free(aux);
	}

	if(it->p->prox == NULL && it->p->ant == NULL){
		it->l = NULL;
		free(aux);
	}

	else if(it->p->prox == NULL){
		it->p->ant->prox = NULL;
		free(aux);
	}

	else if(it->p->ant == NULL){
		it->l->ini = it->p->prox;
		it->p->prox->ant = NULL;
		free(aux);
	}
}

void removeAntes(Iterador* it, T* item){
	if(it->p->ant != NULL){
		No* aux = it->p->ant;
		*item = it->p->ant->item;
		it->p->ant = it->p->ant->ant;
		it->p->ant->prox = it->p;
		free(aux);
	}
}

void removeFim(Lista* l, T* item){
	No* aux = l->ini;
	while(aux->prox != NULL)
		aux = aux->prox;

	if(aux->ant == NULL){
		l->ini = NULL;
		free(aux);
	}
	else{
		aux->ant->prox = NULL;
		free(aux);
	}
}

int vazia(Lista* l){
	return (l->ini == NULL);
}

int igual(Lista* l1, Lista* l2, int (*cmp_igual)(T, T)){
	Iterador it1 = inicio(l1);
	Iterador it2 = inicio(l2);
	T e1, e2;

	while(!acabou(&it1) && !acabou(&it2)){
		elemento(&it1, &e1);
		elemento(&it2, &e2);
		//A funcao cmp_igual vem da main como ponteiro
		if(!cmp_igual(e1,e2))
			return 0;

		if(e1 != e2)
			return 0;

		proximo(&it1);
		proximo(&it2);
	}
	if(acabou(&it1) && acabou(&it2))
		return 1;
	return 0;
}

No* meioLista(Lista* l){
	No *inic = l->ini;
	No *final = l->ini;

	if(l->ini == NULL)
		return 0;

	while(final->prox != NULL){
		final = final->prox;
	}

	while(inic != final){
		inic = inic->prox;
		if(inic == final){
			return inic;
		}
		final = final->ant;
	}
	return inic;
}

No* inverteLista(No *p){
	if(p == NULL)
		return p;

	else{
		inverteLista(p->prox)->prox = p;
		p->prox = NULL;
	}
}
