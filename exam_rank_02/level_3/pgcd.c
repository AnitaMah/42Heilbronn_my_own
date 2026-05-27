#include <stdlib.h>
#include <stdio.h>

void    pgcd(int a, int b)
{
    int res;
    int div;
    if (a < 0 || b < 0)
        return (0);
    div = 1;
    res = 0;
    while (div <= a && div <= b)
    {
        if (a % div == 0 && div % b == 0)
            res = div;
        div++;
    }
    printf("%d", res);
}

int main(int argc, char **argv)
{
    int a;
    int b;
    if (argc == 3)
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        pgcd(a, b);
    }
    printf("\n");
    return (0);
}