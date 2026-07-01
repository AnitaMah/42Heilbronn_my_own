#include <unistd.h>

int main (void)
{
    int i = 9;
    while (i >= 0)
    {
        write(1, &(char){i + '0'}, 1);
        i--;
    }
}