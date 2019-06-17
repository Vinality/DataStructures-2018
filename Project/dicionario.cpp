#include <iostream>
#include <stack>
#include <string>
#include "avltree.h"
#include "dicionario.h"
#include "palavra.h"
#include <fstream>

using namespace std;

//função que permite ao usuário efetuar a consulta de uma palavra no exportarDicionario
//retorna false para palavra não encontrada e true para palavra encontrada
bool Dicionario::consulta(Palavra& p){
    return tree.busca(p);
}

//função que permite ao usuário inserir uma nova palavra na árvore do Dicionario
//e consequentemente insere no arquivo.txt do Dicionario
void Dicionario::inserirPalavra(Palavra& p){
    mudou = true;
    tree.inserir(p);
}

//funçao que carrega Dicionario a partir de um arquivo .txt e o insere na árvore
void Dicionario::importarDicionario(){
    Palavra buffer;
    wstring temp;
    wifstream arquivo;

    arquivo.open("dic.txt");

    if(!arquivo.is_open()){
        throw "Falha ao ler dicionário";
    }

    while(!arquivo.eof()){
        arquivo >> temp;

        if(temp.size() == 0){
            throw "Dicionario vazio";
        }

        buffer.setWord(temp);
        tree.inserir(buffer);
      }
    arquivo.close();

    cout << "Dicionario importado com sucesso!" << endl;

    return;
}

//a versão abaixa exporta o dicionário como um todo,
//caso uma alteração no dicionário tenha sido efetuada
void Dicionario::exportarDicionario(){
    if(mudou == true){
        stack <Palavra>s;
        wstring temp;
        wofstream arquivo;
        arquivo.open("dic.txt");

        s = tree.inOrderPublic();

        if(arquivo){
            while(!s.empty()){
                temp = s.top().getWord();
                arquivo << temp << endl;
                s.pop();
            }
        }
        arquivo.close();
    }
}

//função que busca e retorna uma lista de palavras semelhantes aquela passada como parâmetro
void Dicionario::buscaSemelhantes(Palavra& p){
    if(tree.vazia()){
        return;
    }else{
        tree.busca(p, semelhantes);
    }
    return;
}

//função que reseta a lista de semelhantes para que possa ser usada
//para armazenar novas palavras semelhantes a uma outra palavra
void Dicionario::resetSemelhantes(){
    if(!semelhantes.empty()){
        semelhantes.clear();
    }
}

//função que retorna true para lista de semelhantes vazia e 0 para lista
//de semelhantes não vazia
bool Dicionario::semelhantesVazia(){
    if(semelhantes.empty()){
        return true;
    }else{
        return false;
    }
}

//função retorna a palavra para qual o iterador está apontando
Palavra& Dicionario::getPalavra(deque<Palavra> :: iterator& it){
    return *it;
}

//função retorna uma palavra do deque de acordo com o índice fornecido
Palavra& Dicionario::getPalavra(unsigned i){
    if(i < semelhantes.size() && i <= 10){
        return semelhantes[i];
    }
    else throw "Indice invalido, tchau!";
}

//imprime lista de palavras semelhantes
void Dicionario::printSemelhantes(){

    int tamanho = semelhantes.size();
    for(int i = 0;  i < 11 && i < tamanho; i++){
        Palavra temp = semelhantes[i];
        wstring aux = temp.getWord();
        wcout << i << "." << aux << endl;

    }
}
