#include <stdlib.h>
#include <stdio.h>
int do_op(int nb1, char op, int nb2)
{
    int results = 0;
    if (op == '/' && nb2 == 0)
    {
        return (0);    
    }
    if (op == '%' && nb2 == 0)
    {
        return (0);    
    }
    if (op == '*')
    {
        results = nb1 * nb2;        
    }
    else if (op == '+')
    {
        results = nb1 + nb2;
    }
    else if (op == '-')
    {
        results = nb1 - nb2;
    }
    else if (op == '/')
    {
        results = nb1 / nb2;    
    }
    else if (op == '%')
    {
        results = nb1 % nb2;
    }
    return (results);
}
int main (int argc, char **argv)
{
    int nb1, nb2, res;
    if (argc == 4)
    {
        nb1 = atoi(argv[1]);
        nb2 = atoi(argv[3]);
        res = do_op(nb1, argv[2][0], nb2);
        printf("%d", res);
    }
    printf ("\n");
    return (0);
}