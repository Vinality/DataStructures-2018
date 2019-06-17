#ifndef CORRETOR_H_
#define CORRETOR_H_

#include <iostream>
#include "dicionario.h"
#include "avltree.h"
#include "palavra.h"
#include "texto.h"
#include <list>

using namespace std;

class Corretor{
    private:
        Dicionario dic;
        Texto text;
        list<Palavra> erros;
        list<Palavra> :: iterator it;

    public:
        //Integracao com Texto
        void carregarTexto(const string &);
        void salvarTexto(const string &);
        void verificarTexto();
        void corrigirPalavra(wstring, Palavra);
        void mostrarContexto(Palavra);

        //Integracao com Palavra
        void mostrarOcorrencias(Palavra a);

        //Integracao com Dicionario
        void adicionarEx(Palavra);
        void mostrarSemelhantes();
        void corrigirSemelhante(Palavra, int);
        bool semelhantesVazia();
        void buscaSemelhantes(Palavra a);
        void importarDicionario();
        void exportarDicionario();

        //Interface da lista de erros
        Palavra erroAtual();
        bool errosFim();
        void errosProx();
        bool getErros();
        void exibeErros();
};

#endif
