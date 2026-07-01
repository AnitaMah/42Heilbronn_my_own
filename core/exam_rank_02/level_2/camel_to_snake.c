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

char	*camel_to_snake(char *str)
{
	int		i;
	int		j;
	char	*res;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	res = malloc(len * 2 + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			if (i != 0)
				res[j++] = '_';
			res[j++] = str[i] + 32;
		}
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	main(int argc, char **argv)
{
	char	*res;
	int		len;

	if (argc == 2)
	{
		res = camel_to_snake(argv[1]);
		len = ft_strlen(res);
		write(1, res, len);
		free(res);
	}
	write(1, "\n", 1);
	return (0);
}
