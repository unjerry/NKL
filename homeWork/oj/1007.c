#include <stdio.h>
#include <math.h>

void swap(int n, double A[][100], double b[], int r, int k);
void Eliminate(int n, double A[][100], double b[]);
void Substitude(int n, double A[][100], double b[], double x[]);

// 以下程序为了和通常所说的矩阵第一行第一列适应，舍去第零行第零列
// 若需要从第零行第零列开始储存，请修改各个循环初始条件与中止条件 (i = 1; ;i <= n) => (i = 0; ; i < n)

int main()
{
    freopen("1007.in", "r", stdin);
    int n;
    double A[100][100] = {}, b[100] = {}, x[100] = {};

    scanf("%d", &n); // 读入矩阵大小 n , 增广矩阵 (A|b)
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%lf", &A[i][j]);
        }
        scanf("%lf", &b[i]);
    }

    Eliminate(n, A, b);

    Substitude(n, A, b, x);

    // 输出解向量
    for (int i = 1; i <= n; i++)
    {
        printf("%lf ", x[i]);
    }
    // printf("\n");
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         printf("%lf ", A[i][j]);
    //     }
    //     printf("%lf\n", b[i]);
    // }
    fclose(stdin);
}

void swap(int n, double A[][100], double b[], int r, int k)
{
    // 交换增广矩阵 (A|b) 之 r,k 两行
    // printf("swap\n");
    double tmp;
    tmp = b[r];
    b[r] = b[k];
    b[k] = tmp;
    for (int i = 1; i <= n; i++)
    {
        tmp = A[r][i];
        A[r][i] = A[k][i];
        A[k][i] = tmp;
    }
}

void Eliminate(int n, double A[][100], double b[])
{

    // 消元
    for (int k = 1; k <= n; k++)
    {
        // 选择主元
        int tmp = k;
        for (int r = k + 1; r <= n; r++)
        {
            if (abs(A[r][k]) > abs(A[tmp][k]))
            {
                tmp = r;
            }
        }
        // 若主元行与操作行不同，交换两行
        if (tmp != k)
        {
            swap(n, A, b, tmp, k);
        }
        // 消元
        for (int r = k + 1; r <= n; r++)
        {
            A[r][k] /= A[k][k];
            for (int c = k + 1; c <= n; c++)
            {
                A[r][c] -= A[r][k] * A[k][c];
            }
            b[r] -= A[r][k] * b[k];
        }
    }
}

void Substitude(int n, double A[][100], double b[], double x[])
{
    // 回代
    for (int c = n; c >= 1; c--)
    {
        x[c] = b[c] / A[c][c];
        for (int r = 1; r <= c - 1; r++)
        {
            b[r] -= x[c] * A[r][c];
        }
    }
}
