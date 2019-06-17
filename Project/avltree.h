#ifndef AVLTREE_H_
#define AVLTREE_H_
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <deque>
#include "palavra.h"
using namespace std;

struct no{
    Palavra palavra;
    int altura;
    struct no* esq;
    struct no* dir;
};

class AvlTree{
    public:
        bool vazia();
        void inserir(Palavra&);
        int busca(Palavra&);
        int busca(Palavra& plv, deque<Palavra>& semelhante);
        stack<Palavra> inOrderPublic();

        AvlTree(){
            raiz = NULL;
        }
        ~AvlTree(){
            destruirAvl(raiz);
        }

    private:
        int busca(no*, Palavra&);
        int busca(no*, Palavra&, deque<Palavra>&);
        no *inserir(no*, Palavra&);
        int getBal(no*);
        void destruirAvl(no*);
        no *rotacionaED(no*);
        no *rotacionaDE(no*);
        no *rotacionaDireita(no*);
        no *rotacionaEsquerda(no*);
        int getAltura(no*);
        int max(int, int);
        no *raiz;
        stack<Palavra> inOrder();

};

#endif
