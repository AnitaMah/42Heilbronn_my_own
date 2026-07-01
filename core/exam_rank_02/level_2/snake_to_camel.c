#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
		iter++;
	return (iter);
}

void	ft_putstr(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		write(1, &str[iter], 1);
		iter++;
	}
}
char	*snake_to_camel(char *str)
{
	int		i;
	char	*res;
	int		j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '_')
			i++;
		else
		{
			if (i > 0 && str[i - 1] == '_')
				res[j++] = str[i] - 32;
			else
				res[j++] = str[i];
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}

int	main(int argc, char **argv)
{
	char	*str;

	if (argc == 2)
	{
		str = snake_to_camel(argv[1]);
		if (str)
		{
			ft_putstr(str);
			free(str);
		}
	}
	write(1, "\n", 1);
	return (0);
}
