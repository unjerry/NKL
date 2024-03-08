
#include "gaussLib.h"
// -D__USE_MINGW_ANSI_STDIO
void gaussEliminationMainRow(size_t rowNum, size_t colNum, long double A[rowNum][colNum], size_t lable[rowNum])
{
    for (size_t c = 0; c < rowNum; c++)
    {
        size_t temp = c;
        for (size_t r = c; r < rowNum; r++)
        {
            if (A[lable[r]][c] > A[lable[temp]][c])
            {
                temp = r;
            }
        }
        // printf("%llu %llu %llu %llu\n\n", temp, c, lable[temp], lable[c]);
        if (temp != c)
        {
            lable[temp] ^= lable[c];
            lable[c] ^= lable[temp];
            lable[temp] ^= lable[c];
        }
        for (size_t r = c + 1; r < rowNum; r++)
        {
            A[lable[r]][c] /= A[lable[c]][c];
            for (size_t c2 = c + 1; c2 < colNum; c2++)
            {
                A[lable[r]][c2] -= A[lable[r]][c] * A[lable[c]][c2];
            }
            A[lable[r]][c] = 0;
        }
    }
    return;
}
void gaussBackPropMainRow(size_t rowNum, size_t colNum, long double A[rowNum][colNum], long double *x, size_t lable[rowNum])
{
    for (size_t c = 1; c <= rowNum; c++)
    {
        x[lable[rowNum - c]] = A[lable[rowNum - c]][colNum - 1] / A[lable[rowNum - c]][rowNum - c];
        for (size_t r = 0; r < rowNum - c; r++)
        {
            A[lable[r]][colNum - 1] -= x[lable[rowNum - c]] * A[lable[r]][rowNum - c];
        }
    }
    return;
}

void gaussElimination(size_t rowNum, size_t colNum, long double A[rowNum][colNum], size_t lable[rowNum], long double x[rowNum], void (*elim)(size_t, size_t, long double (*)[colNum], size_t *), void (*back)(size_t, size_t, long double (*)[colNum], long double *, size_t *))
{
    printf("sdfsdf");
}
