#ifndef MATRIX_OVER_FIELD_H
#define MATRIX_OVER_FIELD_H
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <initializer_list>
template <class F>
class matrix_over_field
{
public:
    size_t r, c;
    F *data;
    matrix_over_field(const size_t &r = 0, const size_t &c = 0);
    matrix_over_field(const std::initializer_list<std::initializer_list<F>> &A);
    matrix_over_field(const matrix_over_field &A);
    ~matrix_over_field();
    void operator=(const F &y);
    void operator=(const matrix_over_field &y);
    matrix_over_field operator[](const std::initializer_list<std::initializer_list<F>> &X);
    matrix_over_field T();
};

template <class F>
matrix_over_field<F>::matrix_over_field(const size_t &r, const size_t &c) : r{r}, c{c}
{
    // printf("matrix_over_field constructor0 (%llu %llu)\n", this, this->data);
    this->data = (F *)malloc(sizeof(F) * r * c);
    // printf("matrix_over_field constructor0 end (%llu %llu)\n\n", this, this->data);
}

template <class F>
matrix_over_field<F>::matrix_over_field(const std::initializer_list<std::initializer_list<F>> &A) : r{A.size()}, c{0}
{
    // printf("matrix_over_field constructor1 (%llu %llu)\n", this, this->data);
    for (auto &x : A)
    {
        if (x.size() > c)
        {
            c = x.size();
        }
    }
    const std::initializer_list<F> *x = A.begin();
    this->data = (F *)malloc(sizeof(F) * r * c);
    const size_t c = this->c;
    F(*D)
    [c] = (F(*)[c])this->data;
    for (size_t i = 0; i < r; i++, x++)
    {
        std::copy(x->begin(), x->end(), D[i]);
    }
    // printf("matrix_over_field constructor1 end (%llu %llu)\n\n", this, this->data);
}

template <class F>
matrix_over_field<F>::matrix_over_field(const matrix_over_field<F> &A)
{
    // printf("matrix_over_field constructor2 (%llu %llu)\n", this, this->data);
    this->c = A.c;
    this->r = A.r;
    this->data = (F *)malloc(sizeof(F) * this->r * this->c);
    F(*a)
    [A.c] = (F(*)[A.c])A.data;
    F(*b)
    [A.c] = (F(*)[A.c])this->data;
    for (size_t i = 0; i < A.r; i++)
    {
        for (size_t j = 0; j < A.c; j++)
        {
            b[i][j] = a[i][j];
        }
    }

    // printf("matrix_over_field constructor2 end (%llu %llu)\n\n", this, this->data);
}

template <class F>
matrix_over_field<F>::~matrix_over_field()
{
    free(this->data);
    // printf("matrix_over_field Destructors (%llu %llu)\n\n", this, this->data);
}

template <class F>
void matrix_over_field<F>::operator=(const F &y)
{
    // printf("matrix_over_field operator=0 (%llu %llu)\n", this, this->data);
    const size_t c = this->c;
    F(*A)
    [c] = (F(*)[c])this->data;
    // printf("op=%llu\n", y);
    for (size_t i = 0; i < this->r; i++)
    {
        for (size_t j = 0; j < this->c; j++)
        {
            if (i == j)
            {
                A[i][j] = y;
            }
            else
            {
                A[i][j] = 0;
            }
        }
    }
    // printf("matrix_over_field operator=0 end\n\n");
}

template <class F>
void matrix_over_field<F>::operator=(const matrix_over_field<F> &y)
{
    // printf("matrix_over_field operator=1 (%llu %llu)\n", this, this->data);
    free(this->data);
    this->c = y.c;
    this->r = y.r;
    this->data = (F *)malloc(sizeof(F) * this->r * this->c);
    const size_t c = this->c;
    F(*A)
    [c] = (F(*)[c])this->data;
    F(*B)
    [c] = (F(*)[c])y.data;
    for (size_t i = 0; i < y.r; i++)
    {
        for (size_t j = 0; j < y.c; j++)
        {
            A[i][j] = B[i][j];
        }
    }
    // printf("matrix_over_field operator=1 end\n\n");
}

template <class F>
matrix_over_field<F> matrix_over_field<F>::operator[](const std::initializer_list<std::initializer_list<F>> &X)
{
    // printf("matrix_over_field operator[]0 (%llu %llu)\n", this, this->data);
    matrix_over_field<F> A(0, 0);
    // const size_t l = s.length();
    // const size_t r = this->r, c = this->c;
    // size_t t = 0;
    // for (size_t i = 0; i < l; i++)
    // {
    //     if (s[i] == ',')
    //     {
    //         break;
    //     }
    // }
    // const size_t rl = t;
    // const size_t cl = l - t - 1;
    // size_t rs, re, cs, ce;
    // size_t rt = 0, ct = 0;
    // for (size_t i = 0; i < t; i++)
    // {
    //     if (s[i] == ':')
    //     {
    //         break;
    //     }
    // }
    // for (size_t i = t + 1; i < l; i++)
    // {
    //     if (s[i] == ':')
    //     {
    //         break;
    //     }
    // }
    // std::cout << s << std::endl;
    // printf("matrix_over_field operator[]0 end\n\n");
    for (auto &x : X)
    {
        for (auto &j : x)
        {
            std::cout << j << ":";
        }
        std::cout << ",";
    }
    return A;
}

template <class F>
matrix_over_field<F> matrix_over_field<F>::T()
{
    // printf("matrix_over_field T (%llu %llu)\n", this, this->data);
    matrix_over_field<F> C(this->c, this->r);
    const size_t c = this->c, r = this->r;
    F(*A)
    [c] = (F(*)[c])this->data;
    F(*B)
    [r] = (F(*)[r])C.data;
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
        {
            B[j][i] = A[i][j];
        }
    }
    // printf("matrix_over_field T end\n\n");
    return C;
}

template <class F>
std::ostream &operator<<(std::ostream &fo, const matrix_over_field<F> &a)
{
    // printf("matrix_over_field operator<< (%llu %llu)\n", &a, a.data);
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
    // printf("matrix_over_field operator<< end\n\n");
    return fo;
}

template <class F>
std::istream &operator>>(std::istream &fi, matrix_over_field<F> &z)
{
    // printf("matrix_over_field operator>> (%llu %llu)\n", &z, z.data);
    free(z.data);
    char ch;
    while (ch != '[')
    {
        fi >> ch;
    }
    fi >> z.r >> z.c;
    z.data = (F *)malloc(sizeof(F) * z.r * z.c);
    F(*A)
    [z.c] = (F(*)[z.c])(z.data);
    for (size_t i = 0; i < z.r; i++)
    {
        for (size_t j = 0; j < z.c; j++)
        {
            fi >> A[i][j];
        }
    }
    // printf("matrix_over_field operator>> end\n\n");
    return fi;
}

template <class F>
matrix_over_field<F> operator*(const matrix_over_field<F> &a, const matrix_over_field<F> &b)
{
    // printf("matrix_over_field operator*0 (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data);
    matrix_over_field<F> c(a.r, b.c);
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
    // printf("matrix_over_field operator*0 end\n\n");
    return c;
}

template <class F>
matrix_over_field<F> operator*(const F &a, const matrix_over_field<F> &b)
{
    // printf("matrix_over_field operator*1 (%llu %llu)\n", &b, b.data);
    matrix_over_field<F> c(b.r, b.c);
    F(*B)
    [b.c] = (F(*)[b.c])b.data;
    F(*C)
    [c.c] = (F(*)[c.c])c.data;
    for (size_t i = 0; i < b.r; i++)
    {
        for (size_t j = 0; j < b.c; j++)
        {
            C[i][j] = a * B[i][j];
        }
    }
    // printf("matrix_over_field operator*1 end\n\n");
    return c;
}

template <class F>
matrix_over_field<F> operator+(const matrix_over_field<F> &a, const matrix_over_field<F> &b)
{
    // printf("matrix_over_field operator+ (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data);
    matrix_over_field<F> c(a.r, b.c);
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
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    // printf("matrix_over_field operator+ end\n\n");
    return c;
}

template <class F>
matrix_over_field<F> operator-(const matrix_over_field<F> &a, const matrix_over_field<F> &b)
{
    // printf("matrix_over_field operator- (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data);
    matrix_over_field<F> c(a.r, b.c);
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
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    // printf("matrix_over_field operator- end\n\n");
    return c;
}

template <class F>
void gauss_elimination_with_partial_pivot(matrix_over_field<F> &a, matrix_over_field<F> &b, matrix_over_field<size_t> &l)
{
    // printf("matrix_over_field gauss_elimination_with_partial_pivot (%llu %llu) (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data, &l, l.data);
    const size_t ac = a.c;
    const size_t bc = b.c;
    const size_t lc = l.c;
    F(*A)
    [ac] = (F(*)[ac])a.data;
    F(*B)
    [bc] = (F(*)[bc])b.data;
    size_t(*L)[lc] = (size_t(*)[lc])l.data;
    for (size_t c = 0; c < ac; c++)
    {
        size_t temp = c;
        for (size_t r = c; r < a.r; r++)
        {
            if (A[L[r][0]][c] > A[L[temp][0]][c])
            {
                temp = r;
            }
        }
        if (temp != c)
        {
            L[temp][0] ^= L[c][0];
            L[c][0] ^= L[temp][0];
            L[temp][0] ^= L[c][0];
        }
        for (size_t r = c + 1; r < a.r; r++)
        {
            A[L[r][0]][c] /= A[L[c][0]][c];
            for (size_t c2 = c + 1; c2 < a.c; c2++)
            {
                A[L[r][0]][c2] -= A[L[r][0]][c] * A[L[c][0]][c2];
            }
            B[L[r][0]][0] -= A[L[r][0]][c] * B[L[c][0]][0];
            A[L[r][0]][c] = 0;
        }
    }
    // printf("matrix_over_field gauss_elimination_with_partial_pivot end\n\n");
    return;
}

template <class F>
matrix_over_field<F> point_wise_multiplication(const matrix_over_field<F> &a, const matrix_over_field<F> &b)
{
    // printf("matrix_over_field point_wise_multiplication (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data);
    matrix_over_field<F> c(a.r, a.c);
    const size_t ac = a.c;
    const size_t bc = b.c;
    const size_t cc = c.c;
    F(*A)
    [ac] = (F(*)[ac])a.data;
    F(*B)
    [bc] = (F(*)[bc])b.data;
    F(*C)
    [cc] = (F(*)[cc])c.data;
    for (size_t i = 0; i < a.r; i++)
    {
        for (size_t j = 0; j < a.c; j++)
        {
            C[i][j] = A[i][j] * B[i][j];
        }
    }
    // printf("matrix_over_field point_wise_multiplication end\n\n");
    return c;
}

template <class F>
F sum(const matrix_over_field<F> &a)
{
    // printf("matrix_over_field point_wise_multiplication (%llu %llu) (%llu %llu)\n", &a, a.data, &b, b.data);
    F sum = 0;
    const size_t ac = a.c;
    F(*A)
    [ac] = (F(*)[ac])a.data;
    for (size_t i = 0; i < a.r; i++)
    {
        for (size_t j = 0; j < a.c; j++)
        {
            sum = sum + A[i][j];
        }
    }
    // printf("matrix_over_field point_wise_multiplication end\n\n");
    return sum;
}

#endif
