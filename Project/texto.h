#ifndef TEXTO_H_
#define TEXTO_H_

#include <iostream>
#include <string>
#include <list>

#include "palavra.h"

using namespace std;

class Texto {

private:
	string load, save;
	list<Palavra> palavra;
	list<Palavra> palavraNoSymbol;
public:
	Texto(string s1 = "text.txt", string s2 = "save.txt") : load(s1), save(s2) {};
	bool carregarTexto();
	void alterarPalavra(const Palavra&, const Palavra&);
	bool salvarTexto();
	bool ultimo(const list<Palavra> :: iterator&) const;
	list<Palavra> :: iterator getPrimeiro();
	Palavra& getPalavra(const list<Palavra> :: iterator&) const;
	void setLoad(const string&);
	void setSave(const string&);
	void contexto(list<Palavra> :: iterator&);
};

#endif
