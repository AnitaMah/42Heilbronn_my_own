
int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	rosting(char *str)
{
	int	i;
	int	is_fist_word;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (!str[i])
		return ;
	is_fist_word = i;
	while (str[i] && !is_space(str[i]))
		i++;
	while (str[i])
	{
		if (is_space(str[i]) && !is_space(str[i + 1]))
			put_char(' ');
		else if (!is_space(str[i]))
			put_char(str[i]);
		i++;
	}
	if (i != is_fist_word)
		put_char(' ');
	while (str[is_fist_word] && !is_space(str[is_fist_word]))
	{
		put_char(str[is_fist_word]);
		is_fist_word++;
	}
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		rosting(argv[1]);
	write(1, "\n", 1);
	return (0);
}
