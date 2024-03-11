#ifndef DENSE_H
#define DENSE_H
#include "layer.h"
#include "stdio.h"
#include "math_template/matrix_over_field.h"
class dense : public layer<matrix_over_field<long double>, matrix_over_field<long double>, long double>
{
public:
    matrix_over_field<long double> W;
    matrix_over_field<long double> B;
    dense(const size_t &input_size, const size_t &output_size);
    ~dense();
    matrix_over_field<long double> forward(const matrix_over_field<long double> &input);
    matrix_over_field<long double> backward(const matrix_over_field<long double> &x, const long double &lr);
};

dense::dense(const size_t &input_size, const size_t &output_size)
{
    // printf("dense constructor0 (%llu %llu)\n", this, this->W);
    this->W = *(new matrix_over_field<long double>(output_size, input_size));
    this->B = *(new matrix_over_field<long double>(output_size, 1));
    this->W = 1;
    this->B = 0;
    // printf("dense constructor0 end (%llu %llu)\n\n", this, this->W);
}

dense::~dense()
{
    // printf("dense Destructors (%llu %llu)\n\n", this, this->W);
}

matrix_over_field<long double> dense::forward(const matrix_over_field<long double> &input)
{
    // printf("dense forward (%llu %llu)\n", this, this->W);
    this->input = input;
    // printf("dense forward end\n\n");
    return this->W * this->input + this->B;
}

matrix_over_field<long double> dense::backward(const matrix_over_field<long double> &x, const long double &lr)
{
    // printf("dense backward (%llu %llu)\n", this, this->W);
    matrix_over_field<long double> Wg;
    matrix_over_field<long double> Ilr(x.r, x.r);
    Ilr = lr;
    // std::cout << "-----------" << Ilr;
    Wg = x * this->input.T();
    // std::cout << "-----------" << Wg;
    // std::cout << "-----------" << x;
    this->W = this->W - Ilr * Wg;
    this->B = this->B - Ilr * x;
    // printf("dense backward end\n\n");
    return this->W.T() * x;
}

#endif
