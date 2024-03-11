#include <fstream>
#include "math_template/matrix_over_field.h"
#include "dense.h"
#include "activation_functions.h"
#include "activation.h"
#include <list>

class modl : public layer<matrix_over_field<long double>, matrix_over_field<long double>, long double>
{
public:
    dense D1, D2;
    Tanh ACT1, ACT2;
    modl() : D1(2, 3), D2(3, 1) {}
    ~modl() {}
    matrix_over_field<long double> forward(const matrix_over_field<long double> &input)
    {
        this->input = input;
        this->output = input;
        this->output = D1.forward(this->output);
        this->output = ACT1.forward(this->output);
        this->output = D2.forward(this->output);
        this->output = ACT2.forward(this->output);
        return this->output;
    }
    matrix_over_field<long double> backward(const matrix_over_field<long double> &x, const long double &lr)
    {
        this->output = x;
        this->output = ACT2.backward(this->output, lr);
        this->output = D2.backward(this->output, lr);
        this->output = ACT1.backward(this->output, lr);
        this->output = D1.backward(this->output, lr);
        return this->output;
    }
};

int main()
{
    modl Md;
    matrix_over_field<long double> B[] = {*new matrix_over_field<long double>(
                                              {
                                                  {1},
                                                  {1},
                                              }),
                                          *new matrix_over_field<long double>(
                                              {
                                                  {1},
                                                  {0},
                                              }),
                                          *new matrix_over_field<long double>(
                                              {
                                                  {0},
                                                  {1},
                                              }),
                                          *new matrix_over_field<long double>(
                                              {
                                                  {0},
                                                  {0},
                                              })};
    matrix_over_field<long double> C[] = {*new matrix_over_field<long double>(
                                              {
                                                  {0},
                                              }),
                                          *new matrix_over_field<long double>(
                                              {
                                                  {1},
                                              }),
                                          *new matrix_over_field<long double>(
                                              {
                                                  {1},
                                              }),
                                          *new matrix_over_field<long double>(
                                              {
                                                  {0},
                                              })};
    size_t A[] = {0, 1, 2, 3};
    matrix_over_field<long double> opt, grad;
    for (size_t i = 0; i < 1e6; i++)
    {
        for (auto &a : A)
        {
            opt = Md.forward(B[a]);
            grad = (opt - C[a]);
            Md.backward(grad, 0.1);
        }
        if (i % 10000 == 0)
        {
            std::cout << "*";
        }
    }
    std::ofstream fo;
    fo.open("outputCp.out", std::ios::out | std::ios::binary);

    for (auto &a : A)
    {
        opt = Md.forward(B[a]);
        fo << B[a] << C[a] << opt << std::endl;
    }

    return 0;
}
