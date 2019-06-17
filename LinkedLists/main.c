#include <stdio.h>
#include <stdlib.h>

#include "lista.h"



int main() {

	Lista letras;

	inicializa(&letras);

	insereInicio(&letras, 'K');
	insereInicio(&letras, 'J');
	insereInicio(&letras, 'I');
	insereInicio(&letras, 'H');
	insereInicio(&letras, 'G');
	insereInicio(&letras, 'F');
	insereInicio(&letras, 'E');
	insereInicio(&letras, 'D');
	insereInicio(&letras, 'C');
	insereInicio(&letras, 'B');
	insereInicio(&letras, 'A');

	char c;

	for( Iterador it = inicio(&letras);
	 !acabou(&it); proximo(&it) ) {
		elemento(&it,&c);
		printf("%c\n", c);
	}
	printf("meio da lista: %c\n", (meioLista(&letras))->item);
	printf("lista invertida:\n");
	No* p = letras.ini;

	for( Iterador it = inicio(&letras);
	 !acabou(&it); proximo(&it) ) {
		elemento(&it,&c);
		printf("%c\n", c);
	}

	return 0;
}
