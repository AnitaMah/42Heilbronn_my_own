#include <unistd.h>

void	ft_putstr(char *s1)
{
	int	iter;

	iter = 0;
	while (s1[iter])
	{
		write(1, &s1[iter], 1);
		iter++;
	}
}

void	search_and_replace(char *s1, char search, char replace)
{
	int	i;

	i = 0;
	if (!s1)
		return ;
	while (s1[i])
	{
		if (s1[i] == search)
		{
			s1[i] = replace;
		}
		i++;
	}
	ft_putstr(s1);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 4 && !argv[2][1] && !argv[3][1])
	{
		search_and_replace(argv[1], argv[2][0], argv[3][0]);
	}
	write(1, "\n", 1);
	return (0);
}
