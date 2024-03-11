
#include "dense.h"
#include "math_template/matrix_over_field.h"
#include "activation.h"
#include <fstream>
#include <string>
#include <math.h>
#include "activation_functions.h"

long double sigmoid(const long double &x)
{
    return 1 / (1 + exp(-x));
}
long double sigmoid_prime(const long double &x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}
matrix_over_field<long double> sigmoid(const matrix_over_field<long double> &X)
{
    matrix_over_field<long double> C(X.r, X.c);
    long double(*x)[X.c] = (long double(*)[X.c])X.data;
    long double(*c)[C.c] = (long double(*)[C.c])C.data;
    for (size_t i = 0; i < C.r; i++)
    {
        for (size_t j = 0; j < C.c; j++)
        {
            c[i][j] = sigmoid(x[i][j]);
        }
    }

    return C;
}
matrix_over_field<long double> sigmoid_prime(const matrix_over_field<long double> &X)
{
    matrix_over_field<long double> C(X.r, X.c);
    long double(*x)[X.c] = (long double(*)[X.c])X.data;
    long double(*c)[C.c] = (long double(*)[C.c])C.data;
    for (size_t i = 0; i < C.r; i++)
    {
        for (size_t j = 0; j < C.c; j++)
        {
            c[i][j] = sigmoid_prime(x[i][j]);
        }
    }

    return C;
}

int main()
{
    matrix_over_field<long double> dy, ky, A = {
                                               {1},
                                               {2},
                                               {3},
                                           };
    matrix_over_field<long double> desi =
        {
            {1},
            {1},
        };
    dense a(3, 2);
    // activation bsc(sigmoid, sigmoid_prime);
    Tanh sdfd;
    std::ofstream fo;
    fo.open("output.out", std::ios::out | std::ios::binary);
    fo << a.W;
    fo << a.B;
    for (size_t i = 0; i < 1000; i++)
    {
        ky = a.forward(A);
        dy = ky - desi;
        a.backward(dy, 0.01);
    }

    fo << ky;
    fo << a.W;
    fo << a.B;
    a.W[{{1, 3}, {1, 3}}];
    std::cout << sigmoid(1) << sigmoid(2);
    std::cout << desi << sigmoid(desi);
    std::cout << std::endl;
    std::cout << sdfd.derive(desi);
    std::cout << (long double)2.0 * desi;
    return 0;
}
