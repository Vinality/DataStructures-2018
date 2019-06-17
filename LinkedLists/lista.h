#ifndef LISTA_H
#define LISTA_H

typedef char T;

typedef struct no {
	T item;
	struct no* prox;
	struct no* ant;
} No;

typedef struct lista {
	No* ini;
	int qtd;
} Lista;

typedef struct iterador {
	No* p;
	Lista *l;
} Iterador;

void inicializa(Lista* l); //s
void insereInicio(Lista* l, T item); //s
void removeInicio(Lista* l, T* item); //s
Iterador inicio(Lista* l); //s
Iterador fim(Lista* l); //s
void elemento(Iterador* it, T* item); //s
void proximo(Iterador* it); //s
void anterior(Iterador* it); //s
int acabou(Iterador *it); //s
Iterador buscaPrimeiro(Lista* l, T item); //s
Iterador buscaProximo(Iterador* it, T item); //s
void insereDepois(Iterador* it, T item); //s
void insereAntes(Iterador* it, T item); //s
int quantidade(Lista* l); //s
void insereFim(Lista* l, T item); //s
Iterador buscaUltimo(Lista* l, T item); //s
Iterador buscaAnterior(Iterador* it, T item); //s
void removeDepois(Iterador* it, T* item); //s
void destroi(Lista* l); //s
void remover(Iterador* it, T* item); //s
void removeAntes(Iterador* it, T* item); //s
void removeFim(Lista* l, T* item); //s
int vazia(Lista* l); //s
int igual(Lista* l1, Lista* l2, int (*cmp_igual)(T, T)); //Funcao cmp vem da main, para comparar
No* meioLista(Lista* l);
No* inverteLista(No *p);

#endif
