#include <unistd.h>
int find_positions(char c)
{
    if (c >= 'A' && c <= 'Z')
        return ( c - 'A' + 1);
    else if (c >= 'a' && c <= 'z')
        return (c - 'a' + 1);
    return (0);
}

void reverse(char *str)
{
    int iter = 0, index;

    while (str[iter])
    {
        index = find_positions(str[iter]);
        while (index)
        {
            write(1, &str[iter], 1);
            index--;
        }
        iter++;
    }
}

int  main(int argv, char **argc)
{
    if (argv == 2)
    {
        reverse(argc[1]);
    }
    write(1, "\n", 1);
    return (0);
}