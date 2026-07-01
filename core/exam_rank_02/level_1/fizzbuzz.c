#include <unistd.h>

void print_digt (int nb)
{
    write (1, &(char){nb + '0'}, 1);
}

void print(int nb)
{
    if (nb >= 10)
    {
		print(nb / 10);
    }
    print_digt(nb % 10);
}

int main(void)
{
    int iter = 1;
    while (iter <= 100)
    {
        if (iter % 3 == 0 && iter % 5 == 0)
        {
            write(1, "fizzbuzz", 8);
        }
        else if (iter % 3 == 0)
        {
            write (1, "fizz", 4);
        }
        else if (iter % 5 == 0)
        {
            write (1, "buzz", 4);
        }
        else
        {
            print(iter);
        }
        write (1, "\n", 1);
        iter++;
    }
}
