#include <unistd.h>

void	epur_str(char *str)
{
	int i = 0;
	int printed = 0;

	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;

		if (str[i])
		{
			if (printed)
				write(1, " ", 1);

			while (str[i] && str[i] != ' ' && str[i] != '\t')
			{
				write(1, &str[i], 1);
				i++;
			}
			printed = 1;
		}
	}
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
		epur_str(argv[1]);
    }
	write(1, "\n", 1);
	return (0);
}