#include <iostream>
#include "matrix_over_field.h"
#include "dense.h"
#include <fstream>

void show_dense(const dense &d)
{
    std::cout << "p=" << &d << std::endl
              << "W" << d.W << std::endl
              << "dW" << d.dW << std::endl
              << "B" << d.B << std::endl
              << "dB" << d.dB << std::endl;
}

int main(void)
{
    size_t L[] = {0, 1, 2, 3, 4};
    std::ifstream fi;
    matrix_over_field<double> X, Y, one(1, 1);
    one = 1;
    std::cout << one;
    fi.open("X.in", std::ios::in | std::ios::binary);
    fi >> X >> Y;
    fi.close();
    dense a(1, 1);
    show_dense(a);
    auto tmp = a.forward(X);
    double loss;
    for (size_t i = 0; i < 100000; i++)
    {
        a.zero_d();
        loss = 0;
        for (size_t &l : L)
        {
            auto out = a.forward(X.data[l] * one);
            a.backward(out - (Y.data[l] * one), 0.001);
            loss += sum(((Y.data[l] * one) - out) * ((Y.data[l] * one) - out).T());
        }
        a.step();
    }
    std::cout << "\nloss " << loss << std::endl;
    show_dense(a);

    return 0;
}
