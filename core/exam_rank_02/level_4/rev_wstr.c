#include <unistd.h>

void	rev_wstr(char *str)
{
	int	iter;
	int	end;
	int	start;
	int	first;

	first = 1;
	iter = 0;
	while (str[iter])
		iter++;
	iter--;
	while (iter >= 0)
	{
		while (iter >= 0 && str[iter] == ' ')
			iter--;
		end = iter;
		while (iter >= 0 && str[iter] != ' ')
			iter--;
		start = iter + 1;
		if (start <= end)
		{
			if (!first)
				write(1, " ", 1);
			write(1, &str[start], end - start + 1);
			first = 0;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		rev_wstr(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}
