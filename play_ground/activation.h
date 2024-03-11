#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "layer.h"
#include "math_template/matrix_over_field.h"
#include <stdio.h>
class activation : public layer<matrix_over_field<long double>, matrix_over_field<long double>, long double>
{
public:
    matrix_over_field<long double> (*active)(const matrix_over_field<long double> &);
    matrix_over_field<long double> (*derive)(const matrix_over_field<long double> &);
    activation(matrix_over_field<long double> (*)(const matrix_over_field<long double> &), matrix_over_field<long double> (*)(const matrix_over_field<long double> &));
    ~activation();
    matrix_over_field<long double> forward(const matrix_over_field<long double> &input);
    matrix_over_field<long double> backward(const matrix_over_field<long double> &x, const long double &lr);
};

activation::activation(matrix_over_field<long double> (*active)(const matrix_over_field<long double> &), matrix_over_field<long double> (*derive)(const matrix_over_field<long double> &)) : active{active}, derive{derive}
{
    // printf("activation constructor0 (%llu %llu)\n", this, this->active);
    // printf("activation constructor0 end (%llu %llu)\n\n", this, this->active);
}

activation::~activation()
{
    // printf("activation Destructors (%llu %llu)\n\n", this, this->active);
}

matrix_over_field<long double> activation::forward(const matrix_over_field<long double> &input)
{
    // printf("activation forward (%llu %llu)\n", this, this->active);
    this->input = input;
    // printf("activation forward end\n\n");
    return this->active(input);
}

matrix_over_field<long double> activation::backward(const matrix_over_field<long double> &x, const long double &lr)
{
    // printf("activation backward (%llu %llu)\n", this, this->active);
    // printf("activation backward end\n\n");
    return point_wise_multiplication<long double>(x, this->derive(this->input));
}
#endif
