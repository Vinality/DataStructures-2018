#include "corretor.h"
#include <string>

using namespace std;

//Itera pela lista de palavras do texto comparando-as com o Dicionario
//e adicionando a lista de erros caso nao encontre
void Corretor::verificarTexto(){
    list<Palavra> :: iterator temp;
    list<Palavra> :: iterator encontra;
    temp = text.getPrimeiro();
    while(!text.ultimo(temp)){      //Itera pela lista de palavras do texto
        if(!dic.consulta(text.getPalavra(temp))){       //Palavra nao foi encontrada no dicionario
            encontra = find(erros.begin(), erros.end(), text.getPalavra(temp));         //Iterador procura na lista de erros o erro
            if(encontra == erros.end())         //Caso o erro nao conste na lista de erros
                erros.push_back(text.getPalavra(temp));         //Acrescenta a palavra na lista de erros
            it = find(erros.begin(), erros.end(), text.getPalavra(temp)); //Encontra o apontador do erro na lista de erros
            (*it).incrementarOcorrencias();     //Acrescenta o numero de ocorrencias do erro
        }
        advance(temp, 1);
    }
    it = erros.begin();
}

//Retorna true caso a lista de erros esteja vazia
bool Corretor::getErros(){
    return (!erros.empty());
}

//Percorre a lista de erros com iterador e a imprime
void Corretor::exibeErros(){
    list<Palavra> :: iterator temp;
    for(temp = erros.begin(); temp != erros.end(); temp++){
        wcout << *temp << endl;
    }
}

//Envia a palavra nova e a palavra a ser substituida
void Corretor::corrigirPalavra(wstring a, Palavra b){
    Palavra nova(a);
    text.alterarPalavra(b, nova);
}

//Retorna o ponteiro do iterador que corresponde a uma Palavra
Palavra Corretor::erroAtual(){
    return *it;
}

//Envia uma palavra pra ser adicionada ao dicionario
void Corretor::adicionarEx(Palavra a){
    dic.inserirPalavra(a);
}

//Retrona true caso chegue ao fim da lista de erros
bool Corretor::errosFim(){
    if(it == erros.end())
        return true;
    else
        return false;
}

//Avanca o iterador um elemento na lista de erros
void Corretor::errosProx(){
    advance(it, 1);
}

//Recebe o nome do arquivo a ser salvo e envia para o texto
void Corretor::salvarTexto(const string &n){
    text.setSave(n);
    if(!text.salvarTexto())
        throw "Nao foi possivel salvar o arquivo";
}

//Imprime na tela lista de palavras semelhantes
void Corretor::mostrarSemelhantes(){
    dic.printSemelhantes();
}

//Efetua a busca por palavras semelhantes a palavra inserida
void Corretor::buscaSemelhantes(Palavra a){
    dic.buscaSemelhantes(a);
}

//Importa o dicionario de um arquivo texto
void Corretor::importarDicionario(){
    dic.importarDicionario();
}

//Exporta o dicionario para um arquivo texto
void Corretor::exportarDicionario(){
    dic.exportarDicionario();
}

//Recebe a palavra errada e o numero da sugestao escolhida
void Corretor::corrigirSemelhante(Palavra errada, int i){
    text.alterarPalavra(errada, dic.getPalavra(i));
    dic.resetSemelhantes();
}

//Imprime a palavra anterior e posterior ao erro
void Corretor::mostrarContexto(Palavra a){
    text.contexto(it);
}

//Imprime o número de ocorrencias de determinada palavra
void Corretor::mostrarOcorrencias(Palavra a){
    cout << a.getOcorrencias() << endl;
}
//Recebe nome do arquivo e o carrega
void Corretor::carregarTexto(const string &s) {
    text.setLoad(s);
    if(!text.carregarTexto())
        throw "Texto invalido, tchau!";
}

//Checa se a lista de palavras semelhantes está vazia
bool Corretor::semelhantesVazia(){
    if(dic.semelhantesVazia())
        return true;
    else
        return false;
}
