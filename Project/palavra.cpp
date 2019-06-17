#include <iostream>
#include <string>

#include "palavra.h"
//****************
//*METODOS PUBLIC*
//****************

//Sobrecarga do operador ==
bool Palavra::operator== (const Palavra &op2){

	if(op2.word.compare(word) == 0)
		return true;
	return false;
}

//Invoca função compare da biblioteca string
int Palavra::compara(Palavra &plv2){
	return word.compare(plv2.getWord());
}

//Retorna o atributo string word
wstring Palavra::getWord() const {
	return word;
}

//Altera o valor do atributo string word
void Palavra::setWord(const wstring &p){
	word = p;
}

void Palavra::incrementarOcorrencias(){
	ocorrencias++;
}

int Palavra::getOcorrencias() const {
	return ocorrencias;
}

wostream& operator<<(wostream& os, const Palavra& a)
{
    os << a.word;
    return os;
}
