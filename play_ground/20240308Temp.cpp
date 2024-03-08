#include "20240308matTestTemp.h"
#include <iostream>
int main()
{
    mat<long double> a(2, 3), b(3, 3);
    b = 1;
    a = 1;
    std::cout << a << std::endl
              << b << std::endl;
    std::cout << a * b << std::endl;
    // std::cout << sizeof(a);
    return 0;
}
