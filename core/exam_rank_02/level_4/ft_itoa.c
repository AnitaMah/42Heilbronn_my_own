#include <stdlib.h>

int	ft_size(int nb)
{
	int		size;
	long	n;

	n = nb;
	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

void	fill_str(char *res, int size, int nb)
{
	long	n;

	n = nb;
	res[size] = '\0';
	if (n == 0)
	{
		res[0] = '0';
		return ;
	}
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		res[--size] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int nb)
{
	char	*res;
	int		size;

	size = ft_size(nb);
	res = (char *)malloc(size + 1);
	if (!res)
		return (NULL);
	fill_str(res, size, nb);
	return (res);
}
