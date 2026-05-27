#include <unistd.h>

void	put_str(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		write(1, &str[iter], 1);
		iter++;
	}
}

void	put_nbr(int nb)
{
	if (nb >= 10)
		put_nbr(nb / 10);
	write(1, &(char){nb % 10 + '0'}, 1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			break ;
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}

void	tab_mult(int mult)
{
	int	iter;

	iter = 1;
	while (iter < 10)
	{
		put_nbr(iter);
		put_str(" x ");
		put_nbr(mult);
		put_str(" = ");
		put_nbr(iter * mult);
		write(1, "\n", 1);
		iter++;
	}
}

int	main(int argc, char **argv)
{
	int	nb;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	nb = ft_atoi(argv[1]);
	tab_mult(nb);
	return (0);
}
