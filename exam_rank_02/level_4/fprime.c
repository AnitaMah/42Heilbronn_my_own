#include <stdio.h>
#include <stdlib.h>

void	fprime(int nb)
{
	int	div;

	div = 1;
	if (nb < 0)
		return ;
	if (nb == 1)
		printf("1");
	while (nb > div++)
	{
		if (nb % div == 0)
		{
			printf("%d", div);
			if (nb == div)
				break ;
			printf("*");
			nb /= div;
			div = 1;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		fprime(atoi(argv[1]));
	}
	printf("\n");
	return (0);
}
