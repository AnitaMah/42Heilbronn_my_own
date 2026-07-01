#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_seen(char *str, char c, int limit)
{
	int i;

	i = 0;
	while (i < limit)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_union(char *s1, char *s2)
{
	int	i;
	int	j;
	int len;

	i = 0;
	len = ft_strlen(s1);
	while (s1[i])
	{
		if (!is_seen(s1, s1[i], i))
		{
			write(1, &s1[i], 1);
		}
		i++;
	}
	j = 0;
	while (s2[j])
	{
		if (!is_seen(s1, s2[j], len)
			&& !is_seen(s2, s2[j], j))
				write(1, &s2[j], 1);
		j++;
	}
}  

int main (int argc, char **argv)
{
    if (argc == 3)
    {
        ft_union(argv[1], argv[2]);
    }
    write(1, "\n", 1);
    return (0);
}