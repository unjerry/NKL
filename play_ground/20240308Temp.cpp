#include "20240308matTestTemp.h"
#include <iostream>
int main()
{
    mat<long double> a(2, 3), b(3, 3);
    b = 1;
    a = 1;
    mat<long double> A = {
        {12, 3, 4.5},
        {11, 3, 5},
        {1, 3, 11.3},
    };
    mat<long double> B = {{2},
                          {2},
                          {2}};
    mat<size_t> L = {{0},
                     {1},
                     {2}};
    std::cout << A << B << L << std::endl;
    std::cout << a << std::endl
              << b << std::endl;
    std::cout << a * b << std::endl;
    // std::cout << sizeof(a);
    gauss_elimination_with_partial_pivot<long double>(A, B, L);
    std::cout << A << B << L << std::endl;
    return 0;
}
