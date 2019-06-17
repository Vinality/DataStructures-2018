#include <stdio.h>

#include "priority_queue.h"

int max_idade(T a,T b) {
	return a.idade < b.idade;
}

int min_idade(T a,T b) {
	return a.idade > b.idade;
}


int main() {

	priority_queue idade;

	inicializar(&idade, max_idade);

	T a1, a2, a3, a4, a5;
	a1.idade = 18;
	a2.idade = 22;
	a3.idade = 17;
	a4.idade = 30;
	a5.idade = 25;

	inserir(&idade, a1);
	imprimir(&idade);
	printf("--------\n");

	inserir(&idade, a2);
	imprimir(&idade);
	printf("--------\n");

	inserir(&idade, a3);
	imprimir(&idade);
	printf("--------\n");

	inserir(&idade, a4);
	imprimir(&idade);
	printf("--------\n");

	inserir(&idade, a5);
	imprimir(&idade);
	printf("--------\n");

	return 0;
}
