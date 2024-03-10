#include "20240308matTestTemp.h"
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream fo;
    fo.open("quaternion_table.out", std::ios::out | std::ios::binary);
    mat<long double> E1, E2, E3, I;
    I = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    E1 = {
        {1, 0, 0, 0},
        {0, -1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, -1},
    };
    E2 = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0},
    };
    E3 = {
        {0, 0, 0, 1},
        {0, 0, -1, 0},
        {0, -1, 0, 0},
        {1, 0, 0, 0},
    };
    std::cout << "IE123---------\n"
              << "I\n"
              << I << std::endl
              << "E1\n"
              << E1 << std::endl
              << "E2\n"
              << E2 << std::endl
              << "E3\n"
              << E3 << std::endl;
    fo << "I\n"
       << I << std::endl
       << "E1\n"
       << E1 << std::endl
       << "E2\n"
       << E2 << std::endl
       << "E3\n"
       << E3 << std::endl;
    std::cout << "IEE---------\n"
              << "E1E2\n"
              << E1 * E2 << std::endl
              << "E2E3\n"
              << E2 * E3 << std::endl
              << "E3E1\n"
              << E3 * E1 << std::endl;
    fo << "----test for E*E----\n"
       << "E1E1\n"
       << E1 * E1 << std::endl
       << "E3E3\n"
       << E3 * E3 << std::endl
       << "E2E2\n"
       << E2 * E2 << std::endl
       << "E1E2\n"
       << E1 * E2 << std::endl
       << "E2E1\n"
       << E2 * E1 << std::endl
       << "E3E1\n"
       << E3 * E1 << std::endl
       << "E1E3\n"
       << E1 * E3 << std::endl
       << "E2E3\n"
       << E2 * E3 << std::endl
       << "E3E2\n"
       << E3 * E2 << std::endl;
    fo << "----test for E*E*E----\n"
       << "E1*E2*E3\n"
       << E1 * E2 * E3 << std::endl;
    std::cout << "IEEE---------\n"
              << "E1E2\n"
              << E1 * E2 * E1 * E2 << std::endl
              << "E2E3\n"
              << E2 * E3 * E2 * E3 << std::endl
              << "E3E1\n"
              << E3 * E1 * E3 * E1 << std::endl;
    return 0;
}
