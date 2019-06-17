#ifndef COMPLEX_H_
#define COMPLEX_H_

typedef struct _complex *Complex;

// Create a new `Complex` number from two `double`s.
Complex newComplex (double re, double im);

// Release all resources associated with a `Complex` number.
void destroyComplex (Complex c);

// Retrieve the real part of the `Complex` number.
double complexRe (Complex c);

// Retrieve the imaginary part of the `Complex` number.
double complexIm (Complex c);

// Add two `Complex` numbers together.
Complex complexAdd (Complex w, Complex z);

// Multiply two `Complex` numbers together.
Complex complexMultiply (Complex w, Complex z);

// Take the magnitude (or modulus, or absolute) of a `Complex` number.
double complexMod (Complex w);

// Take the argument (or angle) of a `Complex` number.
double complexArg (Complex w);

#endif // !defined(COMPLEX_H_)
