
#include "matrix_over_field.h"
#include <iostream>
// -D__USE_MINGW_ANSI_STDIO

int main()
{
    matrix_over_field<long double> A =
        {
            {1, 2, 3},
            {2, 2, 2},
            {1, 12, 4},
        };
    matrix_over_field<long double> B;
    std::cin >> B;
    matrix_over_field<size_t> L =
        {
            {0},
            {1},
            {2},
        };
    std::cout << A << std::endl
              << B << std::endl
              << L << std::endl
              << A * B << std::endl;
    gauss_elimination_with_partial_pivot(A, B, L);
    std::cout << A << std::endl
              << B << std::endl
              << L << std::endl
              << A * B << std::endl;
    return 0;
}
