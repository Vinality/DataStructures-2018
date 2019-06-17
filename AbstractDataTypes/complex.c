#include <stdlib.h>
#include <math.h>
#include "complex.h"

typedef struct _complex{
    double real;
    double img;
}*Complex;

Complex newComplex(double re, double im){
    Complex a = malloc(sizeof(Complex));
    a->real = re;
    a->img = im;

    return a;
}

void destroyComplex(Complex c){
    free(c);
}

double complexRe (Complex c){
    return(c->real);
}

double complexIm (Complex c){
    return(c->img);
}

Complex complexAdd (Complex w, Complex z){
    Complex result = malloc(sizeof(Complex));
    result->real = w->real + z->real;
    result->img = w->img + z->img;

    return result;
}

Complex complexMultiply (Complex w, Complex z){
    Complex result = malloc(sizeof(Complex));
    result->real = (w->real*z->real) - (w->img*z->img);
    result->img = (w->real*z->img) + (z->real*w->img);

    return result;
}

double complexMod (Complex w){
    double modulus;
    modulus = sqrt(pow(w->real, 2) + pow(w->img, 2));

    return modulus;
}

double complexArg (Complex w){
    double x = (180/3.14);
    double angle = atan(w->img/w->real)*x;

    return angle;
}
