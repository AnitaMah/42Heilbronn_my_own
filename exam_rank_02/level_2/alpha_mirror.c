#include <unistd.h>
void ft_putstr(char *str)
{
    int iter = 0;
    while (str[iter])
    {
        write(1, &str[iter], 1);
        iter++;
    }
}

void print_alpha_mirror(char *str)
{
    int iter = 0;
    while (str[iter])
    {
        if (str[iter] >= 'a' && str[iter] <= 'z')
        {
            str[iter] = 'z' - (str[iter] - 'a');
        }
        else if (str[iter] >= 'A' && str[iter] <= 'Z')
        {
            str[iter] = 'Z' - (str[iter] - 'A');
        }
        iter++;
    }
    ft_putstr(str);
}

int main (int argc, char **argv)
{
    if (argc == 2)
    {
        print_alpha_mirror(argv[1]);
    }
    write(1, "\n", 1);
    return (0);
}