#include <fstream>
#include "math_template/matrix_over_field.h"
#include "dense.h"
#include "activation_functions.h"
#include "activation.h"
#include "softmax.h"
#include <list>

class modl : public layer<matrix_over_field<long double>, matrix_over_field<long double>, long double>
{
public:
    dense D1, D2, D3;
    softmax ACT3;
    softmax ACT1, ACT2;
    modl() : D1(2, 5), D2(5, 5), D3(5, 2) {}
    ~modl() {}
    matrix_over_field<long double> forward(const matrix_over_field<long double> &input)
    {
        this->input = input;
        this->output = input;
        this->output = D1.forward(this->output);
        this->output = ACT1.forward(this->output);
        this->output = D2.forward(this->output);
        this->output = ACT2.forward(this->output);
        this->output = D3.forward(this->output);
        this->output = ACT3.forward(this->output);
        return this->output;
    }
    matrix_over_field<long double> backward(const matrix_over_field<long double> &x, const long double &lr)
    {
        this->output = x;
        this->output = ACT3.backward(this->output, lr);
        this->output = D3.backward(this->output, lr);
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
                                                  {1},
                                              }),
                                          *new matrix_over_field<long double>(
                                              {
                                                  {1},
                                                  {0},
                                              })};
    size_t A[] = {0, 2, 1, 3};
    size_t N;
    std::cin >> N;
    std::ofstream fo;
    fo.open("outputCp.out", std::ios::out | std::ios::binary);
    // std::cout << N;
    matrix_over_field<long double> opt, grad;
    for (size_t i = 0; i < 100; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    long double lr = 0.0001, loss, preloss;
    std::cin >> lr;
    for (size_t i = 0; i < N; i++)
    {
        loss = 0;
        for (auto &a : A)
        {
            opt = Md.forward(B[a]);
            grad = (long double)(2 / (C[a].r * C[a].c)) * (opt - C[a]);
            loss += sum(point_wise_multiplication(grad, grad));
            Md.backward(grad, preloss * lr);
        }
        preloss = loss;
        if (i % 10000 == 0)
        {
            std::cout << (long double)i / N << " " << loss << std::endl;
            for (auto &a : A)
            {
                opt = Md.forward(B[a]);
                fo << B[a] << C[a] << opt << std::endl;
            }
            fo << "//////////////////////////////////////////\n";
        }
    }

    for (auto &a : A)
    {
        opt = Md.forward(B[a]);
        fo << B[a] << C[a] << opt << std::endl;
    }

    return 0;
}
