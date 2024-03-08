#include "20240308matTest.h"
#include <iostream>
// -D__USE_MINGW_ANSI_STDIO
int main()
{
    mat a(2, 3), b(3, 3);
    mat A = {
        {1, 2, 3},
        {2, 3, 4},
        {3, 4, 5},
    };
    mat B = {{1},
             {3},
             {4}};
    std::cout << A << B << std::endl;
    b = 1;
    a = 1;
    std::cout << a << std::endl
              << b << std::endl;
    std::cout << a * b << std::endl;
    // std::cout << sizeof(a);
    return 0;
}
