
#include "dense.h"
#include "math_template/matrix_over_field.h"
#include <fstream>
#include <string>

int main()
{
    matrix_over_field<long double> A =
        {
            {1},
            {2},
            {3},
        };
    dense a(3, 3);
    std::ofstream fo;
    fo.open("output.out", std::ios::out | std::ios::binary);
    fo << a.forward(A);
    a.W["1:3"];
    return 0;
}
