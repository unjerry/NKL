#ifndef FIELD_MATRIX_H
#define FIELD_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#define FIELD_MATRIX_MAX(a, b) ((a > b) ? (a) : (b))
#define FIELD_MATRIX_MIN(a, b) ((a < b) ? (a) : (b))

template <class F>
class field_matrix
{
public:
    std::string io_format = "%.3Lf ";
    size_t r, c;
    F *dat;
    field_matrix(const size_t &r = 0, const size_t &c = 0);
    field_matrix(const field_matrix<F> &y);
    // void print(int opt = 0);
    // void fprint(FILE *f, int opt = 0);
    // int scan(int opt = 0);
    // int fscan(FILE *f, int opt = 0);
    // field_matrix operator-();
    void operator=(const size_t &y);
    void operator=(const field_matrix<F> &y);
};
template <class F>
field_matrix<F>::field_matrix(const size_t &r, const size_t &c)
{
    this->r = r;
    this->c = c;
    this->dat = new F[r][c];
}
template <class F>
field_matrix<F>::field_matrix(const field_matrix<F> &y)
{
    this->c = y.c;
    this->r = y.r;
    const size_t *cc = new size_t(3);
    this->dat = new F[*cc][*cc];
    F(*A)
    [this->c];
    F(*B)
    [y.c];
    A = (F(*)[this->c])this->dat;
    B = (F(*)[y.c])y.dat;
    for (size_t i = 0; i < this->r; i++)
    {
        for (size_t j = 0; j < this->c; j++)
        {
            A[i][j] = B[i][j];
        }
    }
}
template <class F>
std::ostream &operator<<(std::ostream &fo, const field_matrix<F> &z)
{
    // std::string tmp, ops;
    // tmp.resize(z.dt.size());
    // ops.resize(z.dt.size() + 20);
    // if (z.dt.size() == 0)
    // {
    //     printf("zahlen_warning(print):length==0\n");
    // }
    // if (z.dt[z.dt.size() - 1] >= 5)
    // {
    //     zahlen I("1"), c = ~z, b;
    //     b = c + I;
    //     tmp.resize(b.dt.size());
    //     for (int i = 0; i < b.dt.size(); i++)
    //     {
    //         tmp[i] = b.dt[b.dt.size() - 1 - i] + '0';
    //     }
    //     sprintf((char *)ops.c_str(), "(zahlen)< -%s >", tmp.c_str());
    // }
    // else
    // {
    //     for (int i = 0; i < z.dt.size(); i++)
    //     {
    //         tmp[i] = z.dt[z.dt.size() - 1 - i] + '0';
    //     }
    //     sprintf((char *)ops.c_str(), "(zahlen)< +%s >", tmp.c_str());
    // }
    // fo << ops.c_str();
    F(*A)
    [z.c];
    A = (F(*)[z.c])(z.dat);
    fo << "[(" << z.r << "," << z.c << ")\n";
    for (size_t i = 0; i < z.r; i++)
    {
        for (size_t j = 0; j < z.c; j++)
        {
            fo << A[i][j] << " ";
        }
        fo << "\n";
    }
    fo << "]\n";
    return fo;
}
template <class F>
std::istream &operator>>(std::istream &fi, field_matrix<F> &z)
{
    // int len = 0;
    // char sw, ch = 0;
    // std::string tmp;
    // while (ch != '(')
    // {
    //     fi >> ch;
    // }
    // fi >> tmp;
    // // printf("%s\n", tmp.c_str());
    // fi >> sw;
    // // printf("%c\n", sw);
    // //  fscanf((FILE *)fi.cur, "(zahlen)< %c", &sw);
    // while (1)
    // {
    //     tmp.resize(len + 1);
    //     ch = fi.get();
    //     // rt = fscanf((FILE *)fi.cur, "%c", &ch);
    //     // printf("%c\n", ch);
    //     if (ch == ' ')
    //     {
    //         break;
    //     }
    //     tmp[len++] = ch;
    // }
    // // printf("%d\n", tmp.size());
    // //  printf("%c\n", sw);
    // zahlen c(tmp.c_str());
    // z = c;
    // if (z.dt.size() == 0)
    // {
    //     printf("zahlen_warning(scan):length==0\n");
    // }
    // if (sw == '-')
    // {
    //     zahlen I("1");
    //     z = ~z + I;
    // }
    // /*
    //  */
    free(z.dat);
    char ch;
    while (ch != '[')
    {
        fi >> ch;
    }
    fi >> ch >> z.r >> ch >> z.c >> ch;
    z.dat = new F[const z.r][const z.c];
    F(*A)
    [z.c];
    A = (F(*)[z.c])(z.dat);
    for (size_t i = 0; i < z.r; i++)
    {
        for (size_t j = 0; j < z.c; j++)
        {
            // printf("%llu %llu", i, j);
            fi >> A[i][j];
        }
    }
    return fi;
}
template <class F>
void field_matrix<F>::operator=(const size_t &y)
{
    if (this->c * this->r == 0)
    {
        printf("field_matrix_warning(operator=):r*c==0\n");
        return;
    }
    if (y == 1)
    {
        F(*A)
        [this->c];
        A = (F(*)[this->c])(this->dat);
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
    }
    else
    {
        F(*A)
        [this->c];
        A = (F(*)[this->c])(this->dat);
        for (size_t i = 0; i < this->r; i++)
        {
            for (size_t j = 0; j < this->c; j++)
            {

                A[i][j] = 0;
            }
        }
    }
}
template <class F>
void field_matrix<F>::operator=(const field_matrix<F> &y)
{
    free(this->dat);
    this->c = y.c;
    this->r = y.r;
    this->dat = malloc(y.c * y.r * sizeof(F));
    F(*A)
    [this->c];
    F(*B)
    [y.c];
    A = (F(*)[this->c])this->dat;
    B = (F(*)[y.c])y.dat;
    for (size_t i = 0; i < this->r; i++)
    {
        for (size_t j = 0; j < this->c; j++)
        {
            A[i][j] = B[i][j];
        }
    }
}
template <class F, class N>
void gaussEliminationMainRow(field_matrix<F> x, field_matrix<F> y, field_matrix<N> lable)
{
    F(*A)
    [x.c];
    A = (F(*)[x.c])x.dat;
    F(*b)
    [y.c];
    b = (F(*)[y.c])y.dat;
    N(*L)
    [lable.c];
    L = (N(*)[lable.c])lable.dat;
    for (size_t c = 0; c < x.c; c++)
    {
        size_t temp = c;
        for (size_t r = c; r < x.r; r++)
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
        for (size_t r = c + 1; r < x.r; r++)
        {
            A[L[r][0]][c] /= A[L[c][0]][c];
            for (size_t c2 = c + 1; c2 < x.c; c2++)
            {
                A[L[r][0]][c2] -= A[L[r][0]][c] * A[L[c][0]][c2];
            }
            b[L[r][0]][0] -= A[L[r][0]][c] * b[L[c][0]][0];
            A[L[r][0]][c] = 0;
        }
    }
    return;
}

// template <class F>
// void field_matrix<F>::print(int opt)
// {
//     printf("[%d,%d\n", r, c);
//     if (r * c != 0)
//     {
//         for (int i = 1; i <= this->r; i++)
//         {
//             for (int j = 1; j <= this->c; j++)
//             {
//                 this->dt[i][j].print(opt);
//                 printf(",");
//             }
//             printf("\n");
//         }
//     }
//     else
//     {
//         printf("NULLMATRIX\n");
//     }
//     printf("]\n");
// }
// template <class F>
// void field_matrix<F>::fprint(FILE *f, int opt)
// {
//     fprintf(f, "[%d,%d\n", r, c);
//     if (r * c != 0)
//     {
//         for (int i = 1; i <= this->r; i++)
//         {
//             for (int j = 1; j <= this->c; j++)
//             {
//                 this->dt[i][j].fprint(f, opt);
//                 fprintf(f, ",");
//             }
//             fprintf(f, "\n");
//         }
//     }
//     else
//     {
//         fprintf(f, "NULLMATRIX\n");
//     }
//     fprintf(f, "]\n");
// }
// template <class F>
// int field_matrix<F>::scan(int opt)
// {
//     int rt;
//     scanf("%*[^[]");
//     rt = scanf("[%d,%d\n", &this->r, &this->c);
//     this->dt.resize(r + 1);
//     for (int i = 1; i <= r; i++)
//     {
//         this->dt[i].resize(c + 1);
//     }
//     if (r * c != 0)
//     {
//         for (int i = 1; i <= this->r; i++)
//         {
//             for (int j = 1; j <= this->c; j++)
//             {
//                 this->dt[i][j].scan(opt);
//                 scanf(",");
//             }
//             scanf("\n");
//         }
//     }
//     else
//     {
//         scanf("NULLMATRIX\n");
//     }
//     scanf("]\n");
//     return rt;
// }
// template <class F>
// int field_matrix<F>::fscan(FILE *f, int opt)
// {
//     int rt;
//     fscanf(f, "%*[^[]");
//     rt = fscanf(f, "[%d,%d\n", &this->r, &this->c);
//     this->dt.resize(r + 1);
//     for (int i = 1; i <= r; i++)
//     {
//         this->dt[i].resize(c + 1);
//     }
//     if (r * c != 0)
//     {
//         for (int i = 1; i <= this->r; i++)
//         {
//             for (int j = 1; j <= this->c; j++)
//             {
//                 this->dt[i][j].fscan(f, opt);
//                 fscanf(f, ",");
//             }
//             fscanf(f, "\n");
//         }
//     }
//     else
//     {
//         fscanf(f, "NULLMATRIX\n");
//     }
//     fscanf(f, "]\n");
//     return rt;
// }
// template <class F>
// field_matrix<F> field_matrix<F>::operator-()
// {
//     field_matrix<F> ans(this->r, this->c);
//     for (int i = 1; i <= ans.r; i++)
//     {
//         for (int j = 1; j <= ans.c; j++)
//         {
//             ans.dt[i][j] = -this->dt[i][j];
//         }
//     }
//     return ans;
// }

template <class F>
field_matrix<F> operator*(const field_matrix<F> &a, const field_matrix<F> &b)
{
    if (a.c == b.r)
    {
        field_matrix<F> c(a.r, b.c);
        F(*A)
        [a.c];
        F(*B)
        [b.c];
        F(*C)
        [c.c];
        A = (F(*)[a.c])a.dat;
        B = (F(*)[b.c])b.dat;
        C = (F(*)[c.c])c.dat;
        for (int i = 1; i <= c.r; i++)
        {
            for (int j = 1; j <= c.c; j++)
            {
                for (int k = 1; k <= a.c; k++)
                {
                    C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
                }
            }
        }
        return c;
    }
    else
    {
        field_matrix<F> c;
        return c;
    }
}
// template <class F>
// field_matrix<F> operator*(const F &a, const field_matrix<F> &b)
// {
//     // printf("field_matrix_number_multiplicationNOTICE:scalor multiplication\n");
//     field_matrix<F> c(b.r, b.c);
//     for (int i = 1; i <= c.r; i++)
//     {
//         for (int j = 1; j <= c.c; j++)
//         {
//             c.dt[i][j] = a * b.dt[i][j];
//         }
//     }
//     return c;
// }
// template <class F>
// field_matrix<F> operator+(const field_matrix<F> &a, const field_matrix<F> &b)
// {
//     if (a.r != b.r || a.c != b.c)
//     {
//         // printf("field_matrix_additionNOTICE:matrix size different\n");
//     }
//     field_matrix<F> c(FIELD_MATRIX_MAX(a.r, b.r), FIELD_MATRIX_MAX(a.c, b.c));
//     for (int i = 1; i <= a.r; i++)
//     {
//         for (int j = 1; j <= a.c; j++)
//         {
//             c.dt[i][j] = c.dt[i][j] + a.dt[i][j];
//         }
//     }
//     for (int i = 1; i <= b.r; i++)
//     {
//         for (int j = 1; j <= b.c; j++)
//         {
//             c.dt[i][j] = c.dt[i][j] + b.dt[i][j];
//         }
//     }
//     return c;
// }
// template <class F>
// field_matrix<F> operator-(const field_matrix<F> &a, const field_matrix<F> &b)
// {
//     field_matrix<F> tmp = b;
//     return a + (-tmp);
// }
// template <class F>
// field_matrix<F> matrix_pointwise_multiplication(const field_matrix<F> &a, const field_matrix<F> &b)
// {
//     if (a.r != b.r || a.c != b.c)
//     {
//         printf("field_matrix_pointwise_multiplicationNOTICE:matrix size different\n");
//     }
//     field_matrix<F> c(FIELD_MATRIX_MAX(a.r, b.r), FIELD_MATRIX_MAX(a.c, b.c));
//     for (int i = 1; i <= c.r; i++)
//     {
//         for (int j = 1; j <= c.c; j++)
//         {
//             c.dt[i][j] = 1;
//         }
//     }
//     for (int i = 1; i <= a.r; i++)
//     {
//         for (int j = 1; j <= a.c; j++)
//         {
//             c.dt[i][j] = c.dt[i][j] * a.dt[i][j];
//         }
//     }
//     for (int i = 1; i <= b.r; i++)
//     {
//         for (int j = 1; j <= b.c; j++)
//         {
//             c.dt[i][j] = c.dt[i][j] * b.dt[i][j];
//         }
//     }
//     return c;
// }
// template <class F>
// field_matrix<F> row_echelon(const field_matrix<F> &x)
// {
//     field_matrix<F> M = x;
//     const F zero;
//     long long r = 1;
//     long long c = 1;
//     long long tr;
//     long long tc;
//     F tmp;
//     while (1)
//     {
//         if (r > M.r || c > M.c)
//         {
//             break;
//         }
//         tr = tc = 0;
//         // find where to start
//         for (int j = c; j <= M.c; j++)
//         {
//             if (tr != 0)
//             {
//                 break;
//             }
//             for (int i = r; i <= M.r; i++)
//             {
//                 if (!(M.dt[i][j] == zero))
//                 {
//                     tr = i;
//                     tc = j;
//                     break;
//                 }
//             }
//         }
//         if (tr == 0)
//         {
//             break;
//         }
//         // exchange
//         for (int j = tc; j <= M.c; j++)
//         {
//             tmp = M.dt[r][j];
//             M.dt[r][j] = M.dt[tr][j];
//             M.dt[tr][j] = tmp;
//         }
//         tmp = M.dt[r][tc];
//         for (int j = tc; j <= M.c; j++)
//         {
//             M.dt[r][j] = M.dt[r][j] / tmp;
//         }
//         for (int i = 1; i <= M.r; i++)
//         {
//             if (i == r)
//             {
//                 continue;
//             }
//             tmp = M.dt[i][tc];
//             for (int j = tc; j <= M.c; j++)
//             {
//                 M.dt[i][j] = M.dt[i][j] - M.dt[r][j] * tmp;
//             }
//         }
//         r = r + 1;
//         c = tc + 1;
//     }
//     return M;
// }
// template <class F>
// field_matrix<F> column_echelon(const field_matrix<F> &x) // can be replace by transpose & rowechelon
// {
//     field_matrix<F> M = x;
//     const F zero;
//     long long r = 1;
//     long long c = 1;
//     long long tr;
//     long long tc;
//     F tmp;
//     while (1)
//     {
//         if (r > M.r || c > M.c)
//         {
//             break;
//         }
//         tr = tc = 0;
//         // find where to start
//         for (int i = r; i <= M.r; i++)
//         {
//             if (tr != 0)
//             {
//                 break;
//             }
//             for (int j = c; j <= M.c; j++)
//             {
//                 if (!(M.dt[i][j] == zero))
//                 {
//                     tr = i;
//                     tc = j;
//                     break;
//                 }
//             }
//         }
//         if (tr == 0)
//         {
//             break;
//         }
//         // exchange
//         for (int i = tr; i <= M.r; i++)
//         {
//             tmp = M.dt[i][c];
//             M.dt[i][c] = M.dt[i][tc];
//             M.dt[i][tc] = tmp;
//         }
//         tmp = M.dt[tr][c];
//         for (int i = tr; i <= M.r; i++)
//         {
//             M.dt[i][c] = M.dt[i][c] / tmp;
//         }
//         for (int j = 1; j <= M.c; j++)
//         {
//             if (j == c)
//             {
//                 continue;
//             }
//             tmp = M.dt[tr][j];
//             for (int i = tr; i <= M.r; i++)
//             {
//                 M.dt[i][j] = M.dt[i][j] - M.dt[i][c] * tmp;
//             }
//         }
//         c = c + 1;
//         r = tr + 1;
//     }
//     return M;
// }
// template <class F>
// field_matrix<F> transpose(const field_matrix<F> &x) // not ready and im tendto make it a sudoinverse
// {
//     field_matrix<F> M(x.c, x.r);
//     for (int i = 1; i <= M.r; i++)
//     {
//         for (int j = 1; j <= M.c; j++)
//         {
//             M.dt[i][j] = x.dt[j][i];
//         }
//     }
//     return M;
// }
// template <class F>
// F determinant(const field_matrix<F> &x) // E means Euclidean Ring not ready and im tendto make it a sudoinverse
// {
//     if (x.r != x.c)
//     {
//         F r;
//         return r;
//     }
//     if (x.r == 1)
//     {
//         return x.dt[1][1];
//     }
//     long long N = x.c;
//     field_matrix<F> M = x, M1(N - 1, N - 1);
//     F P;
//     P = M.dt[1][1];
//     for (int i = 1; i <= N - 1; i++)
//     {
//         for (int j = 1; j <= N - 1; j++)
//         {
//             // printf("i=%d j=%d\n", i, j);
//             M1.dt[i][j] = M.dt[i + 1][j + 1] * M.dt[1][1] - M.dt[1][j + 1] * M.dt[i + 1][1];
//         }
//     }
//     return determinant(M1) / fast_power(P, M.r - 2);
// }
// template <class F>
// F norm(const field_matrix<F> &x) // E means Euclidean Ring not ready and im tendto make it a sudoinverse
// {
//     F ans;
//     for (int i = 1; i <= x.r; i++)
//     {
//         for (int j = 1; j <= x.c; j++)
//         {
//             ans = ans + (x.dt[i][j] * x.dt[i][j]);
//         }
//     }
//     return ans;
// }
// template <class F>
// field_matrix<F> equivalent_normalized_form(const field_matrix<F> &x)
// {
//     return column_echelon(row_echelon(x));
// }
#endif
