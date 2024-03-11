#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H
#include "activation.h"
#include "math_template/matrix_over_field.h"
#include <math.h>
class Tanh : public activation
{
public:
    Tanh();
    ~Tanh();
};

Tanh::Tanh() : activation(active, derive)
{
    matrix_over_field<long double> act(const matrix_over_field<long double> &x);
    this->active = act;
    matrix_over_field<long double> der(const matrix_over_field<long double> &x);
    this->derive = der;
}
matrix_over_field<long double> act(const matrix_over_field<long double> &X)
{
    matrix_over_field<long double> C(X.r, X.c);
    long double(*x)[X.c] = (long double(*)[X.c])X.data;
    long double(*c)[C.c] = (long double(*)[C.c])C.data;
    for (size_t i = 0; i < C.r; i++)
    {
        for (size_t j = 0; j < C.c; j++)
        {
            c[i][j] = tanh(x[i][j]);
        }
    }

    return C;
}
matrix_over_field<long double> der(const matrix_over_field<long double> &X)
{
    matrix_over_field<long double> C(X.r, X.c);
    long double(*x)[X.c] = (long double(*)[X.c])X.data;
    long double(*c)[C.c] = (long double(*)[C.c])C.data;
    for (size_t i = 0; i < C.r; i++)
    {
        for (size_t j = 0; j < C.c; j++)
        {
            const long double t = tanh(x[i][j]);
            c[i][j] = 1 - t * t;
        }
    }

    return C;
}
Tanh::~Tanh()
{
}

#endif
