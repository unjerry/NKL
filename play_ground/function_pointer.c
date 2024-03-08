#include <stdio.h>

void PRINT(int (*func)(int))
{
    printf("%ld\n", func(3));
}

int aa(int a)
{
    return a + 1;
}

int main()
{
    aa(3);
    PRINT(aa);
    return 0;
}
