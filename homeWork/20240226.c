#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p1 = malloc(32);             // allocates enough for an array of 4 int
    int *p2 = malloc(sizeof(int[4])); // same, naming the type directly
    int *p3 = malloc(4 * sizeof *p3); // same, without repeating the type name
    int p4[100];

    if (p1)
    {
        for (int n = 0; n < 4; ++n) // populate the array
            p1[n] = n * n;
        for (int n = 0; n < 4; ++n) // print it back out
            printf("p1[%d] == %d\n", n, p1[n]);
    }
    printf("%d\n", sizeof(p4));

    free(p1);
    free(p2);
    free(p3);
}