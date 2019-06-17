#ifndef RATIONAL_H_
#define RATIONAL_H_

typedef struct {
	int num;
	int den;
} rational;

// Cria um numero racional e retorna
rational define(int numerator, int denominator);

// Retorna a+b
rational plus(rational a, rational b);

// Retorna a-b
rational minus(rational a, rational b);

// Retorna a*b
rational times(rational a, rational b);

// Retorna a/b
rational divides(rational a, rational b);

// Retorna 0, caso 'a' seja diferente de 'b'
int	equals(rational a, rational b);

// Preenche 'str' com o numero 'r' no fomato 'numerador/denominador'
void toString(rational r, char* str);

#endif
