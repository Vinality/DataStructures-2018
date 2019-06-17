#include <stdlib.h>
#include <stdio.h>
#include "rational.h"

rational define(int numerador, int denominador){
    rational a;
    a.num = numerador;
    a.den = denominador;

    return a;
}

rational plus(rational a, rational b){
    rational c;

    if(a.den != b.den){
        c.den = a.den * b.den;
        c.num = (a.num * b.den)+(b.num * a.den);
    }
    else{
        c.num = a.num + b.num;
        c.den = a.den;
    }

    return c;
}

rational minus(rational a, rational b){
    rational c;

    c.den = a.den * b.den;
    c.num = (a.num * b.den)-(b.num * a.den);

    if(c.num == 0)
        c.den = 0;

    return c;
}

rational times(rational a, rational b){
    rational c;
    c.num = a.num*b.num;
    c.den = a.den*b.den;

    return c;
}

rational divides(rational a, rational b){
    rational c;
    c.num = a.num*b.den;
    c.den = a.den*b.num;

    return c;
}

int	equals(rational a, rational b){
    if((a.num/b.num == a.den/b.den) || (b.num/a.num == b.den/a.den))
        return 1;
    else
        return 0;
}

void toString(rational r, char* str){
    sprintf(str, "%d/%d", r.num, r.den);
}
