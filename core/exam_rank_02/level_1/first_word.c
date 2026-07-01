#include <unistd.h>

void    print (char *str)
{
    int iter = 0;
    while (str[iter] == ' ' || str[iter] == '\t')
        iter++;
    while (str[iter] && str[iter] != ' ' && str[iter] != '\t')
    {
        write(1, &str[iter], 1);
        iter++;
    }
}

int main (int argv, char **argc)
{
    int iter = 0;
    if (argv == 2)
    {
        print(argc[1]);
    }
    write(1, "\n", 1);
    return (0);
}