#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_alpha_mirror(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if (str[iter] >= 'a' && str[iter] <= 'z')
		{
			ft_putchar('z' - (str[iter] - 'a'));
		}
		else if (str[iter] >= 'A' && str[iter] <= 'Z')
		{
			ft_putchar('Z' - (str[iter] - 'A'));
		}
		else
			ft_putchar(str[iter]);
		iter++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		print_alpha_mirror(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}
