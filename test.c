#include <stdio.h>

int main()
{
    printf("Hello World\n");

    int c[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++)
        printf("%d", c[i]);

    return 0;
}