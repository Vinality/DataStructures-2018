//Vinicius Brandao Crepschi   RA: 743601

#include <iostream>
#include <string.h>
#include "avltree.h"
#include <stack>
#include <deque>
#include "palavra.h"
using namespace std;

//****************
//*METODOS PUBLIC*
//****************

bool AvlTree::vazia(){
    return (raiz == NULL)? true : false;
}

void AvlTree::inserir(Palavra& plv){
    raiz = inserir(raiz, plv);
}

int AvlTree::busca(Palavra& plv){
    return busca(raiz, plv);
}

int AvlTree::busca(Palavra& plv, deque<Palavra>& semelhantes){
    return busca(raiz, plv, semelhantes);
}

stack<Palavra> AvlTree::inOrderPublic(){
    return inOrder();
}

//*****************
//*METODOS PRIVATE*
//*****************

//Retorna maximo entre dois int
int AvlTree::max(int a, int b){
    return (a>b)? a : b;
}

//Retorna atributo altura
int AvlTree::getAltura(no* raiz){
    if(raiz == NULL)
        return 0;

    return raiz->altura;
}

//Rotaciona para direita
no *AvlTree::rotacionaDireita(no* A){
    no *B = A->esq;
    A->esq = B->dir;
    B->dir = A;

    //Atualizando alturas
    A->altura = max(getAltura(A->esq), getAltura(A->dir))+1;
    B->altura = max(getAltura(B->esq), getAltura(A))+1;

    return B;
}

//Rotaciona para a esquerda
no* AvlTree::rotacionaEsquerda(no* A){
    no *B = A->dir;
    A->dir = B->esq;
    B->esq = A;

    //Atualizando alturas
    A->altura = max(getAltura(A->esq), getAltura(A->dir))+1;
    B->altura = max(getAltura(A->dir), getAltura(A))+1;

    return B;
}

//Rotaciona a sub arvore a esquerda e depois rotaciona para a direita
no* AvlTree::rotacionaED(no* A){
    A->esq = rotacionaEsquerda(A->esq);
    return rotacionaDireita(A);
}

//Rotaciona a sub arvore a direita e depois rotaciona para a esquerda
no* AvlTree::rotacionaDE(no* A){
    A->dir = rotacionaDireita(A->dir);
    return rotacionaEsquerda(A);
}

//Calcula balanceamento de cada no: h_esq - h_dir
int AvlTree::getBal(no* raiz){
    if(raiz == NULL)
        return 0;

    return(getAltura(raiz->esq) - getAltura(raiz->dir));
}

//Inserir privado
no *AvlTree::inserir(no* raiz, Palavra &a){
    if(raiz == NULL){
        raiz = new no;
        raiz->palavra = a;
        raiz->altura = 0;
        raiz->esq = NULL;
        raiz->dir = NULL;
    }

    //Chamada recursiva pra esquerda se for menor
    else if(a.compara(raiz->palavra) < 0){
        raiz->esq = inserir(raiz->esq, a);
    }

    //Chamada recursiva pra direita se for maior
    else if(a.compara(raiz->palavra) > 0){
        raiz->dir = inserir(raiz->dir, a);
    }

    //fator de balanceamento
    int bal = getBal(raiz);

    //Se h_esq - h_dir == 2: Desbalanceamento na esquerda
    if(bal == 2){
        //Caso EE
        if(a.compara(raiz->esq->palavra) < 0)
            raiz = rotacionaDireita(raiz);
        //Caso ED
        else
            raiz = rotacionaED(raiz);
    }

    //Se h_esq - h_dir == -2: Desbalanceamento na direita
    else if(bal == -2){
        //Caso DD
        if(a.compara(raiz->dir->palavra) > 0)
            raiz = rotacionaEsquerda(raiz);
        //Caso DE
        else
            raiz = rotacionaDE(raiz);
    }

    //Atualiza altura antes de retornar
    raiz->altura = 1 + max(getAltura(raiz->esq), getAltura(raiz->dir));
    return raiz;
}

//Busca privado
int AvlTree::busca(no *raiz, Palavra& a){
    if(a == raiz->palavra){
        return 0;
    }
    no *temp = raiz;
    while(temp){
        if(a.compara(temp->palavra) < 0)
            temp = temp->esq;
        else if(a.compara(temp->palavra) > 0)
            temp = temp->dir;
        else //quando dado == t->item
            return 1;
    }
    return 0;
}

//Busca privado sobrecarregado para a busca de palavras semelhantes
int AvlTree::busca(no* raiz, Palavra& p, deque<Palavra>& semelhantes){
    if(!raiz){
        return 0;
    }else{
        if(p.getWord().size() < 2){
            return 0;
        }
        wstring first_second = p.getWord();
        first_second = first_second.substr(0,2);
        no* temp = raiz;

        if(p.getWord().size() < 2){
            return 0;
        }

        while(temp){
            if(first_second == temp->palavra.getWord().substr(0,2)){
                semelhantes.push_front(temp->palavra);
            }if(p.compara(temp->palavra) < 0){
                temp = temp->esq;
            }else if(p.compara(temp->palavra) > 0){
                temp = temp->dir;
            }
        }
    }
    return 1;
}

//Desaloca memoria da arvore percorrendo em post-order
void AvlTree::destruirAvl(no *raiz){
    if(raiz == NULL)
        return;

    destruirAvl(raiz->esq);
    destruirAvl(raiz->dir);

    delete(raiz);
    raiz = NULL;
}

stack<Palavra> AvlTree::inOrder(){
    no* temp = raiz;
    stack<Palavra> s;
    stack<no*> percorre;

    percorre.push(temp);
    while(!percorre.empty()){
        temp = percorre.top();
        s.push(temp->palavra);
        percorre.pop();

        if(temp->esq){
            percorre.push(temp->esq);
        }if(temp->dir){
            percorre.push(temp->dir);
        }
    }
    return s;
}
