#include <unistd.h>

int main (int argc, char **argv)
{
    int j = 0;
    if (argc > 1)
    {
        while(argv[1][j] != '\0')
        {
            if (argv[1][j] == 'z')
            {
                write(1, "z\n", 2);
                break;
            }
            else
            {
                write(1, "z\n", 2);
            }
            j++;
        }
    }
    else
        write(1, "z\n", 2);
}