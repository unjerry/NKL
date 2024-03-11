#include <stdio.h>
// -D__USE_MINGW_ANSI_STDIO
void printt(size_t rowNum, size_t colNum, long double A[rowNum][colNum])
{
    for (size_t i = 0; i < rowNum; i++)
    {
        for (size_t j = 0; j < colNum; j++)
        {
            printf("%Lf ", A[i][j]);
        }
        printf("\n");
    }
    return;
}
void printlabel(size_t rowNum, size_t colNum, long double A[rowNum][colNum], size_t lable[rowNum])
{
    for (size_t i = 0; i < rowNum; i++)
    {
        for (size_t j = 0; j < colNum; j++)
        {
            printf("%Lf ", A[lable[i]][j]);
        }
        printf("\n");
    }
    return;
}
void gaussEliminationPlain(size_t rowNum, size_t colNum, long double A[rowNum][colNum])
{
    for (size_t c = 0; c < rowNum; c++)
    {
        for (size_t r = c + 1; r < rowNum; r++)
        {
            A[r][c] /= A[c][c];
            for (size_t c2 = c + 1; c2 < colNum; c2++)
            {
                A[r][c2] -= A[r][c] * A[c][c2];
            }
            A[r][c] = 0;
        }
    }
    return;
}
void gaussBackProp(size_t rowNum, size_t colNum, long double A[rowNum][colNum], long double *x)
{
    for (size_t c = 1; c <= rowNum; c++)
    {
        x[rowNum - c] = A[rowNum - c][colNum - 1] / A[rowNum - c][rowNum - c];
        for (size_t r = 0; r < rowNum - c; r++)
        {
            A[r][colNum - 1] -= x[rowNum - c] * A[r][rowNum - c];
        }
    }
    return;
}
void test(long double (*a)[5])
{
    return;
}
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
void LUMainRow(size_t rowNum, size_t colNum, long double A[rowNum][colNum], size_t lable[rowNum])
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
            // A[lable[r]][c] = 0;
        }
    }
    return;
}

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
    // long double **p;
    // p = A;
    // printf("%llu\n", p[0]);
    // printf("%llu\n", A);
    // printf("%llu\n", p[2]);
    // for (size_t i = 0; i < 3; i++)
    // {
    //     printf("%llu\n", *A + i);
    // }
    // // for (size_t i = 0; i < 3; i++)
    // // {
    // //     printf("%Lf\n", A[i][1]);
    // // }
    // // long double t = 234.55;
    // // printf("%Lf\n", t);
    // printf("%Lf\n", (long double *)A + 1);
    // printf("%Lf\n", *A);
    // // printf("%Lf\n", (long double *)(**A) + 1);
    // test((long double *(*)[N])(&A));

    printlabel(3, 4, A, lable);
    printf("\n");
    // gaussEliminationMainRow(3, 4, A, lable);
    LUMainRow(3, 4, A, lable);
    printlabel(3, 4, A, lable);
    printf("\n");
    // gaussBackPropMainRow(3, 4, A, x, lable);
    // printlabel(3, 4, A, lable);
    // printf("\n");
    printlabel(3, 1, x, lable);
    printf("\n");
    for (size_t i = 0; i < 3; i++)
    {
        printf("%llu", lable[i]);
    }

    // printf("%d ", A[0]);
    // printf("%d ", A[1]);
    // printf("%d ", (size_t)(A[1]) - (size_t)(A[0]));
    return 0;
}
