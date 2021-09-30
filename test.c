#include <stdio.h>

int max(int a, int b)
{
    return a < b ? b : a;
}

int main()
{
    printf("Hello World\n");

    int c[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++)
        printf("%d", c[i]);

    int j = 0;
    while (j < 4)
    {
        printf("print %d\n", c[j]);
    }

    volatile reg = j;
    j += 4;

    j = max(c[2], c[3]);

    switch (reg)
    {
    case 0:
        j += 5;
        break;
    case 100:
        j = c[2];
        break;
    default:
        printf("may error);
    }

    return 0;
}