#include <unistd.h>
#include <stdlib.h>
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
char *snake_to_camel(char *str)
{
	int		i = 0;
	int		j = 0;
	int		len = ft_strlen(str);
	char	*res;
	int		upper = 0;

	res = malloc (len + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '_')
			upper = 1;
		else
		{
			if (upper && str[i] >= 'a' && str[i] <= 'z')
				res[j++]= str[i] -32;
			else
				res[j++] = str[i];
			upper = 0;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

int main(int argc, char **argv)
{
	char *str;
	if (argc == 2)
	{
		str = snake_to_camel(argv[1]);
		if (str)
		{
			ft_putstr(str);
			free (str);
		}
	}
	write(1, "\n", 1);
	return (0);
}