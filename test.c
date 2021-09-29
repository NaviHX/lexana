#include <stdio.h>

int main()
{
    printf("Hello World\n");

    int c[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++)
        printf("%d", c[i]);

    int j=0;
    while(j<4)
    {
        printf("print %d\n",c[j]);
    }

    return 0;
}