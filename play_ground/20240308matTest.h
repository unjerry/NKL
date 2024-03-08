#ifndef MAT_TEST_H
#define MAT_TEST_H
#include <stdio.h>
#include <fstream>
#include <iostream>
class mat
{

public:
    size_t r, c;
    long double *data;
    mat(const size_t &r = 0, const size_t &c = 0);
    ~mat();
    void operator=(const size_t &y);
};

mat::mat(const size_t &r, const size_t &c)
{
    printf("construct %llu %llu\n", this, this->data);
    this->r = r;
    this->c = c;
    this->data = (long double *)malloc(sizeof(long double) * r * c);
}

mat::~mat()
{
    printf("destruct %llu %llu\n", this, this->data);
}

void mat::operator=(const size_t &y)
{
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
    return fo;
}

mat operator*(const mat &a, const mat &b)
{
    printf("operator* %llu %llu %llu %llu\n", &a, a.data, &b, b.data);
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
    return c;
}

#endif
