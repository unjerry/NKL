
#include "math_template/matrix_over_field.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
int main()
{
    matrix_over_field<long double> L(3, 3), U(3, 3), C(3, 3);
    L = 0;
    U = 0;
    FILE *fi;
    fi = fopen("testfordoolittleb.in", "rb");
    fread(C.data, 144, 1, fi);
    fclose(fi);
    std::ofstream fo;
    fo.open("testfordoolittle.out", std::ios::out | std::ios::binary);
    fo << C << std::endl;
    long double(*c)[C.c] = (long double(*)[C.c])C.data;
    long double(*l)[L.c] = (long double(*)[L.c])L.data;
    long double(*u)[U.c] = (long double(*)[U.c])U.data;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = i; j < 3; j++)
        {
            u[i][j] = c[i][j];
        }
        l[i][i] = 1;
    }
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = i + 1; j < 3; j++)
        {
            l[j][i] = c[j][i];
        }
    }

    fo << L << std::endl
       << U << std::endl
       << L * U << std::endl;
    std::cout << L;
    fo.close();
    return 0;
}
