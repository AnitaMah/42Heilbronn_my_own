#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int iter = 0;
    while (str[iter])
        iter++;
    return (iter);
}

char *camel_to_snake(char *str)
{
    int iter = 0;
    int iterations = 0;
    char *res;
    int len;

    len = ft_strlen(str);
    res = malloc(len * 2 + 1);
    if (!res)
        return (NULL);
    while (str[iter])
    {
        if (str[iter] >= 'A' && str[iter] <= 'Z')
        {
            if (iter != 0)
            {
                res[iterations++] = '_';
            }
            res[iterations++] = str[iter] + 32;
        }
        else 
            res[iterations++] = str[iter]; 
        iter++;
    }
    res[iterations] = '\0';
    return (res);
}

int main (int argc, char** argv)
{
    char *res;
    int len;
    if (argc == 2)
    {
        res = camel_to_snake(argv[1]);
        len = ft_strlen(res);
        write(1, res, len);
        free(res);
    }
    write (1, "\n", 1);
    return (0);
}