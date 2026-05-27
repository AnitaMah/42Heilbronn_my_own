#include <unistd.h>
int main (void)
{
    char *str = "aBcDeFgHiJkLmNoPqRsTuVwXyZ";
    int i = 0;
    while (str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
    return (0);
}