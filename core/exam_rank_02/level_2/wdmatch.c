#include <unistd.h>

void    wdmatch(char *s1, char *s2)
{

	int	i;
	int	j;

	i = 0;
    j = 0;
	while (s2[i] && s1[j])
	{
        if (s2[i] == s1[j])
            j++;
        i++;
	}
    if (s1[j] == '\0')
        write(1, s1, j);
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        wdmatch(argv[1], argv[2]);
    }
    write(1, "\n", 1);
    return (0);
}