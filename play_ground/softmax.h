#ifndef SOFTMAX_H
#define SOFTMAX_H
#include "layer.h"
#include <stdio.h>
#include <math.h>
#include "math_template/matrix_over_field.h"
class softmax : public layer<matrix_over_field<long double>, matrix_over_field<long double>, long double>
{
public:
    softmax(/* args */);
    ~softmax();
    matrix_over_field<long double> forward(const matrix_over_field<long double> &input);
    matrix_over_field<long double> backward(const matrix_over_field<long double> &x, const long double &lr);
};

softmax::softmax(/* args */)
{
}

softmax::~softmax()
{
}

matrix_over_field<long double> softmax::forward(const matrix_over_field<long double> &input)
{
    matrix_over_field<long double> tmp(input.r, input.c);
    long double(*TMP)[tmp.c] = (long double(*)[tmp.c])tmp.data;
    long double(*INP)[input.c] = (long double(*)[input.c])input.data;
    long double SUM = 0;
    for (size_t i = 0; i < input.r; i++)
    {
        for (size_t j = 0; j < input.c; j++)
        {
            TMP[i][j] = exp(INP[i][j]);
            SUM += TMP[i][j];
        }
    }
    for (size_t i = 0; i < input.r; i++)
    {
        for (size_t j = 0; j < input.c; j++)
        {
            TMP[i][j] = TMP[i][j] / SUM;
        }
    }
    this->output = tmp;
    return this->output;
}

matrix_over_field<long double> softmax::backward(const matrix_over_field<long double> &x, const long double &lr)
{
    // printf("activation backward (%llu %llu)\n", this, this->active);
    // printf("activation backward end\n\n");
    matrix_over_field<long double> I(this->output.r, this->output.r);
    I = 1;
    // std::cout << this->output << std::endl;
    return (((long double)(-1) * (this->output * this->output.T())) + I) * x;
}

#endif
