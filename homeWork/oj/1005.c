#include <stdio.h>
#include <math.h>

void Doolittle(int n, double A[][100], double L[][100], double U[][100]);

int main()
{
    // freopen("1005.in", "r", stdin);
    int n;
    double A[100][100], L[100][100], U[100][100];

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }
    Doolittle(n, A, L, U);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%lf ", L[i][j]);
        }
        printf("\n");
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%lf ", U[i][j]);
        }
        printf("\n");
    }
    // fclose(stdin);
}

void Doolittle(int n, double A[][100], double L[][100], double U[][100])
{
    // Doolittle分解
    for (int i = 1; i <= n; i++)
    {
        // 计算矩阵U之第i行第k列元素
        for (int c = i; c <= n; c++)
        {
            U[i][c] = A[i][c];
            for (int k = 1; k <= i - 1; k++)
            {
                U[i][c] -= L[i][k] * U[k][c];
            }
        }
        // 计算矩阵L之第i列第k行元素
        L[i][i] = 1;
        for (int r = i + 1; r <= n; r++)
        {
            L[r][i] = A[r][i];
            for (int k = 1; k <= i - 1; k++)
            {
                L[r][i] -= L[r][k] * U[k][i];
            }
            L[r][i] /= U[i][i];
        }
    }
    return;
}
