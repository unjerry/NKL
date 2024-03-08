
#include <iostream>
#include <fstream>
#include "field_matrix.h"

int main()
{
    field_matrix<long double> a, b;

    std::fstream fi;
    fi.open("matt", std::ios::binary | std::ios::in);
    fi >> a >> b;
    std::cout << a << b;
    // field_matrix<long double> c(b);
    // std::cout << c;
    std::cout << (a * b);
    return 0;
}
