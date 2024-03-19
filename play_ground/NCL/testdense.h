#ifndef TESTDENSE_H
#define TESTDENSE_H
#include "testlayer.h"
#include "stdio.h"
#include "math_template/matrix_over_field.h"
class testdense : public testlayer
{
public:
    double W;
    double B;
    testdense(const size_t &input_size, const size_t &output_size);
    ~testdense();
    virtual double forward(const double &input);
    // double backward(const double &x, const long double &lr);
};

testdense::testdense(const size_t &input_size, const size_t &output_size)
{
    // printf("testdense constructor0 (%llu %llu)\n", this, this->W);
    this->W = *(new double);
    this->B = *(new double);
    this->W = 1;
    this->B = 0;
    // printf("testdense constructor0 end (%llu %llu)\n\n", this, this->W);
}

testdense::~testdense()
{
    // printf("testdense Destructors (%llu %llu)\n\n", this, this->W);
}

double testdense::forward(const double &input)
{
    // printf("testdense forward (%llu %llu)\n", this, this->W);
    this->input = input;
    // printf("testdense forward end\n\n");
    return this->W * this->input + this->B;
}

// double testdense::backward(const double &x, const long double &lr)
// {
//     // printf("testdense backward (%llu %llu)\n", this, this->W);
//     double Wg;
//     double Ilr(x.r, x.r);
//     Ilr = lr;
//     // std::cout << "-----------" << Ilr;
//     Wg = x * this->input.T();
//     // std::cout << "-----------" << Wg;
//     // std::cout << "-----------" << x;
//     this->W = this->W - Ilr * Wg;
//     this->B = this->B - Ilr * x;
//     // printf("testdense backward end\n\n");
//     return this->W.T() * x;
// }

#endif
