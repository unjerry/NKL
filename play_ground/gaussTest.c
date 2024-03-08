
#include "gaussLib.h"

int main()
{
    size_t N = 3;
    long double A[3][4] =
        {
            {12, 3, 4.5, 2},
            {11, 3, 5, 2},
            {1, 3, 11.3, 2},
        };
    long double x[3] = {0};
    size_t lable[3] = {0, 1, 2};
    gaussElimination(3, 4, A, lable, x, gaussEliminationMainRow, gaussBackPropMainRow);
    return 0;
}
