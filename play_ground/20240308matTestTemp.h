#ifndef MAT_TEST_H
#define MAT_TEST_H
#include <stdio.h>
#include <fstream>
#include <iostream>
template <class F>
class mat
{
public:
    size_t r, c;
    F *data;
    mat(const size_t &r = 0, const size_t &c = 0);
    ~mat();
    void operator=(const size_t &y);
};

template <class F>
mat<F>::mat(const size_t &r, const size_t &c)
{
    printf("construct %llu %llu type=%s\n", this, this->data, typeid(F).name());
    this->r = r;
    this->c = c;
    this->data = (F *)malloc(sizeof(F) * r * c);
}

template <class F>
mat<F>::~mat()
{
    printf("destruct %llu %llu\n", this, this->data);
}

template <class F>
void mat<F>::operator=(const size_t &y)
{
    F(*A)
    [this->c] = (F(*)[this->c])this->data;
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

template <class F>
std::ostream &operator<<(std::ostream &fo, const mat<F> &a)
{
    printf("operator<< %llu %llu\n", &a, a.data);
    F(*A)
    [a.c] = (F(*)[a.c])a.data;
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

template <class F>
mat<F> operator*(const mat<F> &a, const mat<F> &b)
{
    printf("operator* %llu %llu %llu %llu\n", &a, a.data, &b, b.data);
    mat<F> c(a.r, b.c);
    c = 0;
    F(*A)
    [a.c] = (F(*)[a.c])a.data;
    F(*B)
    [b.c] = (F(*)[b.c])b.data;
    F(*C)
    [c.c] = (F(*)[c.c])c.data;
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
