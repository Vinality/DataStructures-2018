#ifndef AVLTREE_H_
#define AVLTREE_H_
#include <iostream>
#include <string>
using namespace std;


class AvlTree{
    public:
        bool vazia();
        void inserir(string&);
        int busca(string&);

        AvlTree(){
            raiz = NULL;
        }
        ~AvlTree(){
            destruirAvl(raiz);
        }

    private:
        struct no{
            string palavra;
            int altura;
            struct no* esq;
            struct no* dir;
        };

        int busca(no*, string&);
        no *inserir(no*, string&);
        int getBal(no*);
        void destruirAvl(no*);
        no *rotacionaED(no*);
        no *rotacionaDE(no*);
        no *rotacionaDireita(no*);
        no *rotacionaEsquerda(no*);
        int getAltura(no*);
        int max(int, int);
        no *raiz;

};

#endif
