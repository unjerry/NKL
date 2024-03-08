#ifndef MAT_TEST_H
#define MAT_TEST_H
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <initializer_list>
class mat
{
public:
    size_t r, c;
    long double *data;
    mat(const size_t &r = 0, const size_t &c = 0);
    mat(std::initializer_list<std::initializer_list<long double>> A);
    ~mat();
    void operator=(const size_t &y);
};

mat::mat(const size_t &r, const size_t &c) : r{r}, c{c}
{
    printf("constructor0 %llu %llu\n", this, this->data);
    this->data = (long double *)malloc(sizeof(long double) * r * c);
    printf("constructor0 end %llu %llu\n\n", this, this->data);
}

mat::mat(std::initializer_list<std::initializer_list<long double>> A) : r{A.size()}, c{0}
{
    printf("constructor1 %llu %llu\n", this, this->data);
    for (auto &x : A)
    {
        if (x.size() > c)
        {
            c = x.size();
        }
    }
    const std::initializer_list<long double> *x = A.begin();
    this->data = (long double *)malloc(sizeof(long double) * r * c);
    long double(*D)[this->c] = (long double(*)[this->c])this->data;
    for (size_t i = 0; i < r; i++, x++)
    {
        std::copy(x->begin(), x->end(), D[i]);
    }
    printf("constructor1 end %llu %llu\n\n", this, this->data);
}

mat::~mat()
{
    printf("Destructors %llu %llu\n", this, this->data);
}

void mat::operator=(const size_t &y)
{
    printf("operator=0 %llu %llu\n", this, this->data);
    long double(*A)[this->c] = (long double(*)[this->c])this->data;
    switch (y)
    {
    case 1:
        printf("op=1\n");
        for (size_t i = 0; i < this->r; i++)
        {
            for (size_t j = 0; j < this->c; j++)
            {
                if (i == j)
                {
                    A[i][j] = 1;
                }
                else
                {
                    A[i][j] = 0;
                }
            }
        }
        break;

    default:
        printf("op=0\n");
        for (size_t i = 0; i < this->r; i++)
        {
            for (size_t j = 0; j < this->c; j++)
            {
                A[i][j] = 0;
            }
        }
        break;
    }
    printf("operator=0 end\n\n");
}

std::ostream &operator<<(std::ostream &fo, const mat &a)
{
    printf("operator<< %llu %llu\n", &a, a.data);
    long double(*A)[a.c] = (long double(*)[a.c])a.data;
    fo << "[" << a.r << " " << a.c;
    for (size_t i = 0; i < a.r; i++)
    {
        fo << std::endl;
        for (size_t j = 0; j < a.c; j++)
        {
            fo << A[i][j] << " ";
        }
    }
    fo << "]\n";
    printf("operator<< end\n\n");
    return fo;
}

mat operator*(const mat &a, const mat &b)
{
    printf("operator* (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data);
    mat c(a.r, b.c);
    c = 0;
    long double(*A)[a.c] = (long double(*)[a.c])a.data;
    long double(*B)[b.c] = (long double(*)[b.c])b.data;
    long double(*C)[c.c] = (long double(*)[c.c])c.data;
    for (size_t i = 0; i < a.r; i++)
    {
        for (size_t j = 0; j < b.c; j++)
        {
            for (size_t k = 0; k < a.c; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    printf("operator* end\n\n");
    return c;
}

void gauss_elimination_with_partial_pivot(mat &a, mat &b, mat &l)
{
    printf("gauss_elimination_with_partial_pivot (%llu %llu) (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data, &l, l.data);
    const size_t ac = a.c;
    const size_t bc = b.c;
    const size_t lc = l.c;
    long double(*A)[ac] = (long double(*)[ac])a.data;
    long double(*B)[bc] = (long double(*)[bc])b.data;
    size_t(*L)[lc] = (size_t(*)[lc])l.data;
    for (size_t c = 0; c < a.c; c++)
    {
        size_t temp = c;
        // for (size_t r = c; r < a.r; r++)
        // {
        //     if (A[L[r][0]][c] > A[L[temp][0]][c])
        //     {
        //         temp = r;
        //     }
        // }
        // if (temp != c)
        // {
        //     L[temp][0] ^= L[c][0];
        //     L[c][0] ^= L[temp][0];
        //     L[temp][0] ^= L[c][0];
        // }
        // for (size_t r = c + 1; r < a.r; r++)
        // {
        //     A[L[r][0]][c] /= A[L[c][0]][c];
        //     for (size_t c2 = c + 1; c2 < a.c; c2++)
        //     {
        //         A[L[r][0]][c2] -= A[L[r][0]][c] * A[L[c][0]][c2];
        //     }
        //     B[L[r][0]][0] -= A[L[r][0]][c] * B[L[c][0]][0];
        //     A[L[r][0]][c] = 0;
        // }
    }
    printf("gauss_elimination_with_partial_pivot end\n\n");
    return;
}

#endif
