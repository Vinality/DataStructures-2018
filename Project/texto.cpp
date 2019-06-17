#include "texto.h"
#include "palavra.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

/*-------------------------------------------------------------------------------------------------------------------------------
     carregarTexto: Funcao para carregar o arquivo .txt para a correcao. Retorna uma excecao caso o arquivo nao seja encontrado.
-------------------------------------------------------------------------------------------------------------------------------*/
bool Texto::carregarTexto() {

    //Carrega o arquivo a ser corrigido
    wstring plv;
    wifstream arq;
    arq.open(load.c_str(), ios::in);

    if(arq.is_open()) {
        while (arq >> plv) {
            Palavra p(plv);
            palavra.push_back(p);
        }
        arq.close();

        //Remove da lista noSymbol símbolos irrelevantes e deixa as letras minúsculas
        list<Palavra> :: iterator it;
        for (it = palavra.begin(); it != palavra.end(); it++) {
            wstring temp = it->getWord();
            for (unsigned int i = 0; i < temp.length(); i++) {
                    temp[i] = tolower(temp[i]);
            if ( !( (temp[i] >= 97 && temp[i] <= 122) || (temp[i] >= 192 && temp[i] <= 255))) {
                    temp.erase(remove(temp.begin(), temp.end(), temp[i]), temp.end());
              }
            }
            Palavra p(temp);
            palavraNoSymbol.push_back(p);
        }
    }
    else return false;

    return true;
}

/*-------------------------------------------------------------------------------------------------------------------------------
     salvarTexto: Funcao para salvar o arquivo .txt corrigido. Retorna uma excecao caso nao seja possivel salvar o arquivo
-------------------------------------------------------------------------------------------------------------------------------*/
bool Texto::salvarTexto() {

    //Salva todas palavras da lista em um arquivo
    if (!palavra.empty()) {
        wofstream arq;
        arq.open(save.c_str(), ios::out | ios::trunc);

        if(arq.is_open()) {
            list<Palavra> :: iterator it;
            for (it = palavra.begin(); it != palavra.end(); it++) {
                arq << *it << L" ";
            }
            arq.close();
            return true;
        }
        return false;
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------
     alterarPalavra: Funcao para trocar a palavrada errada pela correta na lista
-------------------------------------------------------------------------------------------------------------------------------*/
void Texto::alterarPalavra(const Palavra &errada, const Palavra &correta) {

    list<Palavra> :: iterator it;
    list<Palavra> :: iterator it2;
    bool symbol, symbolStart;
    wchar_t tempc, tempc2;
    it = palavraNoSymbol.begin();
    it2 = palavra.begin();

    for (; it != palavraNoSymbol.end(); it++, it2++) {
        wstring temp = it2->getWord();
        symbol = false;
        symbolStart = false;
        for (unsigned int i = 0; i < temp.length(); i++)
            temp[i] = tolower(temp[i]);

        if ( !( (temp[0] >= 97 && temp[0] <= 122) || (temp[0] >= 192 && temp[0] <= 255))) {
            tempc2 = temp[0];
            symbolStart = true;
        }

        int s = temp.length() - 1;
        if ( !( (temp[s] >= 97 && temp[s] <= 122) || (temp[s] >= 192 && temp[s] <= 255))) {
            tempc = temp[s];
            symbol = true;
        }

        if(*it == errada) {
            *it2 = correta;
            if (symbol)
                it2->setWord(it2->getWord() + tempc);
            if (symbolStart)
                it2->setWord(tempc2 + it2->getWord());
        }
    }

  }

/*-------------------------------------------------------------------------------------------------------------------------------
     getPrimeiro: retorna um iterador para o elemento de primeira posição na list
-------------------------------------------------------------------------------------------------------------------------------*/
list<Palavra> :: iterator Texto::getPrimeiro() {
    list<Palavra> :: iterator it = palavraNoSymbol.begin();
    return it;
}

/*-------------------------------------------------------------------------------------------------------------------------------
     ultimo: retorna true caso o iterador estiver na ultima posição da list e false caso contrario
-------------------------------------------------------------------------------------------------------------------------------*/
bool Texto::ultimo(const list<Palavra> :: iterator &it) const {
    if (it == palavraNoSymbol.end())
        return true;
    return false;
}

/*-------------------------------------------------------------------------------------------------------------------------------
     getPalavra: retorna palavra para qual o iterador da list aponta
-------------------------------------------------------------------------------------------------------------------------------*/
Palavra& Texto::getPalavra(const list<Palavra> :: iterator &it) const {
    return *it;
}

/*-------------------------------------------------------------------------------------------------------------------------------
     contexto: printa palavras proximas a palavra errada
-------------------------------------------------------------------------------------------------------------------------------*/
void Texto::contexto(list<Palavra> :: iterator &it) {

    list<Palavra> :: iterator temp;
    list<Palavra> :: iterator fim;
    fim = palavraNoSymbol.end();
    advance(fim, -1);
    for (temp = palavraNoSymbol.begin(); temp != fim; temp++) {
        if(*temp == *it)
            break;
    }

    if (temp == palavraNoSymbol.begin()) {
        wcout << *temp << " ";
        advance(temp, 1);
        wcout << *temp << endl;
    }
    else if (temp == fim) {
        advance(temp, -1);
        wcout << *temp << " ";
        advance(temp, 1);
        wcout << *temp << endl;

    }
    else {
        advance(temp, -1);
        wcout << *temp << " ";
        advance(temp, 1);
        wcout << *temp << " ";
        advance(temp, 1);
        wcout << *temp << endl;
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------
     Getters e setters
-------------------------------------------------------------------------------------------------------------------------------*/
void Texto::setLoad(const string &s) {
    load = s;
}

void Texto::setSave(const string &s) {
    save = s;
}
