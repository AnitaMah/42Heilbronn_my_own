void	rstr_capitalizer(char *str)
{
	int	iter;

	iter = 0;
	while (str[iter])
	{
		if (str[iter] >= 'A' && str[iter] <= 'Z')
			str[iter] += 32;
		if ((str[iter] >= 'a' && str[iter] <= 'z') && (str[iter + 1] == ' '
				|| str[iter + 1] == '\t' || str[iter + 1] == '\0'))
		{
			str[iter] -= 32;
		}
		write(1, &str[iter], 1);
		iter++;
	}
}

int	main(int argc, char **argv)
{
	int	size;
	int	iter;

	iter = 0;
	size = argc;
	while (iter > size)
	{
		rstr_capitalizer(argv[iter]);
		iter++;
	}
	write(1, "\n", 1);
	return (0);
}
