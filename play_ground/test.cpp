#include <stdio.h>
#include "field_matrix.h"
#include <iostream>
#include <fstream>
int main()
{
    field_matrix<long double> a, b;
    field_matrix<size_t> lable;
    std::ifstream fi;
    fi.open("mat", std::ios::binary | std::ios::in);
    fi >> a;
    std::cout << a;
    fi >> b;
    std::cout << b;
    fi >> lable;
    std::cout << lable;

    gaussEliminationMainRow<long double, size_t>(a, b, lable);
    std::cout << a;
    std::cout << b;
    std::cout << lable;

    field_matrix<long double> c(a.r, a.c), d(b.r, b.c);
    long double(*tem)[c.c];
    tem = (long double(*)[c.c])c.dat;
    long double(*tema)[a.c];
    tema = (long double(*)[a.c])a.dat;
    size_t(*L)[lable.c];
    L = (size_t(*)[lable.c])lable.dat;
    for (size_t i = 0; i < a.r; i++)
    {
        for (size_t j = 0; j < a.c; j++)
        {
            tem[i][j] = tema[L[i][0]][j];
        }
    }
    long double(*temd)[d.c];
    temd = (long double(*)[d.c])d.dat;
    long double(*temb)[b.c];
    temb = (long double(*)[b.c])b.dat;
    for (size_t i = 0; i < b.r; i++)
    {
        for (size_t j = 0; j < b.c; j++)
        {
            temd[i][j] = temb[L[i][0]][j];
        }
    }

    std::cout << c;
    std::cout << d;
    std::cout << lable;
    return 0;
}
